#!/usr/bin/env bash
#
# Reset the AT91SAM9260, let the primary loader run for 60 s so the EBI/SMC
# and the on-chip SRAM remap at 0x00000000 are set up, then halt and
# replicate what the primary loader's run_module() does on an ARM-CODE
# module: copy each "data" segment into RAM, zero-fill each "bss" segment,
# and jump to the entry point.
#
# This lets us boot a fresh App image straight out of RAM, without
# touching the parallel flash, so we can validate it before committing
# it to flash.
#
# Module layout, decoded from the header of vendor/Rev 2_5/App/RM2040-044.bin
# and cross-checked against run_module @ 0x00300000 in Bbb-1004.s19:
#
#   struct_module {
#     char[8] magic;                // "ARM-CODE"
#     dword   crc_len;              // 0x00023724
#     dword   checksum;             // 0xF54B2D2F
#     dword   crc_start_ptr;        // 0x000001F0
#     dword   _unnamed;             // 0x20400044
#     dword   num_segments;         // 7
#     void   *entry_ptr;            // 0x00000000  (jump to vectors)
#     struct_seg_record seg[7];
#   };
#   struct_seg_record { void *dest; dword value_or_offset; dword len; dword mode; };
#     mode == 0 : fill <dest..dest+len> with the constant <value_or_offset>
#     mode != 0 : copy <len> bytes from file_offset <value_or_offset> into <dest>
#
#   #  mode  dest          src_off    len         purpose
#   0  copy  0x20000000    0x000000   0x000200    header mirror ("head")
#   1  copy  0x00000000    0x000200   0x0003A0    exception vectors
#   2  copy  0x20000200    0x0005A0   0x022820    .text
#   3  copy  0x20023000    0x022DC0   0x000974    .data
#   4  bss   0x20024000    0          0x1708E0    .bss (region 1)
#   5  bss   0x20195000    0          0xBD3100    .bss (region 2, framebuffer/heap)
#   6  bss   0x20D69000    0          0x060000    .bss (region 3)
#
# Usage:    sudo ./load_module.sh [path/to/module.bin]
# Env:
#   RUN_MS    run time before halt, ms      (default 60000)
#   CFG       OpenOCD config to use         (default at91sam9260_jtaghat.cfg)
#   SKIP_BSS  if set, skip the BSS zero-fill (default unset — fill it)
#
set -euo pipefail

BIN="${1:-$(dirname "$0")/RM2040-044.bin}"
RUN_MS="${RUN_MS:-60000}"
CFG="${CFG:-$(dirname "$0")/at91sam9260_jtaghat.cfg}"

if [ "$(id -u)" -ne 0 ]; then
    echo "error: must run as root (bcm2835gpio needs /dev/mem)" >&2
    exit 1
fi

if [ ! -f "$BIN" ]; then
    echo "error: module not found: $BIN" >&2
    exit 1
fi

# Verify the magic so we don't silently load garbage if the wrong file is
# passed in.
MAGIC=$(head -c 8 "$BIN")
if [ "$MAGIC" != "ARM-CODE" ]; then
    echo "error: $BIN does not start with 'ARM-CODE' magic" >&2
    exit 1
fi

BIN_ABS="$(cd "$(dirname "$BIN")" && pwd)/$(basename "$BIN")"

# Stage zero-fill blobs for the BSS regions. load_image streams the whole
# blob over JTAG in one go, which is dramatically faster than mwb looping
# tens of MB of zeroes one word at a time.
SCRATCH=""
if [ -z "${SKIP_BSS:-}" ]; then
    SCRATCH="$(mktemp -d)"
    trap 'rm -rf "$SCRATCH"' EXIT
    # sizes match seg[4], seg[5], seg[6] above
    dd if=/dev/zero of="$SCRATCH/bss1.bin" bs=4096 count=$((0x1708E0 / 4096 + 1)) status=none
    dd if=/dev/zero of="$SCRATCH/bss2.bin" bs=4096 count=$((0xBD3100 / 4096 + 1)) status=none
    dd if=/dev/zero of="$SCRATCH/bss3.bin" bs=4096 count=$((0x060000 / 4096))     status=none
    # Trim to exact sizes; the kernel's truncate is byte-accurate.
    truncate -s $((0x1708E0)) "$SCRATCH/bss1.bin"
    truncate -s $((0xBD3100)) "$SCRATCH/bss2.bin"
    truncate -s $((0x060000)) "$SCRATCH/bss3.bin"
fi

echo "Load plan:"
echo "  cfg   : $CFG"
echo "  bin   : $BIN_ABS"
echo "  run   : ${RUN_MS} ms before halt"
echo "  bss   : $([ -z "${SKIP_BSS:-}" ] && echo "zero-fill" || echo "SKIPPED")"
echo

TCL=$(cat <<EOF
init
echo "resetting target, letting it run for ${RUN_MS} ms..."
reset run
sleep ${RUN_MS}
halt

# PLL is up after the primary loader settles, so raise TCK for the bulk
# transfer. 3 MHz is the same ceiling dump_flash.sh uses for the JTAG Hat
# level shifters on a Pi 3B+.
adapter speed 500


# --- segment table from RM2040-044.bin header ----------------------------
# load_image syntax: load_image <file> <addr> bin <file_offset> <length>
echo "loading seg 0 (head)    -> 0x20000000  0x000200"
load_image head.bin 0x20000000 bin
echo "loading seg 1 (vectors) -> 0x00000000  0x0003A0"
# load_image vectors.bin 0x00000000 bin
load_image vectors.bin 0x00200000 bin
echo "loading seg 2 (text)    -> 0x20000200  0x022820"
load_image text.bin 0x20000200 bin
echo "loading seg 3 (data)    -> 0x20023000  0x000974"
load_image data.bin 0x20023000
EOF
)

if [ -z "${SKIP_BSS:-}" ]; then
TCL="$TCL
$(cat <<EOF
echo "zeroing seg 4 (bss1) at 0x20024000  0x1708E0 (~1.5 MB)..."
load_image {${SCRATCH}/bss1.bin} 0x20024000 bin
echo "zeroing seg 5 (bss2) at 0x20195000  0xBD3100 (~12 MB)..."
load_image {${SCRATCH}/bss2.bin} 0x20195000 bin
echo "zeroing seg 6 (bss3) at 0x20D69000  0x060000 (384 KB)..."
load_image {${SCRATCH}/bss3.bin} 0x20D69000 bin
EOF
)"
fi

TCL="$TCL
$(cat <<'EOF'

# ARM926EJ-S: invalidate I-cache and D-cache (and drain write buffer) so the
# core re-fetches the freshly loaded vectors and .text from RAM rather than
# from whatever the previous firmware had cached. This is the CP15 c7 dance:
#   MCR p15, 0, Rd, c7, c5, 0   invalidate entire I-cache
#   MCR p15, 0, Rd, c7, c6, 0   invalidate entire D-cache
#   MCR p15, 0, Rd, c7, c10, 4  drain write buffer
arm mcr 15 0 7 5  0 0
arm mcr 15 0 7 6  0 0
arm mcr 15 0 7 10 4 0

# Point PC at the entry_ptr from the module header (0x00000000 -> reset
# vector at the start of the just-loaded vector table) and run.
reg pc 0x00000000
echo "resuming at 0x00000000 (reset vector of loaded module)..."
resume 0x20000228

# Stay attached briefly so any "halt on fault" semantics on the adapter
# don't kill the run, then drop the OpenOCD session. The target keeps
# executing after shutdown.
sleep 600
shutdown
EOF
)"

exec openocd -f "$CFG" -c "$TCL"

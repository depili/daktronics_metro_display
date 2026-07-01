#!/usr/bin/env bash
#
# Reset the AT91SAM9260, let it run for 60 s so the bootloader brings up the
# EBI / SMC for the external flash, then halt and dump the flash region in
# 256 KB chunks to ./flash_dump/dump_<addr>.bin
#
# Usage:    sudo ./dump_flash.sh [output_dir]
# Env:
#   START       base address to dump from   (default 0x10000000 = EBI_CS0)
#   CHUNK       bytes per file              (default 262144 = 256 KB)
#   COUNT       number of chunks            (default 64 = 16 MB total)
#   RUN_MS      run time before halt, ms    (default 60000 = 60 s)
#   CFG         OpenOCD config to use       (default at91sam9260_jtaghat.cfg)
#
# NOTE on START:
#   On the AT91SAM9260 the external NOR flash on EBI chip-select 0 is at
#   0x10000000, NOT 0x01000000 (that's an internal-peripheral region).
#   Override with `START=0x01000000 ./dump_flash.sh` if you really want the
#   literal address from your spec.
#
set -euo pipefail

OUT_DIR="${1:-flash_dump}"
START="${START:-0x10030000}"
CHUNK="${CHUNK:-262144}"
COUNT="${COUNT:-20}"
RUN_MS="${RUN_MS:-30000}"
CFG="${CFG:-$(dirname "$0")/at91sam9260_jtaghat.cfg}"

if [ "$(id -u)" -ne 0 ]; then
    echo "error: must run as root (bcm2835gpio needs /dev/mem)" >&2
    exit 1
fi

mkdir -p "$OUT_DIR"
OUT_DIR_ABS="$(cd "$OUT_DIR" && pwd)"

echo "Dump plan:"
echo "  cfg     : $CFG"
echo "  start   : $START"
echo "  chunk   : $CHUNK bytes"
echo "  count   : $COUNT chunks  ($((CHUNK*COUNT/1024)) KB total)"
echo "  run     : ${RUN_MS} ms before halt"
echo "  out dir : $OUT_DIR_ABS"
echo

# Build the TCL dump loop. Using a heredoc keeps the quoting sane.
TCL=$(cat <<EOF
init
echo "resetting target, letting it run for ${RUN_MS} ms..."
reset run
sleep ${RUN_MS}
halt

# Disable watchdog
# mww 0xfffffd44 0x00008000

# PLL is up after the firmware boots, so raise TCK for the dump.
# Capped at 3 MHz to stay well inside what the JTAG Hat level shifters
# and the bcm2835gpio bitbang driver handle reliably on a Pi 3B+.
adapter speed 250

set start  ${START}
set chunk  ${CHUNK}
set count  ${COUNT}
set outdir "${OUT_DIR_ABS}"
# dump_image mem 0x20000000 0x100000


# Secondary loader put the app image here
dump_image RM2037.bin      0x21c00000 0x315E4

# Fonts
dump_image font1.bin       0x208eb000 0xFBE8
dump_image font2.bin       0x2092b000 0xFBE8
dump_image font3.bin       0x2096b000 0xFBE8

# App on the display, segments
# dump_image mem_vectors 0x00000000 0x3A0
# dump_image mem_head    0x20000000 0x200
# dump_image mem_text    0x20000200 0x3072C
# dump_image mem_data    0x20031000 0x928
# dump_image mem_bss1    0x20032000 0x528054
# dump_image mem_bss2    0x2055b000 0x4C6100

#dump_image flash_1000 0x10000000 0x10000
#dump_image flash_1001 0x10010000 0x20000
#dump_image flash_1003 0x10030000 0x40000

#for {set i 0} {\$i < \$count} {incr i} {
#    set addr  [expr {\$start + \$i * \$chunk}]
#    set fname [format "%s/dump_%08x.bin" \$outdir \$addr]
#    echo [format "  chunk %3d/%d  0x%08x -> %s" [expr {\$i + 1}] \$count \$addr \$fname]
#    dump_image \$fname \$addr \$chunk
#}

echo "dump complete"
shutdown
EOF
)

exec openocd -f "$CFG" -c "$TCL"

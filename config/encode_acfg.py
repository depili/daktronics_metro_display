#!/usr/bin/env python3
"""encode_acfg.py — Build (or decode) an ARM-ACFG configuration file
for the Daktronics RM2040 boot loader.

The boot loader's `check_module_header` validates a 16-byte header:

    [0..3]   magic       = b"ARM-"
    [4..7]   type tag    = b"ACFG"  (or another 4-char module type)
    [8..11]  content_len (uint32 LE)
    [12..15] stored CRC  (uint32 LE)
    [16..]   content

The CRC is the standard CRC-32/ISO-HDLC computed over the content
bytes WITHOUT the final XOR. zlib.crc32() returns the value WITH the
final XOR, so we XOR back: `unit_crc = zlib.crc32(content) ^ 0xFFFFFFFF`.

The config-parser stops at a line containing just a single '.'. By
default this encoder normalises line endings to CRLF and appends a
trailing terminator line ('.\\r\\n') if the input doesn't already
end with one. Use --no-terminator to write the content bytes verbatim.

Examples:

    # Encode a text config into a binary blob ready to flash
    $ ./encode_acfg.py boot_config.txt -o boot.bin -v
    content_len=4438 crc=0xa64a17f9 file_size=4454 type_tag='ACFG'

    # Decode a memory dump (handles leading NUL padding from the dump
    # window not aligning with the file boundary)
    $ ./encode_acfg.py --decode memdump/cfg -o extracted.txt -v
    type_tag = b'ACFG'  declared_len = 4438
    stored_crc = 0xa64a17f9  computed_crc = 0xa64a17f9  (ok)
"""

import argparse
import sys
import zlib
from pathlib import Path

MAGIC = b"ARM-"
DEFAULT_TYPE_TAG = b"ACFG"

# parse_config's content buffer is 8176 bytes
MAX_CONTENT = 8176


def calc_crc(content: bytes) -> int:
    """Compute the unit's CRC: standard CRC-32/ISO-HDLC minus the final XOR."""
    return zlib.crc32(content) ^ 0xFFFFFFFF


def normalise_content(text: str, add_terminator: bool = True) -> bytes:
    """Normalise line endings to CRLF and (optionally) ensure a '.\\r\\n'
    terminator. The parser stops on a line containing just '.'.
    """
    # Collapse any line ending into LF, then expand all to CRLF.
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    text = text.replace("\n", "\r\n")
    if add_terminator and not text.rstrip().endswith("\r\n."):
        if not text.endswith("\r\n"):
            text += "\r\n"
        text += ".\r\n"
    return text.encode("ascii")


def build_acfg(content: bytes, type_tag: bytes = DEFAULT_TYPE_TAG) -> bytes:
    if len(type_tag) != 4:
        raise ValueError(f"type tag must be exactly 4 bytes, got {len(type_tag)}")
    if len(content) > MAX_CONTENT:
        raise ValueError(
            f"content length {len(content)} exceeds the {MAX_CONTENT}-byte "
            f"loader buffer"
        )
    length_le = len(content).to_bytes(4, "little")
    crc_le = calc_crc(content).to_bytes(4, "little")
    return MAGIC + type_tag + length_le + crc_le + content


def decode_acfg(data: bytes) -> tuple:
    """Locate the ARM- magic, validate the header, return
    (type_tag, content, declared_len, stored_crc, computed_crc).
    Raises ValueError if the magic is missing.
    """
    idx = data.find(MAGIC)
    if idx < 0:
        raise ValueError("ARM- magic not found in input")
    data = data[idx:]
    if len(data) < 16:
        raise ValueError(f"data too short for header: {len(data)} bytes")
    type_tag = data[4:8]
    declared_len = int.from_bytes(data[8:12], "little")
    stored_crc = int.from_bytes(data[12:16], "little")
    if 16 + declared_len > len(data):
        raise ValueError(
            f"declared content length {declared_len} exceeds available "
            f"{len(data) - 16} bytes after header"
        )
    content = data[16 : 16 + declared_len]
    computed_crc = calc_crc(content)
    return type_tag, content, declared_len, stored_crc, computed_crc


def cmd_encode(args, ap):
    if len(args.type_tag) != 4:
        ap.error(f"type tag must be 4 chars, got {args.type_tag!r}")

    text = sys.stdin.read() if args.input == "-" else Path(args.input).read_text()
    content = normalise_content(text, add_terminator=not args.no_terminator)

    try:
        out = build_acfg(content, args.type_tag.encode("ascii"))
    except ValueError as e:
        ap.error(str(e))

    if args.output == "-":
        sys.stdout.buffer.write(out)
    else:
        Path(args.output).write_bytes(out)

    if args.verbose:
        crc = calc_crc(content)
        print(
            f"content_len={len(content)} crc={crc:#010x} "
            f"file_size={len(out)} type_tag={args.type_tag!r}",
            file=sys.stderr,
        )


def cmd_decode(args, ap):
    data = (
        sys.stdin.buffer.read()
        if args.input == "-"
        else Path(args.input).read_bytes()
    )
    try:
        type_tag, content, declared_len, stored_crc, computed_crc = decode_acfg(data)
    except ValueError as e:
        ap.error(str(e))

    if args.output == "-":
        sys.stdout.buffer.write(content)
    else:
        Path(args.output).write_bytes(content)

    if args.verbose:
        status = "ok" if stored_crc == computed_crc else "MISMATCH"
        print(
            f"type_tag = {type_tag!r}  declared_len = {declared_len}\n"
            f"stored_crc = {stored_crc:#010x}  computed_crc = {computed_crc:#010x}  ({status})",
            file=sys.stderr,
        )
    if stored_crc != computed_crc:
        return 1
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ap.add_argument(
        "input",
        help="input file path (use '-' for stdin)",
    )
    ap.add_argument(
        "--output", "-o", required=True,
        help="output file path (use '-' for stdout)",
    )
    ap.add_argument(
        "--decode", action="store_true",
        help="decode mode: read ARM-ACFG binary, write content text. "
             "Validates the CRC. Skips leading NUL padding so memory "
             "dumps where the file isn't aligned to the dump window work.",
    )
    ap.add_argument(
        "--type-tag", default="ACFG",
        help="4-char type tag (encode mode; default: ACFG)",
    )
    ap.add_argument(
        "--no-terminator", action="store_true",
        help="encode mode: don't auto-append a '.\\r\\n' parser-stop line",
    )
    ap.add_argument(
        "--verbose", "-v", action="store_true",
        help="print size and CRC info to stderr",
    )
    args = ap.parse_args()

    if args.decode:
        return cmd_decode(args, ap)
    return cmd_encode(args, ap)


if __name__ == "__main__":
    sys.exit(main())

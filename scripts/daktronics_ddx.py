"""Daktronics AF-6700 DDX protocol client library.

Implements the ASCII serial protocol used by the PCB236/PCB237 controllers
(RM2037 / RM2040 firmware) as reverse-engineered in this project. See
README.md and "Commands for DDX protocol.md" in the repository root for
the protocol specification.

Typical use:

    from daktronics_ddx import Display, Line

    with Display("/dev/ttyUSB0", address="0A") as d:
        d.define_page(1, [
            Line(1, "Helsinki Hacklab"),
            Line(2, "By: Depili"),
            Line(3, "26-06-21"),
        ], mapping=1, duration=5)
        d.set_playlist([1])
"""

from __future__ import annotations

import logging
import time
from dataclasses import dataclass, field
from typing import Iterable, List, Mapping, Optional, Sequence

import serial


ACK_CHAR = "Y"
NACK_CHAR = "N"

STATUS_NOT_READY = 0x01
STATUS_BAD_PARAM = 0x02
STATUS_DENIED = 0x04
STATUS_BAD_SEPARATOR = 0x08
STATUS_CHECKSUM_MISMATCH = 0x20

VALID_JUSTIFY = ("C", "L", "N", "R")

PIXEL_TRANSPARENT = 0
PIXEL_OFF = 1
PIXEL_RED = 2
PIXEL_GREEN = 3
PIXEL_AMBER = 4

# Map user-facing pixel values to the protocol's internal pixel codes
# (the wire codes are 0=off, 1=red, 2=green, 3=amber, 4=transparent).
_PIXEL_TO_WIRE = {
    PIXEL_OFF: 0,
    PIXEL_RED: 1,
    PIXEL_GREEN: 2,
    PIXEL_AMBER: 3,
    PIXEL_TRANSPARENT: 4,
}

SPRITE_MAX_PIXELS = 32768
SPRITE_MAX_INDEX = 24

DEFAULT_PIXEL_CHARS: Mapping[str, int] = {
    " ": PIXEL_OFF,
    ".": PIXEL_TRANSPARENT,
    "R": PIXEL_RED,
    "r": PIXEL_RED,
    "G": PIXEL_GREEN,
    "g": PIXEL_GREEN,
    "A": PIXEL_AMBER,
    "a": PIXEL_AMBER,
    "X": PIXEL_AMBER,
    "x": PIXEL_AMBER,
}


def escape_text(text: str) -> str:
    """Escape protocol control characters in a literal text payload.

    The DDX text-field control characters are ``\\``, ``|``, ``>`` and
    ``$``. Pass already-escaped text or hand-crafted control sequences
    through unchanged by skipping this helper.
    """
    out = []
    for ch in text:
        if ch in ("\\", "|", ">", "$"):
            out.append("\\" + ch)
        else:
            out.append(ch)
    return "".join(out)


def build_address(group: int, unit: str) -> str:
    """Compose a wire-format address from group (0-8) and unit (A-Z)."""
    if not 0 <= group <= 8:
        raise ValueError("group must be 0-8")
    unit = unit.upper()
    if len(unit) != 1 or not ("A" <= unit <= "Z"):
        raise ValueError("unit must be a single letter A-Z")
    return f"{group}{unit}"


def _checksum(data: bytes) -> int:
    return sum(data) & 0xFF


def build_frame(address: str, payload: str, checksum: bool = True) -> bytes:
    """Wrap a command payload into a complete protocol frame.

    address: two-character wire address, e.g. "0A".
    payload: the command body (without surrounding brackets), e.g. "!?p".
    checksum: when True, append "/HH" checksum before the closing "]".
    """
    if len(address) != 2:
        raise ValueError(f"address must be two chars, got {address!r}")
    inner = f"[{address}{payload}".encode("ascii")
    if checksum:
        return inner + f"/{_checksum(inner):02X}]".encode("ascii")
    return inner + b"]"


@dataclass
class Response:
    """A parsed ACK/NACK reply frame from the display."""

    unit: str
    ack: bool
    status: int
    hw_status: int
    payload: Optional[str]
    checksum_ok: bool
    raw: bytes

    @property
    def ok(self) -> bool:
        return self.ack and self.status == 0 and self.checksum_ok


def parse_response(frame: bytes) -> Response:
    """Parse an ACK/NACK reply frame produced by the display.

    Detailed status frames (``[FFP...]``) are not handled here -- they do
    not match the reply grammar and will raise ValueError.
    """
    if not (frame.startswith(b"[") and frame.endswith(b"]")):
        raise ValueError(f"not a frame: {frame!r}")
    body = frame[1:-1]

    rx_checksum: Optional[int] = None
    if len(body) >= 3 and body[-3:-2] == b"/":
        try:
            rx_checksum = int(body[-2:], 16)
        except ValueError as e:
            raise ValueError(f"bad checksum hex in {frame!r}") from e
        content = body[:-3]
        checksum_ok = _checksum(b"[" + content) == rx_checksum
    else:
        content = body
        checksum_ok = True

    if len(content) < 7:
        raise ValueError(f"reply too short: {frame!r}")

    unit = chr(content[0])
    ack_ch = chr(content[1])
    if not ("A" <= unit <= "Z") or ack_ch not in (ACK_CHAR, NACK_CHAR):
        raise ValueError(f"not an ack/nack reply: {frame!r}")

    try:
        status = int(content[2:4], 16)
        if chr(content[4]) != ",":
            raise ValueError
        hw_status = int(content[5:7], 16)
    except ValueError as e:
        raise ValueError(f"malformed status fields in {frame!r}") from e

    rest = content[7:]
    payload: Optional[str] = None
    if rest:
        if rest[:1] != b":":
            raise ValueError(f"missing ':' before payload in {frame!r}")
        payload = rest[1:].decode("ascii", errors="replace")

    return Response(
        unit=unit,
        ack=(ack_ch == ACK_CHAR),
        status=status,
        hw_status=hw_status,
        payload=payload,
        checksum_ok=checksum_ok,
        raw=frame,
    )


@dataclass
class Line:
    """One ``!dl`` line definition on a page.

    ``text`` is the literal text payload. It is wrapped in ``<...>``
    when the frame is built unless it already starts with ``*`` (which
    selects a stored text by index, e.g. ``*05``). Use escape_text() to
    sanitise user-supplied strings before constructing a Line.
    """

    line: int
    text: str
    effect: str = "jp"
    justify: str = "L"
    mirror: bool = False

    def render(self) -> str:
        if self.justify not in VALID_JUSTIFY:
            raise ValueError(
                f"justify must be one of {VALID_JUSTIFY}, got {self.justify!r}"
            )
        if len(self.effect) != 2:
            raise ValueError(f"effect must be 2 characters, got {self.effect!r}")
        body = self.text if self.text.startswith("*") else f"<{self.text}>"
        mirror = "+" if self.mirror else ""
        return f"!dl{self.line:02d}{mirror}{self.effect}{self.justify}{body}"


@dataclass
class Graphic:
    """One ``!dg`` sprite placement on a page.

    ``sprite`` is the index of a previously installed sprite (see
    ``!kg`` / ``Display.define_sprite``). ``x``/``y`` are pixel
    coordinates (top-left is 0,0). ``w``/``h`` are the placement size.
    When ``duration`` is set, a ``!dr<NNN>`` animation delay (in graphics
    ticks) is appended after the ``!dg`` -- the standard way to give a
    placed graphic an on-screen dwell.
    """

    sprite: int
    x: int
    y: int
    w: int
    h: int
    duration: Optional[int] = None

    def render(self) -> str:
        if not 0 <= self.sprite <= SPRITE_MAX_INDEX:
            raise ValueError(f"sprite must be 0-{SPRITE_MAX_INDEX}")
        for name, val in (("x", self.x), ("y", self.y), ("w", self.w), ("h", self.h)):
            if val < 0:
                raise ValueError(f"{name} must be non-negative, got {val}")
        body = f"!dg{self.sprite},{self.x},{self.y},{self.w},{self.h},0,0"
        if self.duration is not None:
            if self.duration < 0:
                raise ValueError("duration must be non-negative")
            body += f"!dr{self.duration:03d}"
        return body


@dataclass
class LineMap:
    """Geometry for one line in a ``!Fm`` mapping definition."""

    line: int
    x: int
    y: int
    h: int
    w: int


def build_mapping_command(mapping: int, lines: Iterable[LineMap]) -> str:
    """Build a ``!Fm`` mapping definition command body."""
    if not 0 <= mapping <= 0xF:
        raise ValueError("mapping must be 0-15")
    parts = [f"!Fmm{mapping:X}"]
    for lm in lines:
        parts.append(f"l{lm.line:02d}x{lm.x:03d}y{lm.y:03d}h{lm.h:02d}w{lm.w:02d}")
    parts.append("*")
    return "".join(parts)


def encode_sprite_pixels(
    pixels: Sequence[Sequence[int]],
) -> "tuple[int, int, str]":
    """Encode a 2D pixel array into ``!kg`` wire-format ASCII payload.

    Pixel values use the library convention: 0 transparent, 1 off,
    2 red, 3 green, 4 amber. Rows must all have the same width. For odd
    widths the trailing half-byte's right pixel is encoded as off (wire
    value 0) and ignored by the display.

    Returns ``(width, height, payload)``.
    """
    rows = [list(row) for row in pixels]
    if not rows or not rows[0]:
        raise ValueError("pixels must have at least one row and column")
    width = len(rows[0])
    height = len(rows)
    if any(len(row) != width for row in rows):
        raise ValueError("all rows must have the same width")
    if width * height > SPRITE_MAX_PIXELS:
        raise ValueError(
            f"sprite has {width * height} pixels, exceeds limit of {SPRITE_MAX_PIXELS}"
        )

    out: List[str] = []
    for r, row in enumerate(rows):
        for i in range(0, width, 2):
            try:
                left = _PIXEL_TO_WIRE[row[i]]
            except KeyError as e:
                raise ValueError(
                    f"row {r} col {i}: pixel value must be 0-4, got {row[i]!r}"
                ) from e
            if i + 1 < width:
                try:
                    right = _PIXEL_TO_WIRE[row[i + 1]]
                except KeyError as e:
                    raise ValueError(
                        f"row {r} col {i + 1}: pixel value must be 0-4, got {row[i + 1]!r}"
                    ) from e
            else:
                right = 0  # unused trailing half-byte
            out.append(chr(0x40 | (left << 3) | right))
    return width, height, "".join(out)


def build_sprite_command(
    sprite_id: int, pixels: Sequence[Sequence[int]]
) -> str:
    """Build a ``!kg`` sprite-definition command body."""
    if not 0 <= sprite_id <= SPRITE_MAX_INDEX:
        raise ValueError(f"sprite_id must be 0-{SPRITE_MAX_INDEX}")
    width, height, data = encode_sprite_pixels(pixels)
    return f"!kg{sprite_id:03d},{width:03d},{height:03d}<{data}>"


def load_pixels_from_file(
    path: str,
    chars: Optional[Mapping[str, int]] = None,
) -> List[List[int]]:
    """Read a 2D pixel array from a text file: one character per pixel.

    Each non-empty line is one row. All non-empty rows must have the
    same number of characters. Default character map:
    ``' '`` off, ``'.'`` transparent, ``R/r`` red, ``G/g`` green,
    ``A/a/X/x`` amber. Pass ``chars`` to override or extend.

    Returns a 2D list of pixel values suitable for
    ``build_sprite_command`` / ``Display.define_sprite``.
    """
    table = dict(chars) if chars is not None else dict(DEFAULT_PIXEL_CHARS)
    with open(path, "r", encoding="ascii") as fp:
        text = fp.read()
    rows: List[List[int]] = []
    for lineno, line in enumerate(text.splitlines(), 1):
        if not line:
            continue
        row: List[int] = []
        for col, ch in enumerate(line, 1):
            try:
                row.append(table[ch])
            except KeyError as e:
                raise ValueError(
                    f"{path}:{lineno}:{col}: unknown pixel char {ch!r}"
                ) from e
        rows.append(row)
    if not rows:
        raise ValueError(f"{path}: no pixel rows found")
    width = len(rows[0])
    for i, row in enumerate(rows, 1):
        if len(row) != width:
            raise ValueError(
                f"{path}:row {i}: width {len(row)} != first row width {width}"
            )
    return rows


class Display:
    """Serial client for one DDX display.

    The reply timeout defaults to 5 seconds. Frames are sent with a
    checksum appended by default; some firmware variants tolerate frames
    without one but always include the checksum in their own replies.
    """

    def __init__(
        self,
        port: str,
        address: str = "0A",
        baudrate: int = 19200,
        *,
        checksum: bool = True,
        reply_timeout: float = 5.0,
        logger: Optional[logging.Logger] = None,
    ) -> None:
        if len(address) != 2:
            raise ValueError(f"address must be two chars, got {address!r}")
        self.port = port
        self.address = address
        self.baudrate = baudrate
        self.checksum = checksum
        self.reply_timeout = reply_timeout
        self.log = logger or logging.getLogger(__name__)
        self._serial: Optional[serial.Serial] = None

    def open(self) -> None:
        """Open the serial link and probe the display with ``!?p``.

        Sends ``!?p`` up to three times with 5-second response windows.
        Raises ConnectionError if no ACK arrives within all three tries.
        """
        self._serial = serial.Serial(
            port=self.port,
            baudrate=self.baudrate,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=0.2,
        )
        self._serial.reset_input_buffer()
        self._serial.reset_output_buffer()

        last_error: Optional[Exception] = None
        for attempt in range(1, 4):
            try:
                resp = self.send_frame("!?p", timeout=5.0)
                if resp.ack:
                    self.log.info(
                        "display %s present (attempt %d)", self.address, attempt
                    )
                    return
                last_error = ConnectionError(
                    f"NACK on !?p: status=0x{resp.status:02X}"
                )
            except TimeoutError as e:
                last_error = e
                self.log.warning("!?p attempt %d timed out", attempt)
        self.close()
        raise ConnectionError(
            f"display {self.address} did not respond to !?p"
        ) from last_error

    def close(self) -> None:
        if self._serial is not None:
            self._serial.close()
            self._serial = None

    def __enter__(self) -> "Display":
        self.open()
        return self

    def __exit__(self, exc_type, exc, tb) -> None:
        self.close()

    def send_frame(self, payload: str, timeout: Optional[float] = None) -> Response:
        """Send a command payload, await an ACK/NACK reply, return it.

        ``payload`` is the inside of the frame (e.g. ``"!?p"``). The
        method blocks up to ``timeout`` seconds (default ``reply_timeout``)
        and raises TimeoutError if no reply arrives.
        """
        if self._serial is None:
            raise RuntimeError("serial port not open; call open() first")
        if timeout is None:
            timeout = self.reply_timeout

        frame = build_frame(self.address, payload, checksum=self.checksum)
        self._serial.reset_input_buffer()
        self.log.debug("TX %s", frame.decode("ascii", errors="replace"))
        self._serial.write(frame)
        self._serial.flush()
        return self._read_reply(timeout)

    def _read_reply(self, timeout: float) -> Response:
        assert self._serial is not None
        deadline = time.monotonic() + timeout
        buf = bytearray()
        in_frame = False
        while True:
            remaining = deadline - time.monotonic()
            if remaining <= 0:
                raise TimeoutError("no ACK/NACK within timeout")
            self._serial.timeout = min(remaining, 0.2)
            chunk = self._serial.read(128)
            for b in chunk:
                if not in_frame:
                    if b == 0x5B:  # '['
                        buf.clear()
                        buf.append(b)
                        in_frame = True
                else:
                    buf.append(b)
                    if b == 0x5D:  # ']'
                        in_frame = False
                        frame = bytes(buf)
                        try:
                            resp = parse_response(frame)
                        except ValueError:
                            self.log.debug(
                                "ignored frame: %s",
                                frame.decode("ascii", errors="replace"),
                            )
                            continue
                        if resp.unit != self.address[1]:
                            self.log.debug(
                                "reply from %s ignored (expected %s)",
                                resp.unit,
                                self.address[1],
                            )
                            continue
                        self.log.debug(
                            "RX %s", frame.decode("ascii", errors="replace")
                        )
                        return resp

    def define_page(
        self,
        page: int,
        lines: Iterable[Line] = (),
        mapping: int = 1,
        *,
        graphics: Iterable[Graphic] = (),
        duration: Optional[int] = None,
        carry: Optional[bool] = None,
        timeout: Optional[float] = None,
    ) -> Response:
        """Define one display page in a single ``!ps...`` frame.

        page: 1-based page index, base-10 zero-padded to two digits.
        lines: iterable of Line definitions (``!dl`` commands).
        mapping: line mapping index 0-15 (selected via ``!m<H>``).
        graphics: iterable of Graphic placements; each emits ``!dg``
            and, if ``Graphic.duration`` is set, a following ``!dr``.
        duration: optional ``!dp`` page dwell in seconds.
        carry: optional ``!pcY``/``!pcN`` page-carry flag.

        At least one Line or Graphic must be supplied.
        """
        if not 0 <= mapping <= 0xF:
            raise ValueError("mapping must be 0-15")
        line_list: List[Line] = list(lines)
        graphic_list: List[Graphic] = list(graphics)
        if not line_list and not graphic_list:
            raise ValueError("define_page requires at least one Line or Graphic")
        parts = [f"!ps{page:02d}", f"!m{mapping:X}"]
        if duration is not None:
            if duration < 0:
                raise ValueError("duration must be non-negative")
            parts.append(f"!dp{duration:02d}")
        if carry is not None:
            parts.append("!pcY" if carry else "!pcN")
        parts.extend(ln.render() for ln in line_list)
        parts.extend(g.render() for g in graphic_list)
        return self.send_frame("".join(parts), timeout=timeout)

    def set_playlist(
        self, pages: Iterable[int], timeout: Optional[float] = None
    ) -> Response:
        """Send a ``!pl`` playlist command for the given page indexes."""
        page_list = list(pages)
        if not page_list:
            raise ValueError("playlist must contain at least one page")
        body = ",".join(f"{p:02d}" for p in page_list)
        return self.send_frame(f"!pl{body}", timeout=timeout)

    def clear_playlist(self, timeout: Optional[float] = None) -> Response:
        """Send ``!px`` to clear the current playlist."""
        return self.send_frame("!px", timeout=timeout)

    def delete_page(
        self, page: int, timeout: Optional[float] = None
    ) -> Response:
        """Send ``!pd<NN>`` to delete a page."""
        return self.send_frame(f"!pd{page:02d}", timeout=timeout)

    def define_mapping(
        self,
        mapping: int,
        lines: Iterable[LineMap],
        timeout: Optional[float] = None,
    ) -> Response:
        """Send ``!Fm`` to install a runtime line-mapping definition."""
        return self.send_frame(
            build_mapping_command(mapping, lines), timeout=timeout
        )

    def query_presence(self, timeout: Optional[float] = None) -> Response:
        """Send a plain ``!?p`` presence probe."""
        return self.send_frame("!?p", timeout=timeout)

    def define_sprite(
        self,
        sprite_id: int,
        pixels: Sequence[Sequence[int]],
        timeout: Optional[float] = None,
    ) -> Response:
        """Send ``!kg`` to install a sprite from a 2D pixel array.

        Pixel values: 0 transparent, 1 off, 2 red, 3 green, 4 amber.
        """
        return self.send_frame(
            build_sprite_command(sprite_id, pixels), timeout=timeout
        )

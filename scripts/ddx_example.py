#!/usr/bin/env python3
"""Example: connect to a Daktronics display and show a three-page playlist.

The pages cycle a small "Hello world" message that mirrors the example
in the project README.
"""

import argparse
import logging
import sys

from daktronics_ddx import Display, Line, LineMap


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("serial_port", help="Serial device, e.g. /dev/ttyUSB0")
    p.add_argument(
        "-a", "--address", default="0A", help="Display address (default 0A)"
    )
    p.add_argument(
        "-b", "--baudrate", type=int, default=19200, help="Baud rate (default 19200)"
    )
    p.add_argument(
        "-m", "--mapping", type=int, default=1, help="Line mapping index (default 1)"
    )
    p.add_argument(
        "-d", "--duration", type=int, default=10, help="Page dwell in seconds (default 3)"
    )
    p.add_argument(
        "--no-checksum",
        action="store_true",
        help="Send frames without the optional /HH checksum",
    )
    p.add_argument("-v", "--verbose", action="store_true", help="Log TX/RX frames")
    return p.parse_args()


def show_or_die(label: str, resp) -> None:
    print(
        f"{label}: {'ACK' if resp.ack else 'NACK'} "
        f"status=0x{resp.status:02X} hw=0x{resp.hw_status:02X} "
        f"payload={resp.payload!r}"
    )
    if not resp.ack:
        print(f"command {label} failed; aborting", file=sys.stderr)
        sys.exit(1)


def main() -> int:
    args = parse_args()
    logging.basicConfig(
        level=logging.DEBUG if args.verbose else logging.INFO,
        format="%(asctime)s %(levelname)s %(message)s",
        datefmt="%H:%M:%S",
    )

    display = Display(
        port=args.serial_port,
        address=args.address,
        baudrate=args.baudrate,
        checksum=not args.no_checksum,
    )

    with display:
        show_or_die(
            "protocol 1",
            display.send_frame(
                "!zm1"
                )
        )

        show_or_die(
            "framerate 300",
            display.send_frame(
                "!Fs300"
                )
        )

        show_or_die(
            "effects slowdown",
            display.send_frame(
                "!Fx5"
                )
        )

        show_or_die(
            "disable timeout",
            display.send_frame(
                "!up00"
                )
        )

        show_or_die(
            "page 1",
            display.define_page(
                1,
                [
                    Line(1, "West metro display"),
                    Line(2, "Keilaniemi, Espoo"),
                    Line(3, "Helsinki Hacklab"),
                    Line(4, "By: Depili"),
                    Line(5, "30.06. 2026"),
                    Line(6, "\\t{HH:MM:SS}")
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )

        show_or_die(
            "page 2",
            display.define_page(
                2,
                [
                    Line(1, "Hello world!", effect="jp", justify="C"),
                    Line(2, "Left justify", effect="jp", justify="L"),
                    Line(3, "Center justify", effect="jp", justify="C"),
                    Line(4, "Right justify", effect="jp", justify="R"),
                    Line(5, ""),
                    Line(6, "\\t{HH:MM:SS}")
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )

        show_or_die(
            "page 3",
            display.define_page(
                3,
                [
                    Line(1, "Roll up", effect="ru", justify="C"),
                    Line(2, "Roll down", effect="rd", justify="C"),
                    Line(3, "Sparkle", effect="sp", justify="C"),
                    Line(4, ""),
                    Line(5, ""),
                    Line(6, "\\t{HH:MM:SS}")
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )

        show_or_die(
            "page 4",
            display.define_page(
                4,
                [
                    Line(1, "Open left", effect="ol", justify="C"),
                    Line(2, "Open right", effect="or", justify="C"),
                    Line(3, "Open center", effect="oc", justify="C"),
                    Line(4, "Open ends", effect="oe", justify="C"),
                    Line(5, ""),
                    Line(6, "\\t{HH:MM:SS}")
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )

        show_or_die(
            "page 5",
            display.define_page(
                5,
                [
                    Line(1, "Scroll, spaced", effect="s0", justify="C"),
                    Line(2, "Scroll, no spacing", effect="S0", justify="C"),
                    Line(3, "Constant|scroll, spaced", effect="c0", justify="C"),
                    Line(4, "Constant|scroll, no spacing", effect="C0", justify="C"),
                    Line(5, "Sequence|Text|Line", effect="sq", justify="C"),
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )


        show_or_die("playlist", display.set_playlist([1, 2, 3, 4, 5]))

    print("done")
    return 0


if __name__ == "__main__":
    sys.exit(main())

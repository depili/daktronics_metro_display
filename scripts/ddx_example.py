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
                    Line(1, "L$e4nsimetron n$e4ytt$f6"),
                    Line(2, "Keilaniemi, Espoo"),
                    Line(3, "Helsinki Hacklab"),
                    Line(4, "By: Depili"),
                    Line(5, "30.06. 2026"),
                    Line(6, "\\t{HH:MM:SS}", effect="jp", justify="C")
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
                    Line(6, "\\t{HH:MM:SS}", effect="jp", justify="C")
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
                    Line(6, "\\t{HH:MM:SS}", effect="jp", justify="C")
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
                    Line(6, "\\t{HH:MM:SS}", effect="jp", justify="C")
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
                    Line(1, "Scroll, spaced", effect="S0", justify="C"),
                    Line(2, "Scroll, no spacing", effect="s0", justify="C"),
                    Line(3, "Constant|scroll, spaced", effect="C0", justify="C"),
                    Line(4, "Constant|scroll, no spacing", effect="c0", justify="C"),
                    Line(5, "Sequence|Text|Line", effect="sq", justify="C"),
                    Line(6, "\\t{HH:MM:SS}", effect="jp", justify="C")
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )

        show_or_die(
            "page 6",
            display.define_page(
                6,
                [
                    Line(1, "$20$21$22$23$24$25$26$27$28$29$2a$2b$2c$2d$2e$2f$30$31$32$33$34$35$36$37$38$39$3a$3b$3c$3d$3e$3f$40$41$42$43$44$45$46$47$48$49$4a$4b$4c", effect="S0", justify="L"),
                    Line(2, "$4d$4e$4f$50$51$52$53$54$55$56$57$58$59$5a$5b$5c$5d$5e$5f$60$61$62$63$64$65$66$67$68$69$6a$6b$6c$6d$6e$6f$70$71$72$73$74$75$76$77$78$79", effect="S0", justify="L"),
                    Line(3, "$7a$7b$7c$7d$7e$7f$80$81$82$83$84$85$86$87$88$89$8a$8b$8c$8d$8e$8f$90$91$92$93$94$95$96$97$98$99$9a$9b$9c$9d$9e$9f$a0$a1$a2$a3$a4$a5$a6", effect="S0", justify="L"),
                    Line(4, "$a7$a8$a9$aa$ab$ac$ad$ae$af$b0$b1$b2$b3$b4$b5$b6$b7$b8$b9$ba$bb$bc$bd$be$bf$c0$c1$c2$c3$c4$c5$c6$c7$c8$c9$ca$cb$cc$cd$ce$cf$d0$d1$d2$d3", effect="S0", justify="L"),
                    Line(5, "$d4$d5$d6$d7$d8$d9$da$db$dc$dd$de$df$e0$e1$e2$e3$e4$e5$e6$e7$e8$e9$ea$eb$ec$ed$ee$ef$f0$f1$f2$f3$f4$f5$f6$f7$f8$f9$fa$fb$fc$fd$fe$ff", effect="S0", justify="L"),
                    Line(6, "\\t{HH:MM:SS}", effect="jp", justify="C")
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )



        show_or_die(
            "page 7",
            display.define_page(
                7,
                [
                    Line(1, "\\F1ABCDEFGHIJKLMNabcdefghjiklmn", effect="jp", justify="L"),
                    Line(2, "\\F2ABCDEFGHIJKLabcdefghjikl", effect="jp", justify="L"),
                    Line(3, "\\F3ABCDEFGHIJKLabcdefghjikl", effect="jp", justify="L"),
                    Line(4, "\\sStatic \\fBlink", effect="jp", justify="C"),
                    Line(5, "", effect="jp", justify="L"),
                    Line(6, "\\t{HH:MM:SS}", effect="jp", justify="C")
                ],
                mapping=args.mapping,
                duration=args.duration,
                carry=False,
            ),
        )

        show_or_die("playlist", display.set_playlist([1, 2, 3, 4, 5, 6, 7]))

    print("done")
    return 0


if __name__ == "__main__":
    sys.exit(main())

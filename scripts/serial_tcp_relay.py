#!/usr/bin/env python3
"""Relay bytes between a serial port and a TCP socket, logging both directions.

TX entries log data written to the serial port (received from the TCP client).
RX entries log data read from the serial port (forwarded to the TCP client).
"""

import argparse
import datetime
import logging
import selectors
import socket
import sys

import serial


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Serial<->TCP relay with logging.")
    p.add_argument("serial_port", help="Serial device, e.g. /dev/ttyUSB0")
    p.add_argument(
        "-b", "--baudrate", type=int, default=19200, help="Baud rate (default 19200)"
    )
    p.add_argument(
        "-p", "--tcp-port", type=int, default=4001, help="TCP listen port (default 4001)"
    )
    p.add_argument(
        "-H", "--host", default="0.0.0.0", help="TCP bind address (default 0.0.0.0)"
    )
    p.add_argument(
        "-l", "--log-dir", default=".", help="Directory for log files (default .)"
    )
    return p.parse_args()


def setup_logger(log_dir: str) -> logging.Logger:
    ts = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    log_path = f"{log_dir.rstrip('/')}/serial_tcp_relay_{ts}.log"
    logger = logging.getLogger("relay")
    logger.setLevel(logging.DEBUG)
    fh = logging.FileHandler(log_path)
    fh.setFormatter(
        logging.Formatter(
            fmt="%(asctime)s.%(msecs)03d %(message)s", datefmt="%Y-%m-%d %H:%M:%S"
        )
    )
    sh = logging.StreamHandler(sys.stdout)
    sh.setFormatter(logging.Formatter(fmt="%(asctime)s %(message)s", datefmt="%H:%M:%S"))
    logger.addHandler(fh)
    logger.addHandler(sh)
    logger.info("LOG start -> %s", log_path)
    return logger


def fmt_bytes(data: bytes) -> str:
    return data.decode("ascii", errors="replace")


def serve_client(
    conn: socket.socket, peer: tuple, ser: serial.Serial, log: logging.Logger
) -> None:
    log.info("CONN open %s:%d", peer[0], peer[1])
    conn.setblocking(False)
    sel = selectors.DefaultSelector()
    sel.register(conn, selectors.EVENT_READ, data="tcp")
    sel.register(ser, selectors.EVENT_READ, data="serial")
    try:
        while True:
            for key, _ in sel.select(timeout=None):
                if key.data == "tcp":
                    try:
                        chunk = conn.recv(4096)
                    except (BlockingIOError, InterruptedError):
                        continue
                    if not chunk:
                        log.info("CONN close %s:%d", peer[0], peer[1])
                        return
                    ser.write(chunk)
                    log.info("TX %d %s", len(chunk), fmt_bytes(chunk))
                else:
                    n = ser.in_waiting or 1
                    chunk = ser.read(n)
                    if not chunk:
                        continue
                    try:
                        conn.sendall(chunk)
                    except (BrokenPipeError, ConnectionResetError):
                        log.info("CONN reset %s:%d", peer[0], peer[1])
                        return
                    log.info("RX %d %s", len(chunk), fmt_bytes(chunk))
    finally:
        sel.close()


def main() -> int:
    args = parse_args()
    log = setup_logger(args.log_dir)

    ser = serial.Serial(
        port=args.serial_port,
        baudrate=args.baudrate,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=0,
    )
    log.info("SERIAL open %s @ %d 8N1", args.serial_port, args.baudrate)

    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind((args.host, args.tcp_port))
    srv.listen(1)
    log.info("TCP listen %s:%d", args.host, args.tcp_port)

    try:
        while True:
            conn, peer = srv.accept()
            try:
                ser.reset_input_buffer()
                ser.reset_output_buffer()
                serve_client(conn, peer, ser, log)
            finally:
                conn.close()
    except KeyboardInterrupt:
        log.info("SHUTDOWN keyboard interrupt")
        return 0
    finally:
        srv.close()
        ser.close()


if __name__ == "__main__":
    sys.exit(main())

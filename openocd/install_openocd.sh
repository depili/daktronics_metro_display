#!/usr/bin/env bash
#
# Build and install OpenOCD from source on a Raspberry Pi 3B+, with the
# bcm2835gpio driver enabled so it can drive the Blinkinlabs JTAG Hat
# (which wires JTAG/SWD straight to the Pi's GPIO header).
#
# Usage:  ./install_openocd.sh
# Env:    WORKDIR   where to clone the source (default ~/src)
#         JOBS      parallel make jobs   (default: nproc)
#
set -euo pipefail

WORKDIR="${WORKDIR:-$HOME/src}"
JOBS="${JOBS:-$(nproc)}"

echo "==> Installing build dependencies"
sudo apt-get update
sudo apt-get install -y \
    git build-essential autoconf automake libtool pkg-config \
    libusb-1.0-0-dev libftdi-dev libhidapi-dev libjaylink-dev \
    libtool-bin texinfo

mkdir -p "$WORKDIR"
cd "$WORKDIR"

if [ ! -d openocd ]; then
    echo "==> Cloning OpenOCD"
    git clone --recursive https://github.com/openocd-org/openocd.git
fi

cd openocd
echo "==> Updating sources"
git fetch --tags origin
git checkout master
git pull --ff-only
git submodule update --init --recursive

echo "==> bootstrap / configure"
./bootstrap
./configure \
    --enable-bcm2835gpio \
    --enable-sysfsgpio \
    --enable-ftdi \
    --enable-internal-jimtcl \
    --enable-internal-libjaylink \
    --disable-werror \
    --prefix=/usr/local

echo "==> build (-j$JOBS)"
make -j"$JOBS"

echo "==> install"
sudo make install

# Install udev rules so non-root users can talk to common JTAG/SWD USB
# adapters (not strictly needed for the JTAG Hat's GPIO path, but harmless
# and useful if you ever plug in an FT2232H/ST-Link/etc).
if [ -f contrib/60-openocd.rules ]; then
    sudo install -m 644 contrib/60-openocd.rules /etc/udev/rules.d/
    sudo udevadm control --reload-rules
    sudo udevadm trigger
fi

echo
echo "==> Done."
echo "    openocd: $(command -v openocd)"
openocd --version 2>&1 | head -n2
echo
echo "NOTE: bcm2835gpio mmaps /dev/mem, so OpenOCD must be run as root"
echo "      (sudo openocd ...) when driving the JTAG Hat."

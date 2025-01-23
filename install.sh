#!/bin/bash

INSTALL_DIR="/usr/local/bin"
BUILD_DIR="build"
SRC_DIR="src"
BIN_NAME="coconut"

if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root (use sudo)."
    exit 1
fi

make -s fclean
make -s

cp "$BIN_NAME" "$INSTALL_DIR"

make -s fclean

echo "Installation complete!"
coconut -h

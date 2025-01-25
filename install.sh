#!/bin/bash

INSTALL_DIR="/usr/local/bin"
USER_HOME=$(eval echo ~$SUDO_USER)/.config
BUILD_DIR="build"
SRC_DIR="src"
BIN_NAME="coconut"
CONFIG_NAME="coconut.conf"

if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root (use sudo)."
    exit 1
fi

make -s fclean
make -s

cp "$BIN_NAME" "$INSTALL_DIR"

make -s fclean

mkdir -p $USER_HOME/coconut
cp $CONFIG_NAME $USER_HOME/coconut

echo "Installation complete!"
coconut -h

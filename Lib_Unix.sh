#!/usr/bin/env bash
#
# \file  Lib_Unix.sh
# \brief build static lib for Unix OS
#


# vars
MAKE=
TARGET_DIR=


clear
echo -e "Lib xLib ($OSTYPE) ... "
echo -e

# prepare
if   [ "$OSTYPE" = "linux-gnu" ]; then
    MAKE=make
    TARGET_DIR="./Library/G++_linux/Release"
elif [ "$OSTYPE" = "FreeBSD" ]; then
    MAKE=gmake
    TARGET_DIR="./Library/G++_freebsd/Release"
else
    echo -e "Unknown OS"
    exit 1
fi

mkdir -p $TARGET_DIR


# build
$MAKE all --makefile="./Lib.mk"


# checks
if [ ! -f "$TARGET_DIR/libxlib.a" ]; then
    echo -e "${COL_RED}[FAILED]${COL_NORM}\n"
    exit 1
fi


# finished
echo -e
echo -e "Finished."
echo -e

#!/bin/sh
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
if   [ "$OSTYPE" = "linux-gnu"   ]; then
    MAKE=make
    TARGET_DIR=./Contrib/G++_linux/Release
elif [ "$OSTYPE" = "FreeBSD" ]; then
    MAKE=gmake
    TARGET_DIR=./Contrib/G++_freebsd/Release
else
    echo -e "Unknown OS"
    exit 1
fi

# execute
mkdir -p $TARGET_DIR
$MAKE all -f ./Lib.mk

# finished
echo -e
echo -e "Finished."
echo -e

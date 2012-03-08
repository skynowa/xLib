#!/bin/sh
#
# xxxxxxxx
#


# vars
MAKE=
TARGET_DIR=


clear
echo -e "Build xLib ($OSTYPE) ... "
echo -e

# prepare
if   [ "$OSTYPE" = "Linux"   ]; then
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
$MAKE --directory=$TARGET_DIR --makefile=../../../Tests.mk

# finished
echo -e
echo -e "Finished."
echo -e

#!/bin/sh
#
# \file  Tests_Unix.sh
# \brief build tests for Unix OS
#


# constants
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput setaf 1)"
COL_GREEN="$(tput setaf 2)"

# vars
MAKE=
TARGET_DIR=


# prepare
clear

echo -e
echo -e 
echo -e ${COL_GREEN}"Prepare..."($OSTYPE)${COL_NORM}
echo -e

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

mkdir -p $TARGET_DIR


# build
echo -e
echo -e
echo -e ${COL_GREEN}"Build..."${COL_NORM}
echo -e

$MAKE --directory=$TARGET_DIR --makefile=../../../Tests.mk


# finished
echo -e
echo -e
echo -e ${COL_GREEN}"Finished."${COL_NORM}
echo -e

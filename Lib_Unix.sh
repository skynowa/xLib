#!/usr/bin/env bash
#
# \file  Lib_Unix.sh
# \brief build static lib for Unix OS
#


# constants
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput bold; tput setaf 1)"
COL_GREEN="$(tput bold; tput setaf 2)"
COL_YELLOW_BOLD="$(tput bold; tput setaf 3)"


# vars
MAKE=
TARGET_DIR=


clear

echo -e
echo -e $COL_GREEN"Lib xLib ($OSTYPE) ... "$COL_NORM
echo -e

# prepare
echo -e
echo -e $COL_GREEN"Prepare...($OSTYPE)"$COL_NORM
echo -e

if   [ "$OSTYPE" = "linux-gnu" ]; then
    MAKE=make
    TARGET_DIR="./Build/Libs/G++_linux/Release"
elif [ "$OSTYPE" = "FreeBSD" ]; then
    MAKE=gmake
    TARGET_DIR="./Build/Libs/G++_freebsd/Release"
else
    echo -e "Unknown OS"
    exit 1
fi

mkdir -p $TARGET_DIR


# build
echo -e
echo -e ${COL_GREEN}"Build..."${COL_NORM}
echo -e

# TODO: --directory=$TARGET_DIR
$MAKE all --makefile="./Lib.mk"


# finished
echo -e
echo -e ${COL_GREEN}"Finished."${COL_NORM}
echo -e

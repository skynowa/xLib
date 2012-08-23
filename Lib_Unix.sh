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

# bash colors
COL_NORM='\e[0m'            # Text Reset
Black='\e[0;30m'            # Black
COL_RED='\e[0;31m'          # Red
COL_GREEN='\e[0;32m'        # Green
COL_YELLOW_BOLD='\e[0;33m'  # Yellow
Blue='\e[0;34m'             # Blue
Purple='\e[0;35m'           # Purple
Cyan='\e[0;36m'             # Cyan
White='\e[0;37m'            # White

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

if   [ `uname` = "Linux" ]; then
    MAKE=make
    TARGET_DIR="./Build/Libs/G++_linux/Release"
elif [ `uname` = "FreeBSD" ]; then
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

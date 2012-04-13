#!/bin/bash
#
# \file  Tests_Unix.sh
# \brief build tests for Unix OS
#


# constants
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput bold; tput setaf 1)"
COL_GREEN="$(tput bold; tput setaf 2)"
COL_YELLOW_BOLD="$(tput bold; tput setaf 3)"

# vars
MAKE=
TARGET_DIR=


# prepare
clear

echo -e
echo -e
echo -e $COL_GREEN"Prepare..."\($OSTYPE\) $COL_NORM
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
echo ${COL_GREEN}"Build..."${COL_NORM}

$MAKE --directory=$TARGET_DIR --makefile=../../../Tests.mk > ./$HOSTNAME.out 2> ./$HOSTNAME.err

# output
if [ $? != 0 ]; then
    echo -e 
    echo -e "===================================================================================================="
    echo -e "${COL_RED}Errors:${COL_NORM}\n"
    cat ./$HOSTNAME.err
    echo -e "===================================================================================================="

    set $?=1
else
    if [ -f "$TARGET_DIR/xlib_r" ]; then
        echo -e "${COL_RED}[FAILED]${COL_NORM}\n"
        exit 1
    fi

    set $?=0
fi

echo -e 
echo -e "===================================================================================================="
echo -e "${COL_YELLOW_BOLD}Warnings:${COL_NORM}\n"
cat ./$HOSTNAME.err | grep warning
echo -e "===================================================================================================="


# finished
echo -e
echo -e
echo -e ${COL_GREEN}"Finished."${COL_NORM}
echo -e

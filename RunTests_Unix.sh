#!/usr/bin/env bash
#
# \file  RunTests_Unix.sh
# \brief run tests for Unix OS
#


# constants
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput bold; tput setaf 1)"
COL_GREEN="$(tput bold; tput setaf 2)"
COL_YELLOW_BOLD="$(tput bold; tput setaf 3)"


# vars
TARGET_DIR=


clear

echo -e
echo -e $COL_GREEN"Test xLib ($OSTYPE) ... "$COL_NORM
echo -e


# prepare
echo -e
echo -e $COL_GREEN"Prepare...($OSTYPE)"$COL_NORM
echo -e

if   [ "$OSTYPE" = "linux-gnu" ]; then
    TARGET_DIR="./Contrib/G++_linux/Release"
elif [ "$OSTYPE" = "FreeBSD" ]; then
    TARGET_DIR="./Contrib/G++_freebsd/Release"
else
    echo -e "Unknown OS"
    exit 1
fi


# run
echo -e
echo ${COL_GREEN}"Build and run..."${COL_NORM}
echo -e

./Tests_Unix.sh
$TARGET_DIR/xlib_r 1 1 1 1


# finished
echo -e
echo -e ${COL_GREEN}"Finished."${COL_NORM}
echo -e

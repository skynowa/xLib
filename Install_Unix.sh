#!/usr/bin/env bash
#
# \file  Install_Unix.sh
# \brief install xLib for Unix OS
#


# constants
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput bold; tput setaf 1)"
COL_GREEN="$(tput bold; tput setaf 2)"
COL_YELLOW_BOLD="$(tput bold; tput setaf 3)"


# vars
MAKE=


clear

echo -e
echo -e $COL_GREEN"Install xLib ($OSTYPE) ... "$COL_NORM
echo -e


# prepare
echo -e
echo -e $COL_GREEN"Prepare...($OSTYPE)"$COL_NORM
echo -e

if   [ `uname` = "Linux" ]; then
    MAKE=make
elif [ `uname` = "FreeBSD" ]; then
    MAKE=gmake
else
    echo -e "Unknown OS"
    exit 1
fi


# install
echo -e
echo -e ${COL_GREEN}"Install..."${COL_NORM}
echo -e

$MAKE install --makefile="./Lib.mk"


# finished
echo -e
echo -e ${COL_GREEN}"Finished."${COL_NORM}
echo -e

#!/usr/bin/env bash
#
# \file  LibsInstall_Unix.sh
# \brief install libs for Unix OS
#


# bash colors
# COL_NORM='\e[0m'        # Text Reset
# COL_BLACK='\e[0;30m'    # Black
# COL_RED='\e[0;31m'      # Red
# COL_GREEN='\e[0;32m'    # Green
# COL_YELLOW='\e[0;33m'   # Yellow
# COL_BLUE='\e[0;34m'     # Blue
# COL_PURPULE='\e[0;35m'  # Purple
# COL_CYAN='\e[0;36m'     # Cyan
# COL_WHITE='\e[0;37m'    # White


# constants


# vars
MAKE=


echo -e
echo -e $COL_GREEN"Install xLib ($OSTYPE) ... "$COL_NORM
echo -e


# prepare
echo -e
echo -e $COL_GREEN"Prepare..."$COL_NORM
echo -e

if   [ `uname` = "Linux" ]; then
    MAKE=make
elif [ `uname` = "FreeBSD" ]; then
    MAKE=gmake
else
    echo -e "Unknown OS"
    exit 1
fi

# override MAKE by colormake
if [ ! -z "`which colormake`" ]; then
    MAKE=colormake
fi


# execute
echo -e
echo -e ${COL_GREEN}"Install libs..."${COL_NORM}
echo -e

$MAKE install --makefile="./Lib.mk"


# finished
echo -e
echo -e ${COL_GREEN}"Finished."${COL_NORM}
echo -e

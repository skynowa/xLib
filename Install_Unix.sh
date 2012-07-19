#!/usr/bin/env bash
#
# \file  Install_Unix.sh
# \brief install xLib for Unix OS
#


# vars
MAKE=


clear
echo -e "Install xLib ($OSTYPE) ... "
echo -e


# prepare
if   [ "$OSTYPE" = "linux-gnu"   ]; then
    MAKE=make
elif [ "$OSTYPE" = "FreeBSD" ]; then
    MAKE=gmake
else
    echo -e "Unknown OS"
    exit 1
fi


# install
$MAKE install -f ./Lib.mk


# finished
echo -e
echo -e "Finished."
echo -e

#!/bin/bash
#
# \file  RunTests_Unix.sh
# \brief run tests for Unix OS
#


# vars
TARGET_DIR=


clear
echo -e "Test xLib ($OSTYPE) ... "
echo -e

# prepare
if   [ "$OSTYPE" = "linux-gnu"   ]; then
    TARGET_DIR=./Contrib/G++_linux/Release
elif [ "$OSTYPE" = "FreeBSD" ]; then
    TARGET_DIR=./Contrib/G++_freebsd/Release
else
    echo -e "Unknown OS"
    exit 1
fi

# execute
./Tests_Unix.sh
$TARGET_DIR/xlib_r 1 1 1 1

# finished
echo -e
echo -e "Finished."
echo -e

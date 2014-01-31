#!/usr/bin/env bash
#
# \file  makefile_gcc.sh
# \brief build tests
#


# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_`basename -s .sh $0`"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Unix Makefiles" $DIR_XLIB
# make -j4 VERBOSE=1

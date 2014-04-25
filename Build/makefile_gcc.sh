#!/usr/bin/env bash
#
# \file  makefile_gcc.sh
# \brief build tests
#


# vars
# export CC="gcc"
# export CXX="g++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_makefile_gcc"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Unix Makefiles" $DIR_XLIB
# make -j4 VERBOSE=1

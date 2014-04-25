#!/usr/bin/env bash
#
# \file  makefile_clang.sh
# \brief build tests
#


# vars
export CC="clang"
export CXX="clang++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_makefile_clang"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Unix Makefiles" $DIR_XLIB
# make -j4 VERBOSE=1

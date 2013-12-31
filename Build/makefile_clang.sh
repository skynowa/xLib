#!/usr/bin/env bash
#
# \file  makefile_clang.sh
# \brief build tests
#


# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_`basename -s .sh $0`"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++" -G"Unix Makefiles" $DIR_XLIB
make -j4 VERBOSE=1

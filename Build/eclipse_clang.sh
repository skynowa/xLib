#!/usr/bin/env bash
#
# \file  eclipse_clang.sh
# \brief build tests
#


# vars
export CC="clang"
export CXX="clang++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_eclipse_clang"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Eclipse CDT4 - Unix Makefiles" $DIR_XLIB
# make -j4 VERBOSE=1

#!/usr/bin/env bash
#
# \file  eclipse_clang.sh
# \brief build tests
#


# vars
set CC="clang"
set CXX="clang++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_`basename -s .sh $0`"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Eclipse CDT4 - Unix Makefiles" $DIR_XLIB
make -j4 VERBOSE=1

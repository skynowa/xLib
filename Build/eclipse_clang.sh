#!/usr/bin/env bash
#
# \file  eclipse_clang.sh
# \brief build tests
#


# vars
DIR_BUILD="./xLib_`basename -s .sh $0`"


# build
cmake -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++" -G"Eclipse CDT4 - Unix Makefiles" "../.."

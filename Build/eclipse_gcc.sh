#!/usr/bin/env bash
#
# \file  eclipse_gcc.sh
# \brief build tests
#


# vars
DIR_BUILD="./xLib_`basename -s .sh $0`"


# build
cd ../..
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake VERBOSE=1 -G"Eclipse CDT4 - Unix Makefiles" "../xLib"
make

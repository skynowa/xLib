#!/usr/bin/env bash
#
# \file  build_unix.sh
# \brief build tests
#


# vars
DIR_BUILD="./xLib_Build_Unix"


# build
cd ../..
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake VERBOSE=1 ../xLib -G"Eclipse CDT4 - Unix Makefiles"
make

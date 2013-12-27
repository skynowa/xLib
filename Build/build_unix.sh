#!/usr/bin/env bash
#
# \file  build_unix.sh
# \brief build tests
#


cd ../..
mkdir ./xLib_Build_Unix
cd ./xLib_Build_Unix
cmake VERBOSE=1 ../xLib -G"Eclipse CDT4 - Unix Makefiles"
make

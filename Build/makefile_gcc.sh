#!/usr/bin/env bash
#
# \file  makefile_gcc.sh
# \brief build tests
#


# vars
DIR_BUILD="./xLib_`basename -s .sh $0`"


# build
cmake -G"Unix Makefiles" "../.."

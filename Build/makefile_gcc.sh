#!/usr/bin/env bash
#
# \file  makefile_gcc.sh
# \brief build tests
#


# vars
DIR_BUILD="./xLib_Build_Unix"


# build
cmake -G"Unix Makefiles" "../.."

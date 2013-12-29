#!/usr/bin/env bash
#
# \file  eclipse_gcc.sh
# \brief build tests
#


# vars
DIR_BUILD="./xLib_Build_Unix"


# build
cmake -G"Eclipse CDT4 - Unix Makefiles" "../.."

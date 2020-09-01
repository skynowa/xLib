#!/usr/bin/env bash
#
# \file  eclipse.sh
# \brief build project
#


# vars
DIR_BUILD="../../xLib_makefile"

cd $DIR_BUILD

cmake --build . -- -j16

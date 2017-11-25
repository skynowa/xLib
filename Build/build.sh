#!/usr/bin/env bash
#
# \file  build.sh
# \brief build project
#


# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_eclipse"

mkdir -p $DIR_BUILD
cd $DIR_BUILD

cmake --build .

#!/usr/bin/env bash
#
# \file  makefile.sh
# \brief build project
#

set -ex

# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_eclipse"

mkdir -p $DIR_BUILD
cd $DIR_BUILD

cmake --build .

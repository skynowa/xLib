#!/usr/bin/env bash
#
# \file  template_generate.sh
# \brief Generate class template(s)
#


# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_build"

mkdir -p $DIR_BUILD
cd $DIR_BUILD

cmake --build . --target template

#!/usr/bin/env bash
#
# \file  generate_template.sh
# \brief generate template
#


# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_eclipse"

mkdir -p $DIR_BUILD
cd $DIR_BUILD

make template


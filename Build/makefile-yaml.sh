#!/usr/bin/env bash
#
# \file  makefile.sh
# \brief build project
#

set -ex

# vars
DIR_XLIB="../xlib"
DIR_BUILD="../../xLib_makefile"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD

cmake \
	-G"Unix Makefiles" \
	$DIR_XLIB

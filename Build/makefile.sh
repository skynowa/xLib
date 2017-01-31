#!/usr/bin/env bash
#
# \file  makefile.sh
# \brief build project
#


# vars
export CC="gcc"
export CXX="g++"
# export CC="clang"
# export CXX="clang++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_makefile"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake \
	-G"Unix Makefiles" \
	$DIR_XLIB

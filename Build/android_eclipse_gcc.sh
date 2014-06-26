#!/usr/bin/env bash
#
# \file  android_makefile_gcc.sh
# \brief build tests
#


# vars
# export CC="gcc"
# export CXX="g++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_android_eclipse_gcc"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$DIR_XLIB/CMake/android.toolchain.cmake $DIR_XLIB
# make -j4 VERBOSE=1

#!/usr/bin/env bash
#
# \file  android_makefile_gcc.sh
# \brief build tests
#


# vars
# export CC="gcc"
# export CXX="g++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_android_makefile_gcc"


# build
export ANDROID_NDK=/opt/Libs/Android/NDK

mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$DIR_XLIB/CMake/android.toolchain.cmake -DANDROID_API_LEVEL=19 $DIR_XLIB
# make -j4 VERBOSE=1

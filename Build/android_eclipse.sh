#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_android_eclipse"
ECLIPSE_VERSION="4.17" # 2020-09

# prepare
mkdir -p $DIR_BUILD
cd $DIR_BUILD

cmake \
	-G"Eclipse CDT4 - Unix Makefiles" \
	-D_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	-DCMAKE_TOOLCHAIN_FILE=${DIR_PROJECT}/CMake/android.toolchain.cmake \
	$DIR_PROJECT

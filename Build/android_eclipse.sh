#!/usr/bin/env bash
#
# \file  android_eclipse.sh
# \brief CMake configure project
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"
ECLIPSE_VERSION="4.17" # 2020-09
GENERATOR="Eclipse CDT4 - Unix Makefiles"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
cmake \
	-G"${GENERATOR}" \
	-D_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	-DCMAKE_TOOLCHAIN_FILE=${DIR_PROJECT}/CMake/android.toolchain.cmake \
	${DIR_PROJECT}

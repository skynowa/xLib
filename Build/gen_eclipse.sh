#!/usr/bin/env bash
#
# \file  gen_eclipse.sh
# \brief CMake generate project
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"

GENERATOR="Eclipse CDT4 - Unix Makefiles"
ECLIPSE_VERSION="4.22.0"
BUILD_TYPE=Release

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# generate
cmake \
	-G "${GENERATOR}" -D CMAKE_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	-D CMAKE_BUILD_TYPE=${BUILD_TYPE} \
	${DIR_PROJECT}

#!/usr/bin/env bash
#
# \file  gen_msvc_2019.sh
# \brief CMake generate project
#
# https://cmake.org/cmake/help/git-stage/generator/Visual%20Studio%2016%202019.html
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"

GENERATOR="Visual Studio 16 2019"
ARCH=x64 # Win32

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# generate
cmake \
	-G "${GENERATOR}" -A ${ARCH} \
	-D CMAKE_BUILD_TYPE=Release \
	${DIR_PROJECT}

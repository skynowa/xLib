#!/usr/bin/env bash
#
# \file  msvc_2019.sh
# \brief CMake configure project
#
# https://cmake.org/cmake/help/git-stage/generator/Visual%20Studio%2016%202019.html
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"
GENERATOR="Visual Studio 16 2019"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
cmake \
	-G"${GENERATOR}" \
	-A Win32 \	# x64;Win32
	${DIR_PROJECT}

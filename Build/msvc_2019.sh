#!/usr/bin/env bash
#
# \file  msvc_2019.sh
# \brief CMake configure project
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
	-A x64 \
	${DIR_PROJECT}

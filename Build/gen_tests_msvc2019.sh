#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib_tests"
DIR_PROJECT="../xLib/Tests"
DIR_BUILD="../../${PROJECT_NAME}_build"

GENERATOR="Visual Studio 16 2019"
ARCH=x64 # Win32

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# generate
cmake \
	# -G "${GENERATOR}" -A ${ARCH} \
	-G Ninja \
	-D CMAKE_BUILD_TYPE=Release \
	${DIR_PROJECT}

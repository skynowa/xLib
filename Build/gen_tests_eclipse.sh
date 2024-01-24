#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib_tests"
DIR_PROJECT="../xLib/Tests"
DIR_BUILD="../../${PROJECT_NAME}_build"

GENERATOR="Eclipse CDT4 - Unix Makefiles"
ECLIPSE_VERSION="4.30"
BUILD_TYPE=Release

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# generate
cmake \
	-G "${GENERATOR}" -D CMAKE_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	-D CMAKE_BUILD_TYPE=${BUILD_TYPE} \
	${DIR_PROJECT}

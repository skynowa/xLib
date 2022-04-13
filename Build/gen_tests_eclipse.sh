#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib_tests"
DIR_PROJECT="../xLib/Tests"
DIR_BUILD="../../${PROJECT_NAME}_build"

GENERATOR="Eclipse CDT4 - Unix Makefiles"
ECLIPSE_VERSION="4.17" # 2020-09

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# generate
cmake \
	-G "${GENERATOR}" -D _ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	${DIR_PROJECT}

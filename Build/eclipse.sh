#!/usr/bin/env bash
#
# \file  eclipse.sh
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
	-G "${GENERATOR}" \
	-D _ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	$DIR_PROJECT

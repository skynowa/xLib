#!/usr/bin/env bash
#
# \file  gen_eclipse.sh
# \brief CMake generate project
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"

ECLIPSE_VERSION="4.22.0"
GENERATOR="Eclipse CDT4 - Unix Makefiles"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# generate
cmake \
	-G "${GENERATOR}" -DCMAKE_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	${DIR_PROJECT}

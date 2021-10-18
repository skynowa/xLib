#!/usr/bin/env bash


set -ex

# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"
ECLIPSE_VERSION="4.17" # 2020-09
GENERATOR="Unix Makefiles"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
cmake \
	-G"${GENERATOR}" \
	-D_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
	${DIR_PROJECT}

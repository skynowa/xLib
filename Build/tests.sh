#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}/Tests"
DIR_BUILD="../../${PROJECT_NAME}_tests"
### GENERATOR="Eclipse CDT4 - Unix Makefiles"
GENERATOR="Visual Studio 16 2019"
ARCH=Win32	### x64
ECLIPSE_VERSION="4.17" # 2020-09

JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

### Configure
# cmake \
# 	-G"${GENERATOR}" \
# 	-D_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
# 	$DIR_PROJECT
cmake \
	-G"${GENERATOR}" \
	-A ${ARCH} \
	${DIR_PROJECT}

# Build
cmake --build . ### -- -j${JOBS_NUM}

# Run
ctest -C Debug -j${JOBS_NUM} --output-on-failure

#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib_tests"
DIR_PROJECT="../xLib/Tests"
DIR_BUILD="../../${PROJECT_NAME}_build"

### GENERATOR="Eclipse CDT4 - Unix Makefiles"
### ECLIPSE_VERSION="4.17" # 2020-09
GENERATOR="Visual Studio 16 2019"
ARCH=x64 # Win32

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

### Configure
# cmake \
# 	-G "${GENERATOR}" \
# 	-D_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
# 	${DIR_PROJECT}
cmake \
	-G "${GENERATOR}" \
	-A ${ARCH} \
	-D CMAKE_BUILD_TYPE=Release \
	${DIR_PROJECT}

# Build
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

cmake --build . --target ALL_BUILD --config Release --verbose

# Run
### ctest -C Debug --output-on-failure

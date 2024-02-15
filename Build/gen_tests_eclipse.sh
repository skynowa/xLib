#!/usr/bin/env bash
#
# \file  gen_tests_eclipse.sh
# \brief CMake generate tests
#

# vars
PROJECT_NAME="xLib_tests"
PROJECT_DIR="../xLib/Tests"
BUILD_DIR="../../${PROJECT_NAME}_build"

GENERATOR="Eclipse CDT4 - Unix Makefiles"
ECLIPSE_VERSION=$(eclipse_version.sh)
BUILD_TYPE=Release

# prepare
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# generate
cmake \
    -G "${GENERATOR}" \
    -D CMAKE_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
    -D CMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
    -D CMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -Wno-dev \
    "${PROJECT_DIR}"

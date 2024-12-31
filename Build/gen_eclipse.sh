#!/usr/bin/env bash
#
# \file  gen_eclipse.sh
# \brief CMake generate project
#

set -ax

# vars
PROJECT_PATH=$(realpath ../)
PROJECT_NAME=$(basename "$PROJECT_PATH")
PROJECT_DIR="${PROJECT_PATH}"
BUILD_DIR="../../${PROJECT_NAME}_build"

GENERATOR="Eclipse CDT4 - Unix Makefiles"
ECLIPSE_VERSION=$(eclipse_version.sh)
BUILD_TYPE=Release

# prepare
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

# generate
cmake \
    -G "${GENERATOR}" \
    -D CMAKE_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
    -D CMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
    -D CMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -D CMAKE_CXX_STANDARD=20 -DCMAKE_CXX_STANDARD_REQUIRED=ON \
    -Wno-dev \
    "${PROJECT_DIR}"

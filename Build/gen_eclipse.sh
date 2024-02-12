#!/usr/bin/env bash
#
# \file  gen_eclipse.sh
# \brief CMake generate project
#


# vars
PROJECT_PATH=$(realpath .)
PROJECT_NAME=$(basename "$PROJECT_PATH")
PROJECT_DIR="${PROJECT_PATH}"
BUILD_DIR="../../${PROJECT_NAME}_build"

GENERATOR="Eclipse CDT4 - Unix Makefiles"
ECLIPSE_VERSION="4.25"
BUILD_TYPE=Release

# prepare
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}" || exit

# generate
cmake \
    -G "${GENERATOR}" \
    -D CMAKE_ECLIPSE_VERSION=${ECLIPSE_VERSION} \
    -D CMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
    -D CMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -Wno-dev \
    "${PROJECT_DIR}"

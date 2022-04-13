#!/usr/bin/env bash
#
# \file  gen_msvc_2019.sh
# \brief CMake generate project
#
# https://cmake.org/cmake/help/git-stage/generator/Visual%20Studio%2016%202019.html
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"

GENERATOR="Visual Studio 16 2019"
ARCH=x64 # Win32

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# [Win]
VS_INSTALL_DIR="C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise"
VCVARS_BAT="${VS_INSTALL_DIR}/VC/Auxiliary/Build/vcvars64.bat"

cmd.exe /V /C @ "${VCVARS_BAT}" "&&" "$@"

# generate
cmake \
	-G Ninja -D CMAKE_USE_TOOLCHAIN="MSVC" \
	-D CMAKE_BUILD_TYPE=Release \
	${DIR_PROJECT}

#-G "${GENERATOR}" -A ${ARCH} \

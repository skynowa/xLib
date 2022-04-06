#!/usr/bin/env bash
#
# \file  msvc_2022.sh
# \brief CMake configure project
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"
GENERATOR="Visual Studio 17 2022"
ARCH=Win32	### x64

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
cmake \
	-G"${GENERATOR}" \
	-A ${ARCH} \
	${DIR_PROJECT}

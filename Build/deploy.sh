#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib"
DIR_BUILD="../../${PROJECT_NAME}_build"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
SUDO="sudo"

if [[ "${OSTYPE}" == "win"* || "${OSTYPE}" == "msys"* ]]; then
	SUDO=""
fi

${SUDO} cmake --build . --target install --config Release

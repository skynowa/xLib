#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib"
DIR_BUILD="../../${PROJECT_NAME}_build"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
SUDO="sudo"
PARAM_QUIET="-q" # Make

if [[ "${OSTYPE}" == "win"* || "${OSTYPE}" == "msys"* ]]; then
	SUDO=""
	PARAM_QUIET="/verbosity:minimal" # MSBuild
fi

${SUDO} cmake --build . --target install --config Release -- ${PARAM_QUIET}

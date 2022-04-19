#!/usr/bin/env bash
#


# set -ex

# vars
PROJECT_NAME="xLib"
DIR_BUILD="../../${PROJECT_NAME}_build"
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
UNAME=$(uname)

if   [[ "$UNAME" == CYGWIN* || "$UNAME" == MINGW* ]] ; then
	echo "OS: Windows"
	## cmake --build . --target ALL_BUILD --config Release --parallel ${JOBS_NUM}
	cmake --build . --target ${PROJECT_NAME} --config Release --parallel ${JOBS_NUM}
elif [ "$UNAME" == "Linux" ] ; then
	echo "OS: Linux"
	cmake --build . --target ${PROJECT_NAME} --config Release -- -j${JOBS_NUM}
elif [ "$UNAME" == "Darwin" ] ; then
	echo "OS: Darwin"
	cmake --build . --target ${PROJECT_NAME} --config Release -- -j${JOBS_NUM}
fi

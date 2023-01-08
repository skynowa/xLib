#!/usr/bin/env bash


set -ex

# Params
UNIT_TEST_NAME=$*

# vars
PROJECT_NAME="xLib_tests"
DIR_PROJECT="../xLib/Tests"
DIR_BUILD="../../${PROJECT_NAME}_build"
JOBS_NUM=1 # $(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"
echo "OS ver: $(uname -a)"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
UNAME=$(uname)

# Single test
if [[ "$UNIT_TEST_NAME" != "" ]]; then
	cmake --build . --target "Test_${UNIT_TEST_NAME}"

	ctest -R "^Test_${UNIT_TEST_NAME}$"

	exit 0
fi

# All tests
if   [[ "$UNAME" == CYGWIN* || "$UNAME" == MINGW* ]] ; then
	echo "OS: Windows"
	cmake --build . --target ALL_BUILD --config Release --parallel ${JOBS_NUM}
elif [ "$UNAME" == "Linux" ] ; then
	echo "OS: Linux"
	cmake --build . --config Release -- -j${JOBS_NUM}
elif [ "$UNAME" == "Darwin" ] ; then
	echo "OS: Darwin"
	cmake --build . --config Release -- -j${JOBS_NUM}
fi

# Run
ctest -C Debug --output-on-failure
#--------------------------------------------------------------------------------------------------

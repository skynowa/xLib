#!/usr/bin/env bash


# set -ex

# vars
PROJECT_NAME="xLib_tests"
DIR_PROJECT="../xLib/Tests"
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
	cmake --build . --target ALL_BUILD --config Release --parallel ${JOBS_NUM} # --verbose
elif [ "$UNAME" == "Linux" ] ; then
	echo "OS: Linux"
	# cmake --build . --target xLib_tests --config Release -- -j${JOBS_NUM}
	cmake --build . --config Release -- -j${JOBS_NUM}
elif [ "$UNAME" == "Darwin" ] ; then
	echo "OS: Darwin"
	cmake --build . --target xLib_tests --config Release -- -j${JOBS_NUM}
fi

# Run
### ctest -C Debug --output-on-failure

echo "xLib_tests_build"
ls -ls "D:/a/xLib/xLib/xLib_tests_build"

echo "Release"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/Release"

echo "CMakeFiles"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/CMakeFiles"

echo "x64"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/x64"

echo ""
objdump -f "Test_Xml.obj"

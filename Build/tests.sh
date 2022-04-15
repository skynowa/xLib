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

echo -e "\nxLib_tests_build"
ls -ls "D:/a/xLib/xLib/xLib_tests_build"

echo -e "\nRelease"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/Release"

echo -e "\nTest_Xml.dir/Release"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/Test_Xml.dir/Release"

echo -e "\nCMakeFiles"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/CMakeFiles"

echo -e "\nx64/Release"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/x64/Release"

echo -e "\nCMakeError.log"
cat "D:/a/xLib/xLib/xLib_tests_build/CMakeFiles/CMakeError.log"

echo -e "\n"
objdump -f "D:/a/xLib/xLib/xLib_tests_build/Test_Xml.dir/Release/Test_Xml.obj"

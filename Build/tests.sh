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
ctest -C Debug --output-on-failure

#--------------------------------------------------------------------------------------------------
# echo ""
# file "C:/Program Files/xLib/lib/xLib.lib"
# file "C:/Program Files/xLib/lib/libxml2_a.lib"
# file "C:/Program Files/xLib/lib/libssl.lib"
# file "C:/Program Files/xLib/lib/libcrypto.lib"
# file "C:/Program Files/xLib/lib/libcurl.lib"
# file "C:/Program Files/xLib/lib/mysqlclient.lib"
# file "C:/Program Files/xLib/lib/libssh2.lib"
# file "C:/Program Files/xLib/lib/iconv.lib"

# echo ""
# objdump -f "C:/Program Files/xLib/lib/xLib.lib"
# objdump -f "C:/Program Files/xLib/lib/libxml2_a.lib"
# objdump -f "C:/Program Files/xLib/lib/libssl.lib"
# objdump -f "C:/Program Files/xLib/lib/libcrypto.lib"
# objdump -f "C:/Program Files/xLib/lib/libcurl.lib"
# objdump -f "C:/Program Files/xLib/lib/mysqlclient.lib"
# objdump -f "C:/Program Files/xLib/lib/libssh2.lib"
# objdump -f "C:/Program Files/xLib/lib/iconv.lib"
#--------------------------------------------------------------------------------------------------
echo -e "\n:::::::::: xLib ::::::::::"
ls -ls "D:/a/xLib/xLib"

# cat conanbuildinfo.cmake
# cat conan_paths.cmake

echo -e "\n:::::::::: xLib_tests_build / Bin ::::::::::"
ls -ls "D:/a/xLib/xLib/xLib_tests_build/bin"

# echo -e "\n:::::::::: CMakeError.log ::::::::::"
# cat "D:/a/xLib/xLib/xLib_tests_build/CMakeFiles/CMakeError.log"
#--------------------------------------------------------------------------------------------------

#!/usr/bin/env bash
#
# \file  SystemInfo.sh
# \brief system info about OS
#


# constants
COL_RESET="$(tput sgr0)"
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput bold; tput setaf 1)"
COL_GREEN="$(tput bold; tput setaf 2)"
COL_YELLOW_BOLD="$(tput bold; tput setaf 3)"


# vars
OS_INFO=`uname -a`
OS_TYPE=$OSTYPE
OS_BIT=`getconf LONG_BIT`
OS_ARCH=`uname -m`
SHELL=$SHELL
PYTHON=`python --version 2>&1`
GCC_MACHINE=`g++ -dumpmachine`
GCC_INFO=`g++ --version | head -n 1`
CLANG_INFO=`clang --version | head -n 1`
BINUTILS_INFO=`ld --version | head -n 1`
GDB=`gdb --version | head -n 1`
MAKE=`make --version | head -n 1`
CMAKE=`cmake --version | head -n 1`
PATCH=`patch --version | head -n 1`

CLANG_TIDY=`clang-tidy --version | head -2 | tail -1`
CPPCHECK=`cppcheck --version | head -n 1`
DOXYGEN=`doxygen --version | head -n 1`

GLIBC_INFO=`ldd --version | head -n 1`
LIB_BOOST=`dpkg -s libboost-dev | grep 'Version'`
LIB_CURL=`curl --version | head -n 1`

GIT=`git --version`


# print info
echo ""
echo "************************************************************"
echo "$COL_GREEN Development info $COL_RESET"
echo ""
echo "$COL_GREEN OS: $COL_RESET"
echo " OS:              $OS_INFO"
echo " OS type:         $OS_TYPE"
echo " OS bit:          $OS_BIT ($OS_ARCH)"
echo ""
echo "$COL_GREEN Shells: $COL_RESET"
echo " Shell:           $SHELL"
echo " Python:          $PYTHON"
echo ""
echo "$COL_GREEN Build tools: $COL_RESET"
echo " Machine:         $GCC_MACHINE"
echo " G++:             $GCC_INFO"
echo " Clang:           $CLANG_INFO"
echo " Binutils:        $BINUTILS_INFO"
echo " GDB:             $GDB"
echo " Make:            $MAKE"
echo " CMake:           $CMAKE"
echo " Patch:           $PATCH"
echo ""
echo "$COL_GREEN Environment: $COL_RESET"
echo " PATH:            $PATH"
echo " LD_LIBRARY_PATH: $LD_LIBRARY_PATH"
echo ""
echo "$COL_GREEN Static analysis: $COL_RESET"
echo " Clang-tidy:      $CLANG_TIDY"
echo " Cppcheck:        $CPPCHECK"
echo ""
echo "$COL_GREEN Docs:  $COL_RESET"
echo " Doxygen:         $DOXYGEN"
echo ""
echo "$COL_GREEN Libs: $COL_RESET"
echo " GLibC:           $GLIBC_INFO"
echo " Boost:           $LIB_BOOST"
echo " Curl:            $LIB_CURL"
echo ""
echo "$COL_GREEN SCVs: $COL_RESET"
echo " Git:             $GIT"
echo ""
echo "************************************************************"
echo ""

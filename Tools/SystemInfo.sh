#!/usr/bin/env bash
#
# \file  SystemInfo.sh
# \brief system info about OS
#


# constants
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput bold; tput setaf 1)"
COL_GREEN="$(tput bold; tput setaf 2)"
COL_YELLOW_BOLD="$(tput bold; tput setaf 3)"


# vars
OS_INFO=`uname -a`
OS_TYPE=$OSTYPE
OS_BIT=`getconf LONG_BIT`
OS_ARCH=`uname -m`
GCC_MACHINE=`gcc -dumpmachine`
GCC_INFO=`gcc -dumpversion`
GLIBC_INFO=`ldd --version | head -n 1`
BINUTILS_INFO=`ld --version | head -n 1`
GDB=`gdb --version | head -n 1`
MAKE=`make --version | head -n 1`
CMAKE=`cmake --version | head -n 1`
PATCH=`patch --version | head -n 1`
SHELL=$SHELL


# print info
echo ""
echo "************************************************************"
echo "* System info"
echo "*"
echo "* OS:       $OS_INFO"
echo "* OS type:  $OS_TYPE"
echo "* OS bit:   $OS_BIT ($cOS_ARCH)"
echo "* Machine:  $GCC_MACHINE"
echo "* GCC:      $GCC_INFO"
echo "* GLIBC:    $GLIBC_INFO"
echo "* Binutils: $BINUTILS_INFO"
echo "* GDB:      $GDB"
echo "* Make:     $MAKE"
echo "* CMake:    $CMAKE"
echo "* Patch:    $PATCH"
echo "* Shell:    $SHELL"
echo "*"
echo "************************************************************"
echo ""


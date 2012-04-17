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
cOS_INFO=`uname -a`
cOS_BIT=`getconf LONG_BIT`
cOS_ARCH=`uname -m`
cGCC_INFO=`gcc -dumpversion`
cGLIBC_INFO=`ldd --version | head -n 1`
cBINUTILS_INFO=`ld --version | head -n 1`
cGDB=`gdb --version | head -n 1`
cMAKE=`make --version | head -n 1`
cPATCH=`patch --version | head -n 1`
cSHELL=`echo $SHELL`


# print info
echo ""
echo "************************************************************"
echo "* System info"
echo "*"
echo "* OS:       " $cOS_INFO
echo "* OS bit:   " $cOS_BIT \($cOS_ARCH\)
echo "* GCC:      " $cGCC_INFO
echo "* GLIBC:    " $cGLIBC_INFO
echo "* Binutils: " $cBINUTILS_INFO
echo "* GDB:      " $cGDB
echo "* Make:     " $cMAKE
echo "* Patch:    " $cPATCH
echo "* SHELL:    " $cSHELL
echo "*"
echo "************************************************************"
echo ""

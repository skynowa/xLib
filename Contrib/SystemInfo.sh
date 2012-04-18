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
cOS_TYPE=$OSTYPE
cOS_BIT=`getconf LONG_BIT`
cOS_ARCH=`uname -m`
cGCC_INFO=`gcc -dumpversion`

cGLIBC_INFO=`ldd --version | head -n 1`
if [ "" = "$cGLIBC_INFO" ]; then
    cGLIBC_INFO=`ldd --version`    
fi

cBINUTILS_INFO=`ld --version | head -n 1`
if [ "" = "$cBINUTILS_INFO" ]; then
    cBINUTILS_INFO=`ld --version`    
fi

cGDB=`gdb --version | head -n 1`
if [ "" = "$cGDB" ]; then
    cGDB=`gdb --version`
fi

cMAKE=`make --version | head -n 1`
if [ "" = "$cMAKE" ]; then
    cMAKE=`make --version`
fi

cPATCH=`patch --version | head -n 1`
if [ "" = "$cPATCH" ]; then
    cGDB=`patch --version`
fi


cSHELL=$SHELL


# print info
echo ""
echo "************************************************************"
echo "* System info"
echo "*"
echo "* OS:       " $cOS_INFO
echo "* OS type:  " $cOS_TYPE
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



# gcc -dumpversion
# gcc -dumpmachine

# OS   := $(shell uname -s)
# ARCH := $(shell uname -m)
# KERN := $(shell uname -r | cut -d. -f 1,2)
# BDIR := $(OS)_$(KERN).$(ARCH)


#!/usr/bin/env bash
#
# \file  makefile.sh
# \brief build project
#

set -ex

# vars
DIR_XLIB="../build"
DIR_BUILD="../../xLib_makefile"


# build
mkdir -p $DIR_BUILD
cd $DIR_BUILD && pwd && ls -la
cd .. && pwd && ls -la
cd .. && pwd && ls -la
cd $BITBUCKET_CLONE DIR && pwd && ls -la

# cmake \
# 	-G"Unix Makefiles" \
# 	$DIR_XLIB

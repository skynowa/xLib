#!/usr/bin/env bash
#
# \file  eclipse.sh
# \brief CMake configure project
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_eclipse"
GENERATOR="Visual Studio 16 2019"

# prepare
mkdir -p $DIR_BUILD
cd $DIR_BUILD

# build
cmake $GENERATOR $DIR_PROJECT

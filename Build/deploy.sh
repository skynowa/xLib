#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib"
DIR_BUILD="../../${PROJECT_NAME}_build"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
sudo cmake --build . --target install --config Release

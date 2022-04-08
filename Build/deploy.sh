#!/usr/bin/env bash


# vars
PROJECT_NAME="xLib"
DIR_BUILD="../../${PROJECT_NAME}_build"

cd $DIR_BUILD
cmake --build . --target install --config Release

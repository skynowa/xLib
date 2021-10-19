#!/usr/bin/env bash


./build.sh

# vars
DIR_BUILD="../../xLib_build"
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
ctest -C Debug -j$JOBS_NUM --output-on-failure

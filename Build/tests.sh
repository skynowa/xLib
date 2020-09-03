#!/usr/bin/env bash


./build.sh

# vars
DIR_BUILD="../../xLib_eclipse"
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
ctest -j$JOBS_NUM

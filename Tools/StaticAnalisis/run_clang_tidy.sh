#!/usr/bin/env bash


# vars
DIR_BUILD="../../../xLib_eclipse"
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
cmake --build . --target clang-tidy -- -j$JOBS_NUM

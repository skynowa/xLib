#!/usr/bin/env bash


# vars
DIR_BUILD="../../xLib_eclipse"
JOBS_NUM=$(nproc --all)

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
ctest

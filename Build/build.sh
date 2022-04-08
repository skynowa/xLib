#!/usr/bin/env bash
#


# vars
PROJECT_NAME="xLib"
DIR_BUILD="../../${PROJECT_NAME}_build"
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
cmake --build . --target ALL_BUILD --config Release --parallel ${JOBS_NUM}

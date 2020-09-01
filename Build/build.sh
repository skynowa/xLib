#!/usr/bin/env bash
#
# \file  eclipse.sh
# \brief build project
#


# vars
DIR_BUILD="../../xLib_eclipse"
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
cmake --build . -- -j$JOBS_NUM

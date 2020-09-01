#!/usr/bin/env bash
#
# \file  eclipse.sh
# \brief build project
#


# vars
DIR_BUILD="../../xLib_makefile"
JOBS_NUM=$(nproc --all)

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
cmake --build . -- -j$JOBS_NUM

#!/usr/bin/env bash
#
# \file  tests.sh
# \brief test project
#


# vars
DIR_BUILD="../../xLib_eclipse"
JOBS_NUM=$(nproc --all)

echo "Jobs: $JOBS_NUM"

cd $DIR_BUILD
ctest

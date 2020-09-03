#!/usr/bin/env bash


UNIT_TEST_NAME=$*

if [[ -z "$UNIT_TEST_NAME" ]]; then
	echo "Empty unit test name. Exit"
	echo "Usage: `basename $0` [UNIT_TEST_NAME]"

	exit 1
fi

# vars
DIR_BUILD="../../xLib_eclipse"
JOBS_NUM=$(($(nproc) * 2))

echo "Jobs: $JOBS_NUM"

cd ../xLib_eclipse

if [[ "$UNIT_TEST_NAME" == "all" ]]; then
    make all -j$JOBS_NUM && ctest -j$JOBS_NUM
else
    make Test_$UNIT_TEST_NAME && ./Tests/Test_$UNIT_TEST_NAME
fi

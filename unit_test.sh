#!/usr/bin/env bash


UNIT_TEST_NAME=$*

if [[ -z "$UNIT_TEST_NAME" ]]; then
	echo "Empty unit test name. Exit"
	echo "Usage: `basename $0` [UNIT_TEST_NAME]"

	exit 1
fi

cd ../xLib_eclipse

if [[ "$UNIT_TEST_NAME" == "all" ]]; then
	make all && ctest
else
	make Test_$UNIT_TEST_NAME && ./Tests/Test_$UNIT_TEST_NAME
fi

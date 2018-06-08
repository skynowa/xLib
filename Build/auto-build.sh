#!/bin/bash
##
## Auto build project
##


APP_NAME="[AUTO_BUILD]"

PROJECT_DIR=/home/skynowa/Projects/xLib
BUILD_DIR=$PROJECT_DIR/../xLib_eclipse
TEST_DIR=$BUILD_DIR/Tests


EXCLUDE_DIRS='(.git/|Build/|Docs/|Tools/)'

# TODO: EXCLUDE_FILES
# EXCLUDE_FILES='\.(lock|.project|sh|core|o|so|txt|pid|tmp|swp)'
EXCLUDE_FILES='\.([^h]|[^inl]|[^cpp])$'

INCLUDE_FILES="\.(h|inl|cpp)$"
FILE_PATH_LAST=""

cd $PROJECT_DIR
echo "$APP_NAME: Watch $PROJECT_DIR..."

while true; do
	inotifywait --recursive \
		--exclude "$EXCLUDE_DIRS" \
		--event modify,delete,create,move \
		$PROJECT_DIR | \
	while read DIR EVENT FILE
	do
		FILE_PATH_CURRENT="$DIR$FILE"

		if [[ "$FILE_PATH_LAST" = "$FILE_PATH_CURRENT" ]]; then
			continue
		fi

		FILE_PATH_LAST=$FILE_PATH_CURRENT

		if ! [[ "$FILE" =~ $INCLUDE_FILES ]]; then
			echo "$APP_NAME: Skip $FILE"
			continue
		fi

		reset
		echo "$APP_NAME: Build $DIR$FILE - $EVENT..."

		# prepare
		cd $BUILD_DIR

		if     [[ "$FILE_PATH_CURRENT" =~ "$PROJECT_DIR/Include" ]]; then
			echo -e "$APP_NAME: lib...\n"
			make xLib_static || echo "$APP_NAME: Error - $?"
		elif [[ "$FILE_PATH_CURRENT" =~ "$PROJECT_DIR/Tests" ]]; then
			TEST_UNIT=`basename --suffix=.cpp "$FILE_PATH_CURRENT"`

			echo -e "$APP_NAME: test $TEST_UNIT...\n"
			make $TEST_UNIT && $TEST_DIR/$TEST_UNIT || echo "$APP_NAME: Error - $?"
		else
			echo -e "$APP_NAME: Unknown path $FILE_PATH_CURRENT...\n"
		fi

		echo -e "\n$APP_NAME: Finished.\n"
	done
done

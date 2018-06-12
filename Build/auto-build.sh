#!/bin/bash
##
## Auto build project
##


APP_NAME="[AUTO_BUILD]"

JOBS_NUM=`nproc --all`
MAKE="make -j$JOBS_NUM"

PROJECT_DIR=/home/skynowa/Projects/xLib
BUILD_DIR=$PROJECT_DIR/../xLib_eclipse
TEST_DIR=$BUILD_DIR/Tests
INOTIFY_WAIT=`which inotifywait`

EXCLUDE_DIRS='(.git/|Build/|Docs/|Tools/)'

# TODO: EXCLUDE_FILES
# EXCLUDE_FILES='\.(lock|.project|sh|core|o|so|txt|pid|tmp|swp)'
EXCLUDE_FILES='\.([^h]|[^inl]|[^cpp])$'

INCLUDE_FILES="\.(h|inl|cpp)$"
FILE_PATH_LAST=""

if [ ! -f $INOTIFY_WAIT ]; then
    echo "$INOTIFY_WAIT - not found. Exit."
    exit 1
fi


cd $PROJECT_DIR
echo "$APP_NAME: Watch $PROJECT_DIR..."

while true; do
	$INOTIFY_WAIT --recursive \
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

		# prepare
		reset
		echo "$APP_NAME: Build (jobs $JOBS_NUM) $DIR$FILE - $EVENT..."
		cd $BUILD_DIR

		if     [[ "$FILE_PATH_CURRENT" =~ "$PROJECT_DIR/Include" ]]; then
			echo -e "$APP_NAME: lib...\n"
			$MAKE xLib_static || echo "$APP_NAME: Error - $?"
		elif [[ "$FILE_PATH_CURRENT" =~ "$PROJECT_DIR/Tests" ]]; then
			TEST_UNIT=`basename --suffix=.cpp "$FILE_PATH_CURRENT"`

			echo -e "$APP_NAME: test $TEST_UNIT...\n"
			$MAKE $TEST_UNIT && $TEST_DIR/$TEST_UNIT || echo "$APP_NAME: Error - $?"
		else
			echo -e "$APP_NAME: Unknown path $FILE_PATH_CURRENT...\n"
		fi

		echo -e "\n$APP_NAME: Finished.\n"
	done
done

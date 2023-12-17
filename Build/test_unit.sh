#!/usr/bin/env bash


UNIT_TESTS=(File Backup)

BG='\e[46m'   # green
FG='\e[37m'   # white
RESET='\e[0m' # reset
#--------------------------------------------------------------------------------------------------
for it_test in ${UNIT_TESTS[*]}
do
	echo -e ""
	echo -e "${BG}${FG}::::: ${it_test} :::::${RESET}"
	echo -e ""

	./tests.sh ${it_test} # && ./deploy.sh
done
#--------------------------------------------------------------------------------------------------

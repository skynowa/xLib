#!/usr/bin/env bash


UNIT_TESTS=(File Backup)

# BG='\e[46m'   # green
# FG='\e[37m'   # white
# RESET='\e[0m' # reset

source bash_colors.sh
#--------------------------------------------------------------------------------------------------
for it_test in ${UNIT_TESTS[*]}
do
	echo -e "${BASH_BG_BLACK}+------------------------------+${BASH_RESET}"
	echo -e "${BASH_BG_BLACK}|${BASH_BG_GREEN}${BASH_FG_BLACK} ${it_test} ${BASH_RESET}"
	echo -e "${BASH_BG_BLACK}+------------------------------+${BASH_RESET}"

	./tests.sh ${it_test} # && ./deploy.sh
done
#--------------------------------------------------------------------------------------------------

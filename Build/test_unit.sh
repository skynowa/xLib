#!/usr/bin/env bash


UNIT_TESTS=(Console)
UNIT_TESTS=(Cout)
UNIT_TESTS=(ThreadPool)
# UNIT_TESTS=(FileLog)
# UNIT_TESTS=(MySql)
# UNIT_TESTS=(Thread)
# UNIT_TESTS=(Dll)
# UNIT_TESTS=(Env)
# UNIT_TESTS=(DateTime)
# UNIT_TESTS=(Type)
# UNIT_TESTS=(SourceInfo)
# UNIT_TESTS=(StackTrace)
# UNIT_TESTS=(BuildInfo)
# UNIT_TESTS=(FileText FileBin)
# UNIT_TESTS=(Xml)

# BG='\e[46m'   # green
# FG='\e[37m'   # white
# RESET='\e[0m' # reset

source bash_colors.sh
#--------------------------------------------------------------------------------------------------
./deploy.sh

for it_test in ${UNIT_TESTS[*]}
do
	echo -e "${BASH_BG_BLACK}+------------------------------+${BASH_RESET}"
	echo -e "${BASH_BG_BLACK}|${BASH_FG_YELLOW} ${it_test} ${BASH_RESET}"
	echo -e "${BASH_BG_BLACK}+------------------------------+${BASH_RESET}"

	./tests.sh "${it_test}"
done
#--------------------------------------------------------------------------------------------------

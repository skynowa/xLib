#!/usr/bin/env bash
#
# \file  xLib.sh
# \brief build, install, test, ... for Unix OS
#


# 
# 1 - build static lib
# 2 - install static lib
# 3 - build share lib
# 4 - install share lib
# 5 - build tests
# 6 - run tests
# 7 - quit
#


# constants
COL_NORM="$(tput setaf 9)"
COL_RED="$(tput bold; tput setaf 1)"
COL_GREEN="$(tput bold; tput setaf 2)"
COL_YELLOW_BOLD="$(tput bold; tput setaf 3)"


# vars
MAKE=
TARGET_DIR=


# params
opt=$1


#
# functions
#


f_usage() {
    echo -e 
    echo -e "---------------------------------"
    echo -e "   U S A G E"
    echo -e "---------------------------------"
    echo -e "1. Build static lib"
    echo -e "2. Install static lib"
    echo -e "3. Build share lib"
    echo -e "4. Install share lib"
    echo -e "5. Build tests"
    echo -e "6. Run tests"
    echo -e "7. Quit"
    echo -e "---------------------------------"
    echo -e 
}

f_build_static_lib() {
    echo -e 
    echo -e "build static lib"
    echo -e 
    
    ./Lib_Unix.sh
} 

f_install_static_lib() {
    ./Install_Unix.sh
} 

f_build_share_lib() {
    echo -e 
    echo -e "f_build_share_lib"
    echo -e
} 

f_install_sharelib() {
    echo -e 
    echo -e "f_install_sharelib"
    echo -e      
} 

f_build_tests() {
    ./Tests_Unix.sh
} 

f_run_tests() {
    ./RunTests_Unix.sh
}

f_quit() {
    echo -e 
    echo -e "quit"
    echo -e 

    exit
}

f_invalid_option() {
    echo -e 
    echo -e "invalid option"
    echo -e 
}


#
# main
#


# show menu
if [ ! $opt ]; then
    f_usage
    read -r -p "Enter your choice [1-7] : " opt
fi
    

# take action
case $opt in
    1)  f_build_static_lib;;
    2)  f_install_static_lib;;
    3)  f_build_share_lib;;
    4)  f_install_sharelib;;
    5)  f_build_tests;;
    6)  f_run_tests;;            
    7)  f_quit;;
    *)  f_invalid_option;;
esac



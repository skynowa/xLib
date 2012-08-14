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

options=( \
    "build static lib" \
    "install static lib" \
    "build share lib" \
    "install share lib" \
    "build tests" \
    "run tests" \
    "quit" \
)


#
# functions
#

function f_build_static_lib {
    echo -e 
    echo -e "build static lib"
    echo -e 
    
    ./Lib_Unix.sh
} 

function f_install_static_lib {
    ./Install_Unix.sh
} 

function f_build_share_lib {
    echo -e 
    echo -e "f_build_share_lib"
    echo -e
} 

function f_install_sharelib {
    echo -e 
    echo -e "f_install_sharelib"
    echo -e      
} 

function f_build_tests {
    ./Tests_Unix.sh
} 

function f_run_tests {
    ./RunTests_Unix.sh
}

function f_quit {
    echo -e 
    echo -e "quit"
    echo -e 

    exit
}

function f_invalid_option {
    echo -e 
    echo -e "invalid option"
    echo -e 
}


#
# main
#

PS3="Enter your choice: "

select opt in "${options[@]}"
do
    case $opt in
        "build static lib")     f_build_static_lib;;
        "install static lib")   f_install_static_lib;;
        "build share lib")      f_build_share_lib;;
        "install share lib")    f_install_sharelib;;
        "build tests")          f_build_tests;;
        "run tests")            f_run_tests;;            
        "quit")                 f_quit;;
        *)                      f_invalid_option;;
    esac
done


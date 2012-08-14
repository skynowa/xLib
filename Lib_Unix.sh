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


#
# vars
#

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
    echo -e "build static lib"
} 

function f_install_static_lib {
    echo -e "install static lib"
} 

function f_build_share_lib {
    echo -e "build share lib"
} 

function f_install_sharelib {
    echo -e "install share lib"
} 

function f_build_tests {
    echo -e "build tests"
} 

function f_run_tests {
    echo -e "run tests"
}

function f_quit {
    echo -e "quit"
    exit
}

function f_invalid_option {
    echo -e "invalid option"
}


#
# main
#

PS3='Please enter your choice: '

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

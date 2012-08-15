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


#
# functions
#


usage() {
    echo -e 
    echo -e "---------------------------------"
    echo -e "   `basename $0` usage"
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

xlib_build_static_lib() {
    ./Lib_Unix.sh
} 

xlib_install_static_lib() {
    ./Install_Unix.sh
} 

xlib_build_share_lib() {
    echo -e 
    echo -e "TODO: build_share_lib"
    echo -e
} 

xlib_install_sharelib() {
    echo -e 
    echo -e "TODO: install_sharelib"
    echo -e      
} 

xlib_build_tests() {
    ./Tests_Unix.sh
} 

xlib_run_tests() {
    ./RunTests_Unix.sh
}

quit() {
    echo -e 
    echo -e "Quit"
    echo -e 

    exit
}

invalid_option() {
    echo -e 
    echo -e "Invalid option"
    echo -e 
}


#
# main
#

if [ 0 = $# ]; then
    usage
    exit 0
fi

opt=$1


# take action
case $opt in
    1)  xlib_build_static_lib;;
    2)  xlib_install_static_lib;;
    3)  xlib_build_share_lib;;
    4)  xlib_install_sharelib;;
    5)  xlib_build_tests;;
    6)  xlib_run_tests;;            
    7)  quit;;
    *)  invalid_option;;
esac



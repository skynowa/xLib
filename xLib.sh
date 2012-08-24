#!/usr/bin/env bash
#
# \file  xLib.sh
# \brief build, install, uninstall, test, ... for Unix OS
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


# bash colors
COL_NORM='\e[0m'        # Text Reset
COL_BLACK='\e[0;30m'    # Black
COL_RED='\e[0;31m'      # Red
COL_GREEN='\e[0;32m'    # Green
COL_YELLOW='\e[0;33m'   # Yellow
COL_BLUE='\e[0;34m'     # Blue
COL_PURPULE='\e[0;35m'  # Purple
COL_CYAN='\e[0;36m'     # Cyan
COL_WHITE='\e[0;37m'    # White


# constants


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
    echo -e "2. Install static lib (as root)"
    echo -e "3. Build share lib"
    echo -e "4. Install share lib (as root)"
    echo -e "5. Uninstall lib (as root)"
    echo -e "6. Build tests"
    echo -e "7. Run tests"
    echo -e "8. Quit"
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

xlib_uninstall_libs() {
    ./Uninstall_Unix.sh
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
    5)  xlib_uninstall_libs;;
    6)  xlib_build_tests;;
    7)  xlib_run_tests;;
    8)  quit;;
    *)  invalid_option;;
esac



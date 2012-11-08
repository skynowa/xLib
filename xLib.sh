#!/usr/bin/env bash
#
# \file  xLib.sh
# \brief build, clean, install, uninstall, test, ... for Unix OS
#


# bash colors
# COL_NORM='\e[0m'        # Text Reset
# COL_BLACK='\e[0;30m'    # Black
# COL_RED='\e[0;31m'      # Red
# COL_GREEN='\e[0;32m'    # Green
# COL_YELLOW='\e[0;33m'   # Yellow
# COL_BLUE='\e[0;34m'     # Blue
# COL_PURPULE='\e[0;35m'  # Purple
# COL_CYAN='\e[0;36m'     # Cyan
# COL_WHITE='\e[0;37m'    # White


# constants


# vars


#
# functions
#


usage() {
    echo -e ""
    echo -e "+------------------------------+"
    echo -e "|   xLib.sh usage              |"
    echo -e "+------------------------------+"
    echo -e "|  1. Libs clean               |"
    echo -e "|  2. Libs build               |"
    echo -e "|  3. Libs rebuild             |"
    echo -e "|  4. Libs install             |"
    echo -e "|  5. Libs uninstall           |"
    echo -e "|                              |"
    echo -e "|  6. Tests clean              |"
    echo -e "|  7. Tests build              |"
    echo -e "|  8. Tests rebuild            |"
    echo -e "|  9. Tests build and run      |"
    echo -e "| 10. Tests run                |"
    echo -e "|                              |"
    echo -e "| 11. Quit                     |"
    echo -e "+------------------------------+"
    echo -e ""
}

xlib_libs_clean() {
    ./LibsClean_Unix.sh
}

xlib_libs_build() {
    ./LibsBuild_Unix.sh
}

xlib_libs_rebuild() {
    ./LibsClean_Unix.sh &&
    ./LibsBuild_Unix.sh
}

xlib_libs_install() {
    ./LibsInstall_Unix.sh
}

xlib_libs_uninstall() {
    ./LibsUninstall_Unix.sh
}

xlib_tests_clean() {
    ./TestsClean_Unix.sh
}

xlib_tests_build() {
    ./TestsBuild_Unix.sh
}

xlib_tests_rebuild() {
    ./TestsClean_Unix.sh &&
    ./TestsBuild_Unix.sh
}

xlib_tests_build_run() {
    ./TestsBuild_Unix.sh &&
    ./TestsRun_Unix.sh
}

xlib_tests_run() {
    ./TestsRun_Unix.sh
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

opt_count=$#
opt_menu_pos=$1

if [ 0 = $opt_count ]; then
    usage
    exit 0
fi

# take action
case $opt_menu_pos in
    1)  xlib_libs_clean;;
    2)  xlib_libs_build;;
    3)  xlib_libs_rebuild;;
    4)  xlib_libs_install;;
    5)  xlib_libs_uninstall;;

    6)  xlib_tests_clean;;
    7)  xlib_tests_build;;
    8)  xlib_tests_rebuild;;
    9)  xlib_tests_build_run;;
    10) xlib_tests_run;;

    11) quit;;
    *)  invalid_option;;
esac



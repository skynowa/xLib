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


PS3='Please enter your choice: '
options=(
    "1" \
    "2" \
    "3" \
    "4" \
    "5" \
    "6" \
    "Quit")

select opt in "${options[@]}"
do
    case $opt in
        "1")
            echo "you chose choice 1"
            ;;
        "2")
            echo "you chose choice 2"
            ;;
        "3")
            echo "you chose choice 3"
            ;;
        "4")
            echo "you chose choice 1"
            ;;
        "5")
            echo "you chose choice 2"
            ;;
        "6")
            echo "you chose choice 3"
            ;;            
        "7")
            break
            ;;
        *) echo "invalid option"
            ;;
    esac
done

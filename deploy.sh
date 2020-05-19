#!/usr/bin/env bash
#
# \file  eclipse.sh
# \brief build project
#


# vars
DIR_BUILD="../xLib_eclipse"

cd $DIR_BUILD

cmake --build . -- -j16
sudo cmake . --target install -- -j16
sudo ldconfig
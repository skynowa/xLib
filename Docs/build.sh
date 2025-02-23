#!/bin/sh
#
# \file  build.sh
# \brief Build Doxygen documentation
#


rm -rf ./html
doxygen ./Doxyfile

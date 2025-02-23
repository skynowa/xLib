#!/bin/sh
#
# \file  build_ui.sh
# \brief Build Doxygen documentation using UI client
#

rm -rf ./html
doxywizard ./Doxyfile

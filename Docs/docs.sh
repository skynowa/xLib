#!/usr/bin/env bash
#
# \file  docs.sh
# \brief Generate Doxygen documentation
#


#---------------------------------------------------------------------------------------------------
# Clean
rm -rf ./html/*

# Build - UI
# doxywizard ./Doxyfile

# Build
doxygen ./Doxyfile
#---------------------------------------------------------------------------------------------------

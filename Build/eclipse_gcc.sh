#!/usr/bin/env bash
#
# \file  eclipse_gcc.sh
# \brief build tests
#


# vars
# export CC="gcc"
# export CXX="g++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_eclipse_gcc"


# build

# Eclipse versions:
#   - 3.2 Callisto
#   - 3.3 Europa
#   - 3.4 Ganymede
#   - 3.5 Galileo
#   - 3.6 Helios
#   - 3.7 Indigo
#   - 4.2 Juno
#   - 4.3 Kepler
#   - 4.4 Luna
#   - 4.5 Mars

mkdir -p $DIR_BUILD
cd $DIR_BUILD
cmake -G"Eclipse CDT4 - Unix Makefiles" -D_ECLIPSE_VERSION=4.3 $DIR_XLIB
# make -j4 VERBOSE=1

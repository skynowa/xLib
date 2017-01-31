#!/usr/bin/env bash
#
# \file  eclipse.sh
# \brief build project
#


# vars
# export CC="gcc"
# export CXX="g++"
export CC="clang"
export CXX="clang++"

DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_eclipse"


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
cmake \
	-G"Eclipse CDT4 - Unix Makefiles" \
	-D_ECLIPSE_VERSION=4.3 \
	-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
	$DIR_XLIB

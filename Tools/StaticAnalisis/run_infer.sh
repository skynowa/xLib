#!/usr/bin/env bash
#
# \file  run_infer.sh
# \brief run infer analizator
#


# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_eclipse"

mkdir -p $DIR_BUILD
cd $DIR_BUILD

infer run \
	--compilation-database compile_commands.json

# infer compile -- cmake $DIR_XLIB
# infer run -- make -j 4

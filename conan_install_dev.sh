#!/usr/bin/env bash
#
# Dev: skynowa-pc
#


# vars
DIR_INSTALL="/home/skynowa/Projects"
DIR_BUILD="/home/skynowa/Projects/xLib_conan_build"

conan install \
	conan_file.txt \
	--install-folder "${DIR_INSTALL}" \
	--output-folder  "${DIR_BUILD}" \
	--profile conan_profile_dev.txt \
	--build=missing
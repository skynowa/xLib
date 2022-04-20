#!/usr/bin/env bash
#
# Dev: skynowa-pc
#


# vars
DIR_BUILD="/home/skynowa/Projects/xLib_conan"

conan install \
	conan_file.txt \
	--install-folder "${DIR_BUILD}" \
	--output-folder  "${DIR_BUILD}" \
	--profile conan_profile_dev.txt \
	--build=missing
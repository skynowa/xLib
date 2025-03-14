#!/usr/bin/env bash
#
# Dev: skynowa-pc
#


# vars
PROJECT_NAME="xLib"
DIR_BUILD="../${PROJECT_NAME}_conan"

conan install \
	conan_file.txt \
	--output-folder="${DIR_BUILD}" \
	--profile=conan_profile_dev.txt \
	--build=missing \
	--update
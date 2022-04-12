#!/usr/bin/env bash


# vars
DIR_XLIB="../xLib"
DIR_BUILD="../../xLib_build"

mkdir -p $DIR_BUILD
cd $DIR_BUILD

make template

#!/usr/bin/env bash
#
# \file  eclipse.sh
# \brief build project
#


./build.sh

sudo cmake --build . --target install

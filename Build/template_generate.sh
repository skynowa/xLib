#!/usr/bin/env bash
#
# \file  template_generate.sh
# \brief Generate class template(s)
#


# vars
PROJECT_NAME="xLib"
DIR_PROJECT="../${PROJECT_NAME}"
DIR_BUILD="../../${PROJECT_NAME}_build"

# prepare
mkdir -p ${DIR_BUILD}
cd ${DIR_BUILD}

# build
cmake --build . --target template

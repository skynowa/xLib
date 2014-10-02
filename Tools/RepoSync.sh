#!/usr/bin/env bash
#
# \file  RepoSync.sh
# \brief sync repository
#

cd ..

git push --tags https://skynowa@code.google.com/p/xlib-library/ master:master
git push --tags https://skynowa@github.com/skynowa/xLib.git master:master
git push --tags https://skynowa@git.code.sf.net/p/x-lib/code master:master

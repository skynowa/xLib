#!/usr/bin/env bash
#
# \file  RepoSync.sh
# \brief sync repository
#

cd ..

# code.google.com
git checkout master
git push --tags https://skynowa@code.google.com/p/xlib-library/ master:master

git checkout develop
git push --tags https://skynowa@code.google.com/p/xlib-library/ develop:develop

# github.com
git checkout master
git push --tags https://skynowa@github.com/skynowa/xLib.git master:master

git checkout develop
git push --tags https://skynowa@github.com/skynowa/xLib.git develop:develop

# sourceforge.net
git checkout master
git push --tags https://skynowa@git.code.sf.net/p/x-lib/code master:master

git checkout develop
git push --tags https://skynowa@git.code.sf.net/p/x-lib/code develop:develop

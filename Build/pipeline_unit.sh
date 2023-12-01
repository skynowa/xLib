#!/usr/bin/env bash
#


set -ex

./build.sh
sudo ./deploy.sh

./test_unit.sh

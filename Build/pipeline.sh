#!/usr/bin/env bash
#


set -ex

./gen_eclipse.sh
./build.sh
sudo ./deploy.sh

./gen_tests_eclipse.sh
./tests.sh

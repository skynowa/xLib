#!/usr/bin/env bash
#


set -ex

./gen_eclipse.sh
./build.sh

./gen_tests_eclipse.sh
./tests.sh

sudo ./deploy.sh

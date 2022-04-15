#!/usr/bin/env bash
#


./gen_eclipse.sh
./build.sh

./gen_tests_eclipse.sh
./tests.sh

sudo ./deploy.sh

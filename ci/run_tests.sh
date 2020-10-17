#!/bin/sh

set -ev

mkdir build
cd build/
cmake -DJTL_ENABLE_TESTS=ON ../
make VERBOSE=1 test-jtl
./tests/test-jtl

#!/bin/sh

set -e

mkdir build
cd build/
cmake -DJTL_ENABLE_TESTS=ON ../
make test-jtl
./tests/test-jtl

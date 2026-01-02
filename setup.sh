#!/bin/sh

set -xe

mkdir build
cd build
cmake ../
make
cd ../
chmod +x file_tester.sh
./file_tester.sh
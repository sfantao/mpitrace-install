#!/bin/bash -eux

g++ -std=c++11 a.cpp -I $(pwd)/../gperftools-install/include $(pwd)/../gperftools-install/lib/libprofiler.a 

./a.out 1000000000 1.0000123

export CPUPROFILE_FREQUENCY=100
./a.out 1000000000 1.0000123

export CPUPROFILE_FREQUENCY=400
./a.out 1000000000 1.0000123z

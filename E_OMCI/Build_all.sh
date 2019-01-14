#!/bin/bash
if [ "$1" == "C" ];then
    rm -rf build/*
else
    mkdir build
    cd build/
    cmake -DCMAKE_BUILD_TYPE=Debug ../
    make
    cd ../
    cp build/e_omci src/
fi


#!/bin/bash
if [ "$1" == "C" ];then
    rm -rf build/*
else
    mkdir build
    cd build/
    cmake ../
    make
fi


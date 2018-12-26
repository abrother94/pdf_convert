#!/bin/bash

if [ "$1" == "C" ];then
    rm -rf build/*
else
    cd build/
    cmake ../
    make
fi


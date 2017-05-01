#!/usr/bin/env bash

# compile.sh
#
# Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
# Licensed under MIT
# Version 1.0.2

# Compile script for C++ program

# compiler flags, includes and libs
OPENCV_FLAGS=`pkg-config --cflags --libs opencv`
BOOST_FLAGS="-I/usr/local/opt/boost/include -lboost_system -lboost_filesystem"

echo "Removing previously compiled programs."

# remove the compiled directory
rm -rf ./out/compiled

# create the folders
mkdir -p out/compiled

echo "Compiling source codes."

# compile the program
g++ $OPENCV_FLAGS $BOOST_FLAGS -std=c++11 src/color-map.cpp -o out/compiled/color-map
g++ $OPENCV_FLAGS $BOOST_FLAGS -std=c++11 src/rgb-transformation.cpp -o out/compiled/rgb-transformation

echo "Compilation done."



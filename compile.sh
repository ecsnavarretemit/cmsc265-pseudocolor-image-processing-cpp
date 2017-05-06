#!/usr/bin/env bash

# compile.sh
#
# Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
# Licensed under MIT
# Version 1.0.3

# Compile script for C++ program

# compiler flags, includes and libs
OPENCV_INCLUDE_FLAGS=`pkg-config --cflags opencv`
OPENCV_LINK_FLAGS=`pkg-config --libs opencv`
BOOST_INCLUDE_FLAGS="-I/usr/local/opt/boost/include"
BOOST_LINK_FLAGS="-L/usr/local/opt/boost/lib -lboost_system -lboost_filesystem"

echo "Removing previously compiled programs."

# remove the compiled directory
rm -rf ./out/compiled

# create the folders
mkdir -p out/compiled

echo "Compiling source codes."

# compile the program source files
SOURCE_FILES=("src/color-map.cpp" "src/rgb-transformation.cpp")
for source_file in "${SOURCE_FILES[@]}"; do
    filename=`basename ${source_file%.*}`

    echo "Compiling: '$source_file'. Output will be on 'out/compiled/$filename'"
    g++ $OPENCV_INCLUDE_FLAGS $BOOST_INCLUDE_FLAGS $source_file $OPENCV_LINK_FLAGS $BOOST_LINK_FLAGS -std=c++11 -o out/compiled/$filename

    OUT=$?
    if [ $OUT -ne 0 ];then
        echo "Compilation failed for $source_file"
        exit 1
    fi
done

echo "Compilation done."
exit 0



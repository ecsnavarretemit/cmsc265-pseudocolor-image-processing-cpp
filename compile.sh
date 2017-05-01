# Compile script for C++ program

# compiler flags, includes and libs
OPENCV_PKG_CONFIG=`pkg-config --cflags --libs opencv`
BOOST_FLAGS="-I/usr/local/opt/boost/include -lboost_system -lboost_filesystem"

# remove the compiled directory
rm -rf ./out/compiled

# create the folders
mkdir -p out/compiled

# compile the program
g++ $OPENCV_PKG_CONFIG $BOOST_FLAGS -std=c++11 src/color-map.cpp -o out/compiled/color-map
g++ $OPENCV_PKG_CONFIG $BOOST_FLAGS -std=c++11 src/rgb-transformation.cpp -o out/compiled/rgb-transformation



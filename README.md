# CMSC 265 Exercise 7 - Pseudocolor Image Processing

## Requirements

1. OpenCV 3.x
2. C++ 4.2.x compiler and above (g++)
3. Boost C++ 1.63 and above

# Compiling the program

To compile the program, the following flags are needed:

1. OpenCV Include Flags: `-I<path_to_opencv>/include/opencv -I<path_to_opencv>/include`
2. OpenCV Link Flags: `-L<path_to_opencv>/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs`
3. Boost Include Flags: `-I<path_to_boost>/include`
4. Boost Link FLags: `-L<path_to_boost>/lib -lboost_system -lboost_filesystem`

If `pkg-config` is installed and used during compilation of OpenCV, You can easily replace the OpenCV flags with `pkg-config --cflags --libs opencv`.
Verify first if the command returns value. If no value returned then use the manual inclusion of flags.

The program should be compiled with `g++ <opencv_include_flags> <boost_include_flags> <source_code>.cpp <opencv_link_flags> <boost_link_flags> -std=c++11 -o <where_to_place_the_compiled_file>`.
The flag `-std=c++11` tells the compiler that the programs should be compiled with C++11 compatibility. Without the flag, the compilation will not work and will throw errors.

There is a shell script named `compile.sh` that does this for you automatically. If not properly working, just replace the flags related to OpenCV and Boost. Finally run `sh compile.sh` or `./compile.sh`.

For other systems, compilation might fail. You might need to set `LD_FLAGS` environment variable before compiling:
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<path_to_opencv>/lib:<path_to_boost>/lib`

# Running the program

You can run the compiled programs by invoking `./<name_of_the_compiled_file>`.

## License

MIT



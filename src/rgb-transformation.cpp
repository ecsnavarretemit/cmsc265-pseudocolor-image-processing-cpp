/**
 * rgb-transformation.cpp
 *
 * Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
 * Licensed under MIT
 * Version 1.0.4
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "boost/filesystem.hpp"
#include "boost/range/iterator_range.hpp"
#include "files.cpp"

using namespace std;

// define pixel type
typedef uchar Pixel;

int main() {
    boost::filesystem::path in_path;
    boost::filesystem::path out_path;

    // resolve and normalize paths
    in_path = boost::filesystem::system_complete("assets/img");
    out_path = boost::filesystem::system_complete("out/rgb-transformation");

    // delete the contents of the output folder
    if (boost::filesystem::exists(out_path)) {
        boost::filesystem::remove_all(out_path);
    }

    // create output folder if it does not exist
    if(!boost::filesystem::exists(out_path) && !boost::filesystem::create_directories(out_path)) {
        cerr << "Error in creating output directory" << out_path.string() << endl;
        return 1;
    }

    cout << "Reading all images from the directory: " << in_path.string() << endl;
    cout << "Output will be saved in: " << out_path.string() << endl;

    // formula variables
    int a = 255;
    float b = (2 * M_PI) / 255;
    float c = M_PI / 5;

    // create a vector that will hold the processed r, g, b channels
    vector<cv::Mat> rgb_vector;

    // create Matrices for src, dst, red, green and blue
    cv::Mat src, dst, red, green, blue;

    try {
        vector<boost::filesystem::path> imgs = get_images(in_path);

        int pixel_max_value = 256;

        // define lookup table
        vector<uchar> red_lut(pixel_max_value);
        vector<uchar> green_lut(pixel_max_value);
        vector<uchar> blue_lut(pixel_max_value);

        // pre-compute and assign computed values in the lookup table for each channel
        for (int i = 0; i < pixel_max_value; i++) {
            // compute the value of bx
            float bx = b * i;

            // perform transformation on the r channel: R = a | sin(bx) |
            red_lut[i] = a * abs(sin(bx));

            // perform transformation on the g channel: G = a | sin(bx + c) |
            green_lut[i] = a * abs(sin(bx + c));

            // perform transformation on the b channel: B = a | sin(bx + 2c) |
            blue_lut[i] = a * abs(sin(bx + (2 * c)));
        }

        for (auto & img : imgs) {
             // assemble the output path
            boost::filesystem::path im_out = out_path / img.filename();

            // read image in grayscale
            src = cv::imread(img.string(), CV_LOAD_IMAGE_GRAYSCALE);

            // apply lookup table each matrix: red, green and blue
            cv::LUT(src, red_lut, red);
            cv::LUT(src, green_lut, green);
            cv::LUT(src, blue_lut, blue);

            // add the channels in to the vector matrix in the arrangement of bgr
            // since opencv reads rgb images in bgr not rgb
            rgb_vector.push_back(blue);
            rgb_vector.push_back(green);
            rgb_vector.push_back(red);

            // merge the channels
            cv::merge(rgb_vector, dst);

            // write to the filesystem
            cv::imwrite(im_out.string(), dst);

            // empty out the vector for the next iteration
            rgb_vector.clear();

            // free up resources
            src.release();
            dst.release();
            red.release();
            green.release();
            blue.release();
        }
    } catch(const invalid_argument& e) {
        cerr << e.what() << endl;
        return 1;
    } catch (const string msg) {
        cerr << msg << endl;
        return 1;
    }

    cout << "Done processing images." << endl;

    return 0;
}



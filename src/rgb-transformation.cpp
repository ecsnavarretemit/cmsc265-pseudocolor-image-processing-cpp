/**
 * rgb-transformation.cpp
 *
 * Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
 * Licensed under MIT
 * Version 1.0.2
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
    // resolve and normalize paths
    string cwd = boost::filesystem::current_path().string();
    string in_path = cwd + "/assets/img";
    string out_path = cwd + "/out/rgb-transformation";
    boost::filesystem::path in(in_path);
    boost::filesystem::path out(out_path);

    // delete the contents of the output folder
    if (boost::filesystem::exists(out)) {
        boost::filesystem::remove_all(out);
    }

    // create output folder if it does not exist
    if(!boost::filesystem::exists(out) && !boost::filesystem::create_directories(out)) {
        cerr << "Error in creating output directory" << out << endl;
        return 1;
    }

    cout << "Reading all images from the directory: " << in << endl;
    cout << "Output will be saved in: " << out << endl;

    // formula variables
    int a = 255;
    float b = (2 * M_PI) / 255;
    float c = M_PI / 5;

    // create a vector that will hold the processed r, g, b channels
    vector<cv::Mat> rgb_vector;

    // create Matrices for src, dst, red, green and blue
    cv::Mat src, dst, red, green, blue;

    // variable to use in storing image dimensions
    cv::Size im_size;

    try {
        vector<boost::filesystem::path> imgs = get_images(in_path);

        for (auto & img : imgs) {
             // assemble the output path
            boost::filesystem::path im_out = out / img.filename();

            // read image in grayscale
            src = cv::imread(img.string(), CV_LOAD_IMAGE_GRAYSCALE);

            // create Size object
            im_size = cv::Size(src.cols, src.rows);

            // create empty mat for placing the processed values for each channel
            red = cv::Mat::zeros(im_size, CV_8UC1);
            green = cv::Mat::zeros(im_size, CV_8UC1);
            blue = cv::Mat::zeros(im_size, CV_8UC1);

            // loop through each pixel using Mat::forEach and C++11 lambda.
            src.forEach<Pixel>([&a, &b, &c, &red, &green, &blue](Pixel &pixel, const int * position) -> void {
                // compute the value of bx
                float bx = b * (int) pixel;

                // perform transformation on the r channel: R = a | sin(bx) |
                red.at<uchar>(position[0], position[1]) = a * abs(sin(bx));

                // perform transformation on the g channel: G = a | sin(bx + c) |
                green.at<uchar>(position[0], position[1]) = a * abs(sin(bx + c));

                // perform transformation on the b channel: B = a | sin(bx + 2c) |
                blue.at<uchar>(position[0], position[1]) = a * abs(sin(bx + (2 * c)));
            });

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



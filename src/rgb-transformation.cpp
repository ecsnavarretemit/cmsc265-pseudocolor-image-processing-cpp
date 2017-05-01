/**
 * rgb-transformation.cpp
 *
 * Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
 * Licensed under MIT
 * Version 1.0.0
 */

#include <iostream>
#include <vector>
#include <math.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "boost/filesystem.hpp"
#include "boost/range/iterator_range.hpp"

using namespace std;

int main() {
    cv::Mat src, dst;
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
        cout << "Error in creating output directory" << out << endl;
        return 1;
    }

    cout << "Reading all images from the directory: " << in << endl;
    cout << "Reading all images from the directory: " << out << endl;

    // formula variables
    int a = 255;
    float c = M_PI / 5;

    // read all images in the folder
    for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(in), {})) {
        if (entry.path().extension() != ".jpg") {
            continue;
        }

        // assemble the output path
        boost::filesystem::path im_out = out / entry.path().filename();

        // read image in grayscale
        src = cv::imread(entry.path().string(), CV_LOAD_IMAGE_GRAYSCALE);

        // create a vector that will hold the processed r,g,b channels
        vector<cv::Mat> ch;

        // create empty mat for placing the processed values for each channel
        cv::Mat r = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC1);
        cv::Mat g = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC1);
        cv::Mat b = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC1);

        // loop through all contents of the matrix
        for(int i = 0; i < src.cols; i++) {
            for(int j = 0; j < src.rows; j++) {
                // get pixel at coordinates j, i
                int x = (int) src.at<uchar>(j, i);

                // compute the value of bx
                float bx = ((2 * M_PI) / 255) * x;

                // perform transformation on the r channel: R = a | sin(bx) |
                r.at<uchar>(j, i) = a * abs(sin(bx));

                // perform transformation on the g channel: G = a | sin(bx + c) |
                g.at<uchar>(j, i) = a * abs(sin(bx + c));

                // perform transformation on the b channel: B = a | sin(bx + 2c) |
                b.at<uchar>(j, i) = a * abs(sin(bx + (2 * c)));
            }
        }

        // add the channels in to the vector matrix
        ch.push_back(b);
        ch.push_back(g);
        ch.push_back(r);

        // merge the channels
        cv::merge(ch, dst);

        // write to the filesystem
        cv::imwrite(im_out.string(), dst);

        // free up resources
        src.release();
        dst.release();
        r.release();
        g.release();
        b.release();
    }

    cout << "Done processing images." << endl;

    return 0;
}



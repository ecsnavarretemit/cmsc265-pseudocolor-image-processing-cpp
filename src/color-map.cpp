/**
 * color-map.cpp
 *
 * Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
 * Licensed under MIT
 * Version 1.0.0
 */

#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "boost/filesystem.hpp"
#include "boost/range/iterator_range.hpp"

using namespace std;

// define structure for colormap constants
struct {
    string name;
    int color_constant;
} colormaps[13];

int main() {
    cv::Mat src, dst;
    string cwd = boost::filesystem::current_path().string();
    string in_path = cwd + "/assets/img";
    string out_path = cwd + "/out/color-map";
    boost::filesystem::path in(in_path);
    boost::filesystem::path out(out_path);

    //-----------------------------------------------------------
    // [Color Constants] ::start
    //-----------------------------------------------------------

    colormaps[0].name = "autumn";
    colormaps[0].color_constant = cv::COLORMAP_AUTUMN;

    colormaps[1].name = "bone";
    colormaps[1].color_constant = cv::COLORMAP_BONE;

    colormaps[2].name = "cool";
    colormaps[2].color_constant = cv::COLORMAP_COOL;

    colormaps[3].name = "hot";
    colormaps[3].color_constant = cv::COLORMAP_HOT;

    colormaps[4].name = "hsv";
    colormaps[4].color_constant = cv::COLORMAP_HSV;

    colormaps[5].name = "jet";
    colormaps[5].color_constant = cv::COLORMAP_JET;

    colormaps[6].name = "ocean";
    colormaps[6].color_constant = cv::COLORMAP_OCEAN;

    colormaps[7].name = "parula";
    colormaps[7].color_constant = cv::COLORMAP_PARULA;

    colormaps[8].name = "pink";
    colormaps[8].color_constant = cv::COLORMAP_PINK;

    colormaps[9].name = "rainbow";
    colormaps[9].color_constant = cv::COLORMAP_RAINBOW;

    colormaps[10].name = "spring";
    colormaps[10].color_constant = cv::COLORMAP_SPRING;

    colormaps[11].name = "summer";
    colormaps[11].color_constant = cv::COLORMAP_SUMMER;

    colormaps[12].name = "winter";
    colormaps[12].color_constant = cv::COLORMAP_WINTER;

    //-----------------------------------------------------------
    // [Color Constants] ::end
    //-----------------------------------------------------------

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

    // read all images in the folder
    for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(in), {})) {
        // skip iteration when the file does not have ".jpg" file extension
        if (entry.path().extension() != ".jpg") {
            continue;
        }

        // assemble the output path
        boost::filesystem::path im_out = out / entry.path().stem();

        // create output folder if it does not exist
        if(!boost::filesystem::exists(im_out) && !boost::filesystem::create_directories(im_out)) {
            cout << "Error in writing files!" << endl;
            return 1;
        }

        // loop through all defined constants
        for (int i = 0; i < 13; i++) {
            // assemble the path to the newly created image
            string image_name = colormaps[i].name + ".jpg";
            boost::filesystem::path color_im_out = im_out / image_name;

            // read image in grayscale
            src = cv::imread(entry.path().string(), CV_LOAD_IMAGE_GRAYSCALE);

            // apply colormaps
            cv::applyColorMap(src, dst, colormaps[i].color_constant);

            // write to the filesystem
            cv::imwrite(color_im_out.string(), dst);

            // free up resources
            src.release();
            dst.release();
        }
    }

    cout << "Done processing images." << endl;

    return 0;
}



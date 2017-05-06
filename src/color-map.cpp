/**
 * color-map.cpp
 *
 * Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
 * Licensed under MIT
 * Version 1.0.3
 */

#include <iostream>
#include <vector>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "boost/filesystem.hpp"
#include "boost/range/iterator_range.hpp"
#include "files.cpp"

using namespace std;

// define structure for colormap constants
struct {
    string name;
    int color_constant;
} colormaps[13];

int main() {
    boost::filesystem::path in_path;
    boost::filesystem::path out_path;

    // resolve and normalize paths
    in_path = boost::filesystem::system_complete("assets/img");
    out_path = boost::filesystem::system_complete("out/color-map");

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

    // create Matrices for src, dst
    cv::Mat src, dst;

    try {
        vector<boost::filesystem::path> imgs = get_images(in_path);

        for (auto & img : imgs) {
            // assemble the output path
            boost::filesystem::path im_out = out_path / img.stem();

            // create output folder if it does not exist
            if(!boost::filesystem::exists(im_out) && !boost::filesystem::create_directories(im_out)) {
                throw "Error in writing files!";
            }

            // loop through all defined constants
            for (int i = 0; i < 13; i++) {
                // assemble the path to the newly created image
                string image_name = colormaps[i].name + ".jpg";
                boost::filesystem::path color_im_out = im_out / image_name;

                // read image in grayscale
                src = cv::imread(img.string(), CV_LOAD_IMAGE_GRAYSCALE);

                // apply colormaps
                cv::applyColorMap(src, dst, colormaps[i].color_constant);

                // write to the filesystem
                cv::imwrite(color_im_out.string(), dst);

                // free up resources
                src.release();
                dst.release();
            }
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



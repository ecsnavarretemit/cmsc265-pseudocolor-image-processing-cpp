/**
 * files.cpp
 *
 * Copyright(c) Exequiel Ceasar Navarrete <esnavarrete1@up.edu.ph>
 * Licensed under MIT
 * Version 1.0.3
 */

#include <vector>
#include "boost/filesystem.hpp"
#include "boost/range/iterator_range.hpp"

using namespace std;

vector<boost::filesystem::path> get_images(boost::filesystem::path directory, vector<string> extensions = vector<string>()) {
    vector<string> extensions_filter;
    vector<boost::filesystem::path> images;

    // throw error
    if (!boost::filesystem::is_directory(directory)) {
        throw invalid_argument("Directory: " + directory.string() + " is not a directory.");
    }

    // use the extensions parameter if the number of items is greater than 0
    // else use jpg and png as defaults
    if (extensions.size() > 0) {
        extensions_filter = extensions;
    } else {
        extensions_filter.push_back(".jpg");
        extensions_filter.push_back(".png");
    }

    // add the matched paths to the vector and return it later if it contains more than 0 elements.
    for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(directory), {})) {
        for (auto & extension : extensions_filter) {
            if (!boost::filesystem::is_directory(entry) && entry.path().extension() == extension) {
                images.push_back(entry);
                break;
            }
        }
    }

    // throw error message saying no images found
    if (images.size() == 0) {
        throw "No images found in the directory: " + directory.string();
    }

    return images;
}



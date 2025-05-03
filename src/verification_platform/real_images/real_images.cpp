// Copyright 2019 Victor Hugo Schulz

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "real_images.h"

using namespace std;
using namespace cv;
using namespace std_str;

namespace ssim {

RealImages::RealImages()
{ // Constructor
}

Sky RealImages::asteria()
{ // Generate a sky configuration from image
    string filename = "dataset/asteria_nasa_orion.png";
    Sky output;
    Mat image_color = cv::imread(filename);
    cvtColor(image_color, output.image, COLOR_BGR2GRAY);
    output.q = { 0.683248, { -0.72665, 0.0509266, -0.050578 } };
    return output;
}

vector<string> getAsteriaFilenames()
{
    vector<string> filenames;
    vector<string> json_filenames;
    json_filenames.push_back("dataset/str4sd/processed/SWA_processed_images_metadata.json");
    json_filenames.push_back("dataset/str4sd/processed/SWB_processed_images_metadata.json");
    json_filenames.push_back("dataset/str4sd/processed/SWC_processed_images_metadata.json");
    json_filenames.push_back("dataset/str4sd/processed/SWA2018_processed_images_metadata.json");
    json_filenames.push_back("dataset/str4sd/processed/SWB2018_processed_images_metadata.json");
    json_filenames.push_back("dataset/str4sd/processed/SWC2018_processed_images_metadata.json");

    for (uint i = 0; i < json_filenames.size(); i++) {
        FileStorage fs(json_filenames[i], FileStorage::READ);
        FileNode n = fs.root();
        FileNodeIterator it = n.begin(), it_end = n.end();
        for (; it != it_end; ++it) {
            FileNodeIterator it2 = (*it).begin(), it2_end = (*it).end();
            for (; it2 != it2_end; ++it2) {
                FileNodeIterator it3 = (*it2).begin(), it3_end = (*it2).end();
                for (; it3 != it3_end; ++it3) {
                    string filename = (string)(*it3)["filepath"]["PNG"];
                    filename = "./dataset/str4sd" + filename.substr(1);
                    filenames.push_back(filename);
                }
            }
        }
    }
    return filenames;
}

Sky RealImages::swarm()
{ // Generate a sky configuration from images
    static vector<string> filenames = getAsteriaFilenames();
    static uint i = 0;
    string filename = filenames[i];
    Sky output;
    Mat image_color = cv::imread(filename);
    cvtColor(image_color, output.image, COLOR_BGR2GRAY);
    i++;
    if (i >= filenames.size())
        i = 0;
    return output;
}

}

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

Sky RealImages::generate_sky()
{ // Generate a sky configuration from image
    string filename = "asteria_nasa_orion.jpeg";
    Sky output;
    Mat image_color = cv::imread(filename);
    cvtColor(image_color, output.image, COLOR_BGR2GRAY);
    // output.q = { 0.6834717599437533, { -0.7265912966832452, 0.06356850147638535, -0.029841021490484475 } };
    output.q = { 0.683248, { -0.72665, 0.0509266, -0.050578 } };
    return output;
}

}

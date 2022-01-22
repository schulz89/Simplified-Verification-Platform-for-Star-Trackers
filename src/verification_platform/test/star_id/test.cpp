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

#include "test.h"

using namespace std;
using namespace cv;
using namespace std_str;

TestStarID::TestStarID()
{
    string directory, filename;
    FileStorage fs("config/common.yml", FileStorage::READ);
    fs["vp_output_directory"] >> directory;
    fs["vp_output_filename"]  >> filename;
    fs.release();

    mkdir(directory.c_str(), S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
    filename = directory + "/" + filename;
    ofs = new ofstream(filename,ofstream::out);
    
    *ofs << "%" << "Correct" << "\t" << "Identified" << "\t" << "Total" << "\t" << "Time (s)" << endl;
}

void TestStarID::scoreboard(Sky sky_in, Sky sky_out)
{
    acc.compare_data(sky_in, sky_out);
    *ofs << acc.correct << "\t" << acc.identified << "\t" << acc.total << "\t" << acc.time<< endl;
    // imshow("Image", sky_out.image);
    // waitKey(0);
}

void TestStarID::report(){
    acc.print();
}

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

TestStarTracker::TestStarTracker()
{
    string directory, filename;
    FileStorage fs("config/common.yml", FileStorage::READ);
    fs["vp_output_directory"] >> directory;
    fs["vp_output_filename"] >> filename;
    fs.release();

    mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    filename = directory + "/" + filename;
    ofs = new ofstream(filename, ofstream::out);

    *ofs << "%" << "centroid_t_ms"
         << "\t" << "centroid_nothr_t_ms"
         << "\t" << "star_id_t_ms"
         << "\t" << "attitude_t_ms"
         << "\t" << "att_correct"
         << "\t" << "att_rejected"
         << "\t" << "att_wrong"
         << "\t" << "att_error"
         << "\t" << "starid_total"
         << "\t" << "starid_identified"
         << "\t" << "starid_correct"
         << endl;
}

void TestStarTracker::scoreboard(Sky sky_in, Sky sky_out)
{
    acc_centr.compare_data(sky_in, sky_out);
    acc_starid.compare_data(sky_in, sky_out);
    acc_att.compare_data(sky_in, sky_out);

    *ofs << sky_out.time[0]
         << "\t" << sky_out.time[1]
         << "\t" << sky_out.time[2]
         << "\t" << sky_out.time[3]
         << "\t" << acc_att.correct
         << "\t" << acc_att.rejected
         << "\t" << acc_att.wrong
         << "\t" << acc_att.error
         << "\t" << acc_starid.total
         << "\t" << acc_starid.identified
         << "\t" << acc_starid.correct
         << endl;

//     cout << sky_in.q.r << "\t"
//          << sky_in.q.v[0] << "\t"
//          << sky_in.q.v[1] << "\t"
//          << sky_in.q.v[2] << endl;
//     cout << sky_out.q.r << "\t"
//          << sky_out.q.v[0] << "\t"
//          << sky_out.q.v[1] << "\t"
//          << sky_out.q.v[2] << endl;

    // namedWindow("Image", CV_GUI_NORMAL);
    // resizeWindow("Image", sky_in.image.cols*0.75, sky_in.image.rows*0.75);
    // setWindowProperty("Image", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    // imshow("Image", sky_in.image); waitKey(0);
    // imshow("Image", sky_out.image); waitKey(1);
}

void TestStarTracker::report()
{
    cout << endl;
    cout << "Runtime:" << endl;
    cout << "centroid time, total (s)        = " << acc_centr.time_acc << endl;
    cout << "centroid time, no threshold (s) = " << acc_centr.time_c_acc << endl;
    cout << "star id time (s)                = " << acc_starid.time_acc << endl;
    cout << "attitude determination time (s) = " << acc_att.time_acc << endl;
    cout << "correct attitude ratio          = " << (double)acc_att.correct_acc / acc_att.total_acc << endl;
    cout << "rejected attitude ratio         = " << (double)acc_att.rejected_acc / acc_att.total_acc << endl;
    cout << "wrong attitude ratio            = " << (double)acc_att.wrong_acc / acc_att.total_acc << endl;
    cout << endl;

    // acc_centr.print();
    // acc_starid.print();
    // acc_att.print();
}

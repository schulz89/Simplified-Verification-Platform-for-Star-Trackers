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

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <chrono>
#include <ctime>

#include "star_simulator/starsimulator.h"

#include "dut/centroiding.h"
#include "dut/star_identification.h"
#include "dut/attitude_determination.h"

#include "test/centroiding/test.h"
#include "test/star_id/test.h"
#include "test/star_tracker/test.h"

using namespace std;
using namespace std::chrono;
using namespace cv;
using namespace std_str; // standard structure
using namespace ssim;    // star simulator
using namespace st;

void process_centroiding(Sky& sky_in, Sky& sky_out);
void process_star_identification(Sky& sky_in, Sky& sky_out);
void process_attitude_determination(Sky& sky_in, Sky& sky_out);

enum dut_t { CENTROIDING_REGION_GROWING = 0, // 0
    STAR_ID_GRID = 3,                        // 3
    ATTITUDE_DETERMINATION = 4,              // 4
    STAR_TRACKER = 5,                        // 5
    STAR_SIMULATOR_VALIDATION = 7 };         // 6

enum test_t { TEST_CENTROIDING, // 0
    TEST_STAR_ID,               // 1
    TEST_ATTITUDE,              // 2
    TEST_STAR_TRACKER,          // 3
    TEST_STAR_TRACKER_IMG };    // 4

int main(int argc, char* argv[])
{
    dut_t dut_sel = CENTROIDING_REGION_GROWING;
    test_t test_sel = TEST_CENTROIDING;

    if (argc >= 3) {
        dut_sel = (dut_t)atoi(argv[1]);
        test_sel = (test_t)atoi(argv[2]);
    } else {
        cout << "Usage: verification_plarform [dut_id] [test_id]" << endl;
        exit(1);
    }

    double n_tests = 0;
    cv::FileStorage fs("config/common.yml", cv::FileStorage::READ);
    fs["vp_n_tests"] >> n_tests;
    fs.release();

    StarSimulator ss;
    Sky sky_in, sky_out;

    TestCentroiding test_centroiding;
    TestStarID test_star_id;
    TestStarTracker test_star_tracker;

    for (int i = 0; i < (int)n_tests; i++) {
        // DUT
        switch (dut_sel) {
        case CENTROIDING_REGION_GROWING: {
            sky_in = ss.generate_sky(); // Sequence
            process_centroiding(sky_in, sky_out);
        } break;
        case STAR_ID_GRID: {
            sky_in = ss.generate_sky();
            ss.config.simulator_parameters.build_image = false;
            process_star_identification(sky_in, sky_out);
        } break;
        case ATTITUDE_DETERMINATION: {
            sky_in = ss.generate_sky(); // Sequence
            process_attitude_determination(sky_in, sky_out);
        } break;
        case STAR_TRACKER: {
            sky_in = ss.generate_sky(); // Sequence
            process_centroiding(sky_in, sky_out);
            process_star_identification(sky_out, sky_out);
            process_attitude_determination(sky_out, sky_out);
        } break;
        case STAR_SIMULATOR_VALIDATION: {
            Quaternion q = {0.6834717599437533, {-0.7265912966832452, 0.06356850147638535, -0.029841021490484475}};
            sky_in = ss.generate_sky(q); // Sequence
            imshow("Generated image", sky_in.image); waitKey(0);
            return(0);
        }
        default: {
            cout << "Invalid dut." << endl;
            exit(1);
        } break;
        }

        // Scoreboard
        switch (test_sel) {
        case TEST_CENTROIDING: {
            test_centroiding.scoreboard(sky_in, sky_out);
        } break;
        case TEST_STAR_ID: {
            test_star_id.scoreboard(sky_in, sky_out);
        } break;
        case TEST_ATTITUDE: {
        } break;
        case TEST_STAR_TRACKER: {
            test_star_tracker.scoreboard(sky_in, sky_out);
        } break;
        case TEST_STAR_TRACKER_IMG: {
        } break;
        default: {
            cout << "Invalid test." << endl;
            exit(1);
        } break;
        }
    }

    // Test report
    switch (test_sel) {
    case TEST_CENTROIDING: {
        test_centroiding.report();
    } break;
    case TEST_STAR_ID: {
        test_star_id.report();
    } break;
    case TEST_ATTITUDE: {
    } break;
    case TEST_STAR_TRACKER: {
        test_star_tracker.report();
    } break;
    case TEST_STAR_TRACKER_IMG: {
    } break;
    default: {
        cout << "Invalid test." << endl;
        exit(1);
    } break;
    }

    return 0;
}

void process_centroiding(Sky& sky_in, Sky& sky_out)
{
    static Centroiding centroiding;
    auto start = high_resolution_clock::now();
    sky_out = centroiding.process(sky_in);
    auto end = high_resolution_clock::now();
    duration<double> elapsed_seconds = end - start;
    sky_out.time.push_back(elapsed_seconds.count());
    sky_out.time.push_back(0.0);
}

void process_star_identification(Sky& sky_in, Sky& sky_out)
{
    static StarIdentification star_identification;
    auto start = high_resolution_clock::now();
    sky_out = star_identification.identifyStars(sky_in);
    auto end = high_resolution_clock::now();
    duration<double> elapsed_seconds = end - start;
    sky_out.time.push_back(elapsed_seconds.count());
}

void process_attitude_determination(Sky& sky_in, Sky& sky_out)
{
    static AttitudeDetermination attitude_determination;
    auto start = high_resolution_clock::now();
    sky_out = attitude_determination.process(sky_in);
    auto end = high_resolution_clock::now();
    duration<double> elapsed_seconds = end - start;
    sky_out.time.push_back(elapsed_seconds.count());
}

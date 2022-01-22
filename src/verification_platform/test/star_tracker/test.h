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

#ifndef TEST_STAR_TRACKER_H_
#define TEST_STAR_TRACKER_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sys/stat.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "standard_structures.h"
#include "test/common/scoreboard_common.h"

class TestStarTracker {

public:
    TestStarTracker();
    SBCentroiding acc_centr;
    SBStarId      acc_starid;
    SBAttitude    acc_att;
    void scoreboard(std_str::Sky sky_in, std_str::Sky sky_out);
    void report();
    std::ofstream *ofs;
};

#endif /* TEST_STAR_TRACKER_H_ */

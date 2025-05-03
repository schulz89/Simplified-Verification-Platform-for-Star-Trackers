#!/bin/bash

git clone https://github.com/esa/str4sd.git dataset/str4sd
cd dataset/str4sd
git apply ../../str4sd.patch

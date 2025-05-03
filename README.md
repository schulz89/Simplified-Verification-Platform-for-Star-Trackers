# Simplified Verification Platform for Star Trackers

This is a verification platform for testing star tracker algorithms, based on UVM-SystemC, but with the aim to minimize the dependencies compared to the original project.
The code is currently under development.

## Compiling and running

Compiling the project with the supplied makefile was tested on Debian 11, with the versions of the dependencies shown in the list of dependencies below.

Compiling the platform can be done with:

```
make
```
Downloading the star catalog can be done with:

```
./download_hipparcos
```

Ensure the Atlas library is being loaded:

```
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/atlas/
```

Then, running the tests can be done with:

```
./run_test
```

## List of dependencies

* OpenCV (including Python)
* Atlas
* Blas
* Boost
* Python
* NumPy (for Python)
* Matplotlib (for Python)

Example of command line for installing on Fedora Linux:

```
sudo dnf install opencv-devel python3-opencv atlas atlas-devel openblas blas-devel lapack-devel boost-devel python3-numpy python3-matplotlib
```

## License

This software is licensed under Apache License, Version 2.0

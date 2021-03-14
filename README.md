# docscan

## Installation of OpenCV

> :warning: **In Ubuntu 20.04**: Continuing with the recommended installation process (also below) results in missing dependencies during runtime. The reported missing dependencies are libgtk2.0-dev and pkg-config. Install them before proceeding with the compilation of OpenCV with `sudo apt-get install libgtk2.0-dev` and `sudo apt-get install pkg-config` (the second one was already installed in my system).

Steps taken from [OpenCV docs](https://docs.opencv.org/4.5.0/d7/d9f/tutorial_linux_install.html).

~~~bash
# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
unzip opencv.zip
# Create build directory
mkdir -p ocv-build && cd ocv-build
# Configure
cmake  ../opencv-master
# Build
cmake --build . && cd ..
~~~

Add the environment variable for OpenCV binaries
~~~bash
export OpenCV_DIR=ocv-build
~~~

## Building with g++ and cmake

Start with a simple CMakeLists.txt such as
~~~cmake
cmake_minimum_required(VERSION 2.8)
project( main )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS} )
~~~

and compile with

~~~bash
cmake .
make
~~~



To help others, I found that my .bashrc needed to contain the following:
export DISPLAY=:0.0
previously, it said
export DISPLAY=localhost:0.0
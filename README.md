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

## Building with g++ and cmake

Start with a simple CMakeLists.txt such as
~~~cmake
cmake_minimum_required(VERSION 2.8)
project( main )

set("OpenCV_DIR" "ocv-build")

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

## Using VSCode extensions for cmake and c++

One can use extensions to make it easier to build and debug c++ sources, and place the compiled programs in the desired directory.

1. Install the two extensions from the documentation [page](https://code.visualstudio.com/docs/cpp/CMake-linux#_prerequisites).
2. Select a build kit (to choose the debugger and compiler) by opening the command palette (`ctrl+shift+p`) and type `cmake select kit`. Then, select the kit with g++-9 (GCC 9.3.x).
3. Now, you can build and launch the executable from the VSCode with the buttons in the bottom Status bar.


To help others, I found that my .bashrc needed to contain the following:
export DISPLAY=:0.0
previously, it said
export DISPLAY=localhost:0.0
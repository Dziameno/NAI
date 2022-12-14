cmake_minimum_required(VERSION 3.24)
project(LAB08)

set(CMAKE_CXX_STANDARD 17)

add_executable(LAB08 main.cpp)

set(OpenCV_DIR "/Users/zuo/OpenCV/opencv/cmake-build-release")

find_package( OpenCV REQUIRED )

if( OpenCV_FOUND )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
    link_directories( ${OpenCV_LIB_DIR} )

    target_link_libraries( LAB08 opencv_core;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_videoio )
endif()

cmake_minimum_required(VERSION 3.20)
project(bitmap)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bitmap
    src/main.cpp
    src/Pictures/Bytes.cpp
    src/Pictures/Bitmap.cpp
    src/Pictures/BmpReader.cpp
    src/Pictures/Histogram.cpp
    src/Pictures/utility/FileLoader.cpp
)

target_include_directories(bitmap PRIVATE include)

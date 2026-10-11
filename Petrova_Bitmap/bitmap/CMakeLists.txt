cmake_minimum_required(VERSION 3.20)
project(bitmap)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bitmap
    main.cpp
    FileLoader.cpp
    Bytes.cpp
    Histogram.cpp
    Bitmap.cpp
    BmpReader.cpp
)

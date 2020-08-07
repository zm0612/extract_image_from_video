cmake_minimum_required(VERSION 2.8)
project(extract_image)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")

message(${CMAKE_BUILD_TYPE})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(OpenCV 3.4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(extract_image main.cpp)
target_link_libraries(extract_image ${OpenCV_LIBS})

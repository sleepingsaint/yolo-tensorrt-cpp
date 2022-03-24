cmake_minimum_required(VERSION 3.1) 
project(yolo-trt VERSION 1.0)            
enable_language(CUDA)

set(CMAKE_CXX_COMPILIER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -Wno-write-strings")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE sources modules/*.hpp modules/*.cpp modules/*.h modules/*.cu extra/*.h)
add_library(detector SHARED ${sources})
target_include_directories(detector PRIVATE extra/ modules/ ${OpenCV_INCLUDE_DIRS} ${CUDA_TOOLKIT_ROOT_DIR}/include)
target_link_libraries(detector nvinfer nvinfer_plugin nvparsers "stdc++fs")

add_executable(custom-detector src/custom_detector.cpp)				  
target_include_directories(custom-detector PRIVATE modules/ extra/)
target_link_libraries(custom-detector detector ${OpenCV_LIBS})
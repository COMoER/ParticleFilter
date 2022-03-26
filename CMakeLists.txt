cmake_minimum_required(VERSION 3.16)
project(pratical_filter)

set(CMAKE_CXX_STANDARD 14)
find_package(Eigen3 REQUIRED)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
add_library(simple_pf_lib SHARED simple_pf.cpp)
#link_libraries(simple_pf_lib ${OpenCV_LIBS})


set(PYBIND ${PROJECT_SOURCE_DIR}/third_party/pybind11-2.5.0)

add_subdirectory(${PYBIND})
pybind11_add_module(simple_pf pf.cpp)
target_link_libraries(simple_pf PRIVATE simple_pf_lib)
#add_executable(particle_filter main.cpp)
#target_link_libraries(particle_filter simple_pf_lib)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(lidar_rgbd)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE Release)

find_package(PCL 1.7 REQUIRED)
set(OpenCV_DIR /usr/local/share/OpenCV)
find_package(OpenCV REQUIRED )
find_package( Boost 1.40 COMPONENTS program_options filesystem REQUIRED )

include_directories( ${Boost_INCLUDE_DIR} )
include_directories( ${OPENCV_INCLUDE_DIR} )
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")

add_executable (lyx_pcd2depth  src/lyx_pcd2depth.cpp)
target_link_libraries (lyx_pcd2depth ${PCL_LIBRARIES} ${OpenCV_LIBS})

add_executable(cutimg src/cutimg.cpp)
target_link_libraries (cutimg ${OpenCV_LIBS})

add_executable(ppm2png src/ppm2png.cpp)
target_link_libraries (ppm2png ${OpenCV_LIBS})
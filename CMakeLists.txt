cmake_minimum_required(VERSION 3.10)
project(raytracer)
set(CMAKE_CXX_STANDARD 11)


set(EIGEN_VERSION 3.4.0)
set(RAYLIB_VERSION 5.5)

find_package(Eigen3 ${EIGEN_VERSION} REQUIRED)
find_package(raylib ${RAYLIB_VERSION} REQUIRED)

include_directories(src)
include_directories(include)

set(SOURCES
	src/main.cpp
	src/linalg.cpp
	src/features.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib Eigen3::Eigen)
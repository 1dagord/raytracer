cmake_minimum_required(VERSION 3.10)
project(raytracer)
set(CMAKE_CXX_STANDARD 20)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

set(EIGEN_VERSION 3.4.0)
set(RAYLIB_VERSION 5.5)
set(BOOST_VERSION 1.86.0)

find_package(Eigen3 ${EIGEN_VERSION} REQUIRED)
find_package(raylib ${RAYLIB_VERSION} REQUIRED)
find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS system filesystem)

include_directories(src)
include_directories(include)

set(SOURCES
	src/main.cpp
	src/save_ppm.cpp
	src/linalg.cpp
	src/chapter_tests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::filesystem raylib Eigen3::Eigen)
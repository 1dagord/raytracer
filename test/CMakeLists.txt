cmake_minimum_required(VERSION 3.10)
project(test_raytracer)
set(CMAKE_CXX_STANDARD 11)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()


find_path(EIGEN_DIR NAMES signature_of_eigen3_matrix_library
    PATHS
    ~/Libraries/eigen-${EIGEN_VERSION}
    PATH_SUFFIXES eigen3 eigen
)

set(BOOST_VERSION 1.86.0)
set(BOOST_DIR /usr/local/Cellar/boost/${BOOST_VERSION}/include)

find_package(Eigen3 ${EIGEN_VERSION} REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(wxWidgets REQUIRED COMPONENTS core base)

include_directories(${EIGEN_DIR})
include_directories(${BOOST_DIR})

include_directories(src)
include_directories(include)

set(SOURCES
    src/cMain.cpp
    src/cApp.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::filesystem  wxWidgets::wxWidgets)
cmake_minimum_required(VERSION 3.0.0)
project(MovingAverage VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

file(GLOB CPP_FILES "./src/*.cpp" )
file(GLOB_RECURSE H_FILES "./src/*.hpp")
include_directories(include)
add_executable(MovingAverage ${CPP_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
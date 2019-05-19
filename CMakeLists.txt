cmake_minimum_required(VERSION 3.13)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(lab3 main.cpp List.h Map.h Haff_coder.h Haff_coder.cpp Unit_test.cpp)
target_link_libraries(lab3 gtest gtest_main)
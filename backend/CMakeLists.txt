cmake_minimum_required(VERSION 3.10)
project(SelfBalancingTrees)

# Set C++ Standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include Directories 
include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(tree_app ${SOURCES})


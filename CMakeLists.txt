cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FlagFieldManager)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include)

# Set the output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/tests")

# Add the executable for tests
# add_executable(FlagField_Tests tests/FlagField_Tests.cpp)
add_executable(FlagField_Tests tests/flagfield_tests.cpp)

# Ensure the executable is placed in the tests folder
set_target_properties(FlagField_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FlagFieldManager)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include)

# # Add the source files
# add_library(FlagField STATIC src/FlagField.cpp)

# Add the executable for tests
add_executable(FlagField_Tests tests/FlagField_Tests.cpp)

# Link the library to the tests
target_link_libraries(FlagField_Tests)

# Enable testing
enable_testing()

# Add a test
add_test(NAME FlagFieldTests COMMAND FlagField_Tests)
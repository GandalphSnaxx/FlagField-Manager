cmake_minimum_required(VERSION 3.10)

project(FlagFieldLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory for the header-only library
add_library(flagfield INTERFACE)
target_include_directories(flagfield INTERFACE include)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Include Google Test headers
include_directories(${CMAKE_BINARY_DIR}/googletest-src/googletest/include)

# Ensure consistent runtime library settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

# Add the test executable
add_executable(flagfield_tests tests/flagfield_tests.cpp)
target_link_libraries(flagfield_tests flagfield gtest gtest_main)

# Add the tests
enable_testing()
add_test(NAME FlagFieldTests COMMAND flagfield_tests)

cmake_minimum_required(VERSION 3.10)

project(FlagFieldLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory for the header-only library
add_library(flagfield INTERFACE)
target_include_directories(flagfield INTERFACE include)

include(ExternalProject)

# Download and unpack googletest at configure time
ExternalProject_Add(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
  SOURCE_DIR ${CMAKE_BINARY_DIR}/googletest-src
  BINARY_DIR ${CMAKE_BINARY_DIR}/googletest-build
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${CMAKE_BINARY_DIR}/googletest-src -S ${CMAKE_BINARY_DIR}/googletest-src -B ${CMAKE_BINARY_DIR}/googletest-build
  BUILD_COMMAND ${CMAKE_COMMAND} --build .
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

# # Add googletest directly to our build. This defines
# # the gtest and gtest_main targets.
# add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#                  ${CMAKE_BINARY_DIR}/googletest-build
#                  EXCLUDE_FROM_ALL)

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

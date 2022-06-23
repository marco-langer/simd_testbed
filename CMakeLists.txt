cmake_minimum_required(VERSION 3.18.4)

project(simd-testbed CXX)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(fmt REQUIRED)

# Options
option(WITH_TESTS "Enable building of tests" ON)
if(WITH_TESTS)
    message(STATUS "Building tests: Yes")
    enable_testing()
    find_package(Catch2 3 REQUIRED)
else()
    message(STATUS "Building tests: No")
endif()

option(WITH_BENCHMARKS "Enable building of benchmarks" OFF)
if(WITH_BENCHMARKS)
    message(STATUS "Building benchmarks: Yes")
else()
    message(STATUS "Building benchmarks: No")
endif()

# Set Version
set(SIMD_TESTBED_VERSION_MAJOR "0")
set(SIMD_TESTBED_VERSION_MINOR "0")
set(SIMD_TESTBED_VERSION_PATCH "1")
set(SIMD_TESTBED_VERSION "${SIMD_TESTBED_VERSION_MAJOR}.${SIMD_TESTBED_VERSION_MINOR}.${SIMD_TESTBED_VERSION_PATCH}")

# Build type
set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}")
endif()
message(STATUS "Setting up build for simd-testbed v${SIMD_TESTBED_VERSION} (${CMAKE_BUILD_TYPE})")

if (WITH_TESTS)
  add_subdirectory(tests)
endif()

if (WITH_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

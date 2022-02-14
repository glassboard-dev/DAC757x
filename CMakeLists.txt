# Set min req version of Cmake
cmake_minimum_required(VERSION 3.13)

# Set project name
project(DAC757x_Driver_Lib)

# Set our lib include directories
include_directories(src)

# Set the lib output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)

# Create or our static library
add_library(dac757x STATIC src/dac757x.c)

# Add a custom target for our unit tests
add_custom_target(tests cd ../ && ceedling gcov:all utils:gcov)
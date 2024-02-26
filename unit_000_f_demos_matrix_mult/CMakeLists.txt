cmake_minimum_required(VERSION 3.10)
project(SHA256Optimization)

# Find OpenCL
find_package(OpenCL REQUIRED)

# Add the executable
add_executable(sha256_host sha256_host.cpp)

# Include directories for OpenCL headers
include_directories(${OpenCL_INCLUDE_DIRS})

# Link against OpenCL libraries
target_link_libraries(sha256_host ${OpenCL_LIBRARY})

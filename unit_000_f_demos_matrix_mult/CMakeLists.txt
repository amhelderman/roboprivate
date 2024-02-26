cmake_minimum_required(VERSION 3.10)
project(MatrixMult)

# Find OpenCL
find_package(OpenCL REQUIRED)

# Add the executable
add_executable(matrix_mul_host matrix_mul_host.cpp)

# Include directories for OpenCL headers
include_directories(${OpenCL_INCLUDE_DIRS})

# Link against OpenCL libraries
target_link_libraries(matrix_mul_host ${OpenCL_LIBRARY})


# CL_HPP_TARGET_OPENCL_VERSION
target_compile_definitions(matrix_mul_host PRIVATE CL_HPP_TARGET_OPENCL_VERSION=120)
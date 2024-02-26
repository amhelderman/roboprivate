cmake_minimum_required(VERSION 3.10)
project(MatrixMult)

# Find OpenCL
find_package(OpenCL REQUIRED)

# Add the executable
add_executable(matrix_mul_host matrix_mul_host.cpp)

# Include directories for OpenCL headers
include_directories(${OpenCL_INCLUDE_DIRS})

# Link against OpenCL libraries
# target_link_libraries(matrix_mul_host ${OpenCL_LIBRARY})


# Set opencl version 
target_compile_definitions(matrix_mul_host PRIVATE CL_TARGET_OPENCL_VERSION=300)


target_link_libraries(matrix_mul_host ${OpenCL_LIBRARIES})

# Copy the kernel file to the build directory
configure_file(matrix_mul_kernel.cl matrix_mul_kernel.cl COPYONLY)


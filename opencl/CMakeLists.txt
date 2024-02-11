cmake_minimum_required(VERSION 3.10)
project(VectorAddOpenCL)

# Find OpenCL package
find_package(OpenCL REQUIRED)

# Include directories for OpenCL headers
include_directories(${OpenCL_INCLUDE_DIRS})

# Add the executable
add_executable(vector_add vector_add.c)

# Link with OpenCL library
target_link_libraries(vector_add ${OpenCL_LIBRARY})

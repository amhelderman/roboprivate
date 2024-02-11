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

# The kernel needs to be copied to the build directory
add_custom_command(TARGET vector_add POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/vector_add.cl $<TARGET_FILE_DIR:vector_add>)

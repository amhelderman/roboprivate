# cmake_minimum_required(VERSION 3.0)
# project(DemoSLAMWithOpenCL)

# set(CMAKE_CXX_STANDARD 11)

# find_package(OpenCL REQUIRED)

# include_directories(${OpenCL_INCLUDE_DIRS})

# add_executable(DemoSLAMWithOpenCL slam_host.cpp)

# target_link_libraries(${PROJECT_NAME} PRIVATE OpenCL::OpenCL)

# set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 11
#                                                  C_STANDARD_REQUIRED ON
#                                                  C_EXTENSIONS OFF)

# target_compile_definitions(${PROJECT_NAME} PRIVATE CL_TARGET_OPENCL_VERSION=100)


# # Add a command to copy the kernel file to the build directory
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
#     COMMAND ${CMAKE_COMMAND} -E copy 
#     ${CMAKE_SOURCE_DIR}/slam_kernel.cl 
#     ${CMAKE_CURRENT_BINARY_DIR}/slam_kernel.cl)

cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SLAMProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(external/json)


# Find OpenCL package
find_package(OpenCL REQUIRED)
# find_package(nlohmann_json 3.2.0 REQUIRED)

# Include directories for OpenCL headers
include_directories(${OpenCL_INCLUDE_DIRS})

# Add the executable for the SLAM host codeWhhy 
add_executable(SLAMHost slam_host.cpp)

# Set opencl version 
target_compile_definitions(SLAMHost PRIVATE CL_TARGET_OPENCL_VERSION=300)

# CL_HPP_TARGET_OPENCL_VERSION 


# Link with OpenCL libraries
target_link_libraries(SLAMHost ${OpenCL_LIBRARIES})
target_link_libraries(SLAMHost nlohmann_json::nlohmann_json)



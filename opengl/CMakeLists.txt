cmake_minimum_required(VERSION 3.10)
project(OpenGLCube)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# Define the executable
add_executable(OpenGLCube main.cpp)

# Link libraries
target_link_libraries(OpenGLCube ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw)

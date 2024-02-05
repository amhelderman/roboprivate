# FILEPATH: /home/alex/work/masterplan/study/cpp_opencv/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(OpenCVExample)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Add the executable
add_executable(example example.cpp)

# Link against OpenCV libraries and pthread
target_link_libraries(example ${OpenCV_LIBS} pthread)

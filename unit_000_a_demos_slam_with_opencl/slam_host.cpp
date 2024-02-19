
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/opencl.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

int main() {
    // Initialize OpenCL context
    std::vector<cl::Platform> platforms;


    cl::Platform::get(&platforms);
    if (platforms.empty()) {
        std::cerr << "No OpenCL platform found" << std::endl;
        return 1;
    }

    cl::Platform platform = platforms[1];
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    // Print out hte devices found 
    for (auto& device : devices) {
        std::cout << "Device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    }

    if (devices.empty()) {
        std::cerr << "No OpenCL device found" << std::endl;
        return 1;
    }

    cl::Device device = devices.front();
    cl::Context context(device);


    
    // initialize command queue, and device selection
    cl::CommandQueue queue(context, device);   

    // Load the OpenCL source code from slam_kernel.cl 
    std::ifstream source_file("slam_kernel.cl");
    std::string source_code(std::istreambuf_iterator<char>(source_file), (std::istreambuf_iterator<char>()));
    // cl::Program::Sources source(1, std::make_pair(source_code.c_str(), source_code.length() + 1));
    cl::Program::Sources sources;
    sources.push_back({source_code.c_str(), source_code.length()});



    // Compile the kernel
    cl::Program program(context, sources);
    if (program.build({device}) != CL_SUCCESS) {
        std::cerr << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
        return 1;
    }

    // Prepare data for SLAM update
    std::vector<float> scan_data; // LiDAR scan data
    std::vector<float> commands;      // Commands

    // Output data will go here later.
    std::vector<float> map;       // Map data
    std::vector<float> pose;      // Robot pose

    // Read data from the json data.json file, which contains "scans" and "commands" arrays 
    // (and "map" and "pose" objects but we wont read those here)
    std::ifstream data_file("data.json");
    nlohmann::json data;
    data_file >> data;

    for (auto& scan : data["scans"]) {
        scan_data.push_back(scan);
    }

    for (auto& command : data["commands"]) {
        commands.push_back(command);
    }



    // Create buffers and write initial data to the device
    cl::Buffer scan_buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, scan_data.size() * sizeof(float), scan_data.data());
    cl::Buffer map_buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, map.size() * sizeof(float), map.data());
    cl::Buffer pose_buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, pose.size() * sizeof(float), pose.data());

    // Execute the kernel
    cl::Kernel kernel(program, "slam_update");
    kernel.setArg(0, scan_buffer);
    kernel.setArg(1, map_buffer);
    kernel.setArg(2, pose_buffer);

    // Launch the kernel on a compute device
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(scan_data.size()));

    // The kernel should output the estimated robot pose and 
    queue.enqueueReadBuffer(pose_buffer, CL_TRUE, 0, pose.size() * sizeof(float), pose.data());


    return 0;
}

#include <CL/cl2.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Load OpenCL runtime
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.empty()) {
        std::cerr << "OpenCL platforms not found." << std::endl;
        return 1;
    }

    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices); // Assuming we want to use a GPU
    if (devices.empty()) {
        std::cerr << "OpenCL devices not found." << std::endl;
        return 1;
    }

    auto device = devices.front();
    cl::Context context(device);
    cl::CommandQueue queue(context, device);

    // Load SHA-256 kernel source
    std::ifstream kernelFile("sha256_kernel.cl");
    std::string src(std::istreambuf_iterator<char>(kernelFile), (std::istreambuf_iterator<char>()));
    cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));
    cl::Program program(context, sources);
    auto err = program.build("-cl-std=CL2.0");
    if (err != CL_SUCCESS) {
        std::cerr << "OpenCL program build error: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
        return 1;
    }

    // Prepare data
    std::string inputData = "Your data here"; // Your input data to hash
    std::vector<unsigned char> hashOutput(32); // SHA-256 outputs a 32 byte hash

    cl::Buffer inputBuffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, inputData.size(), const_cast<char*>(inputData.data()));
    cl::Buffer outputBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, hashOutput.size());

    // Set kernel arguments
    cl::Kernel kernel(program, "sha256");
    kernel.setArg(0, inputBuffer);
    kernel.setArg(1, outputBuffer);

    // Execute the kernel
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(inputData.size()), cl::NullRange);
    queue.enqueueReadBuffer(outputBuffer, CL_TRUE, 0, hashOutput.size(), hashOutput.data());

    // Output the result
    std::cout << "SHA-256 Hash: ";
    for (auto byte : hashOutput) {
        printf("%02x", byte);
    }
    std::cout << std::endl;

    return 0;
}

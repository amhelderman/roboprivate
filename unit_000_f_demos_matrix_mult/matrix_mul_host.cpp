
#define CL_HPP_TARGET_OPENCL_VERSION 300
#include <CL/opencl.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    // Matrix dimension (assuming square matrices for simplicity)
    const int N = 256;
    size_t bytes = N * N * sizeof(float);

    std::cout << "Matrix dimension: " << N << "x" << N << std::endl;

    // Generate input matrices (initialization code omitted for brevity)
    std::vector<float> A(N * N, 1.0f); // Example initialization
    std::vector<float> B(N * N, 2.0f); // Example initialization
    std::vector<float> C(N * N, 0.0f);

    std::cout << "Input matrices generated" << std::endl;

    // Boilerplate OpenCL initialization code to set up context, queue, etc.
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.empty()) {
        std::cerr << "No OpenCL platform found" << std::endl;
        return -1;
    }

    auto platform = platforms[1];



    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

    if (devices.empty()) {
        std::cerr << "No OpenCL device found" << std::endl;
        return -1;
    }
    auto device = devices.front();
    auto context = cl::Context(device);
    auto queue = cl::CommandQueue(context, device);

    std::cout << "OpenCL context initialized" << std::endl;


    // Load the OpenCL source code from slam_kernel.cl 
    std::ifstream source_file("matrix_mul_kernel.cl");
    std::string source_code(std::istreambuf_iterator<char>(source_file), (std::istreambuf_iterator<char>()));
    // cl::Program::Sources source(1, std::make_pair(source_code.c_str(), source_code.length() + 1));
    cl::Program::Sources sources;
    sources.push_back({source_code.c_str(), source_code.length()});

    std::cout << "Kernel source code loaded" << std::endl;


    cl::Program program(context, sources);

    // Build program
    if (program.build({device}) != CL_SUCCESS) {
        std::cerr << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
        return -1;
    }

    // Create buffers
    cl::Buffer bufferA(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, bytes, A.data());
    cl::Buffer bufferB(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, bytes, B.data());
    cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, bytes, nullptr);

    // Kernel setup
    cl::Kernel kernel(program, "matrix_multiply");
    kernel.setArg(0, N);
    kernel.setArg(1, bufferA);
    kernel.setArg(2, bufferB);
    kernel.setArg(3, bufferC);

    // Execute the kernel
    cl::NDRange global(N, N);
    cl::NDRange local(16, 16); // Example local work size, adjust based on device capabilities
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);

    // Read back the result
    queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, bytes, C.data());

    // Use the result (output code omitted for brevity)

    return 0;
}

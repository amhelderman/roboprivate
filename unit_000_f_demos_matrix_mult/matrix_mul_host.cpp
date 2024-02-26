

#include <CL/cl.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    // Matrix dimension (assuming square matrices for simplicity)
    const int N = 256;
    size_t bytes = N * N * sizeof(float);

    // Generate input matrices (initialization code omitted for brevity)
    std::vector<float> A(N * N, 1.0f); // Example initialization
    std::vector<float> B(N * N, 2.0f); // Example initialization
    std::vector<float> C(N * N, 0.0f);

    // Boilerplate OpenCL initialization code to set up context, queue, etc.
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
    auto device = devices.front();
    auto context = cl::Context(device);
    auto queue = cl::CommandQueue(context, device);

    // Load kernel source code
    std::ifstream source_file("matrix_mul_kernel.cl");
    std::string source_code(std::istreambuf_iterator<char>(source_file),
                            (std::istreambuf_iterator<char>()));
    cl::Program::Sources sources(1, std::make_pair(source_code.c_str(), source_code.length() + 1));
    cl::Program program(context, sources);

    // Build program
    if (program.build("-cl-std=CL1.2") != CL_SUCCESS) {
        std::cerr << "OpenCL program build error: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
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

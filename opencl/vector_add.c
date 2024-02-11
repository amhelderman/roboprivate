#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

// This should be replaced with the path to your kernel file
#define KERNEL_FILE "vector_add.cl"

// Simple function to load the kernel source code from a file into a string
char* load_source(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    char* src = (char*)malloc(size + 1);
    fread(src, 1, size, fp);
    src[size] = '\0';
    fclose(fp);
    return src;
}

int main() {
    // Use this to check error codes returned by OpenCL calls
    cl_int err;

    // Discover and initialize platforms
    cl_platform_id platform;
    err = clGetPlatformIDs(1, &platform, NULL);

    // Discover and initialize devices
    cl_device_id device;
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

    // Create context
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);

    // Create command queue
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);

    // Load kernel source
    char* kernel_src = load_source(KERNEL_FILE);
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_src, NULL, &err);
    free(kernel_src);

    // Compile kernel
    err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "vector_add", &err);

    // Create memory buffers
    float A[1024], B[1024], C[1024];
    for (int i = 0; i < 1024; i++) {
        A[i] = i;
        B[i] = i;
    }
    cl_mem bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, 1024 * sizeof(float), NULL, &err);
    cl_mem bufB = clCreateBuffer(context, CL_MEM_READ_ONLY, 1024 * sizeof(float), NULL, &err);
    cl_mem bufC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 1024 * sizeof(float), NULL, &err);

    // Copy lists to memory buffers
    err = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, 1024 * sizeof(float), A, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, 1024 * sizeof(float), B, 0, NULL, NULL);

    // Set kernel arguments
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufB);
    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufC);

    // Execute the kernel
    size_t global_size = 1024;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_size, NULL, 0, NULL, NULL);

    // Read the memory buffer C on the device to the local variable C
    err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, 1024 * sizeof(float), C, 0, NULL, NULL);

    // Display the result
    for (int i = 0; i < 10; i++) {
        printf("%f + %f = %f\n", A[i], B[i], C[i]);
    }

    // Clean up
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;
}

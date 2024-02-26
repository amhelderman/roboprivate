__kernel void matrix_multiply(const int N,          // Matrix dimension
                              __global float* A,    // Input Matrix A
                              __global float* B,    // Input Matrix B
                              __global float* C) {  // Output Matrix C
    // Get the row and column index of the C element to work on
    int row = get_global_id(1);
    int col = get_global_id(0);

    float sum = 0.0f;
    for (int k = 0; k < N; ++k) {
        sum += A[row * N + k] * B[k * N + col];
    }

    C[row * N + col] = sum;
}

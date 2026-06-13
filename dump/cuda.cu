#include <cuda_runtime.h>
#include <iostream>



__global__ void addVector(float* A, float* B, float* C, int N)
{
    // Calculate index from block and thread values
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    // Mask out excess threads in last block
    if ( i < N )
    {
        C[i] = A[i] + B[i];
    }
}


int main()
{
    int N = 1024;   // Size of vectors
    
    // Create and intialize host arrays
    float* h_A = new float[N];
    float* h_B = new float[N];
    float* h_C = new float[N];

    for (int i = 0; i < N; ++i) 
    {
        h_A[i] = 1.0f;
        h_B[i] = 2.0f;  // expect h_C[i] == 3.0f
    }

    // Allocate device memory
    float* d_A, *d_B, *d_C;
    cudaMalloc(&d_A, N * sizeof(float));
    cudaMalloc(&d_B, N * sizeof(float));
    cudaMalloc(&d_C, N * sizeof(float));

    // Copy vectors from host to device
    cudaMemcpy(d_A, h_A, N*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N*sizeof(float), cudaMemcpyHostToDevice);

    // Each block of size 256, launch one thread per each of 1024 index of vector
    int threadsPerBlock = 256;
    int numBlocks = (N + threadsPerBlock - 1) / threadsPerBlock;    // Number of blocks of size 256 threads. Ceiling function

    // Launch Kernel
    addVector<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();

    // Copy back from output vector from device to host
    cudaMemcpy( h_C, d_C, N*sizeof(float), cudaMemcpyDeviceToHost );

    //Free up device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}

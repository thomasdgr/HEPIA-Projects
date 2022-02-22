#include <stdio.h>
#include <cassert>
#include <iostream>

__global__ void laplace(float* d_in, int w, int h, float* d_out){
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;
  if(row < h - 1 && row > 0 && col < w - 1 && col > 0){
    d_out[row * w + col] = 0.25 * (
      d_in[(row - 1) * w + col] + d_in[(row + 1) * w + col] +
      d_in[row * w + (col - 1)] + d_in[row * w + (col + 1)] );
  }
}

float* heat_solver(int N, int M, int T, float* north, float* south, float* east, float* west, dim3 grid_dim, dim3 block_dim){
  const size_t n_bytes = sizeof(float) * (N * M);

  float *d = (float*) malloc(n_bytes);
  
  for(int k = 0; k < M; k++){
    d[k] = north[k];
    d[(N-1)*M + k] = south[k];
  }

  for(int k = 0; k < N-2; k++){
    d[(k+1)*M] = west[k];
    d[(k+2)*M - 1] = east[k];
  }

  float* d_in;
  cudaMalloc(&d_in, n_bytes);
  cudaMemcpy(d_in, d, n_bytes, cudaMemcpyHostToDevice);

  float* d_out;
  cudaMalloc(&d_out, n_bytes);
  cudaMemcpy(d_out, d, n_bytes, cudaMemcpyHostToDevice);

  for(int i = 0; i < T; i++){
    if(i % 2 == 0){
      laplace<<<grid_dim, block_dim>>>(d_in, N, M, d_out);
    } else {
      laplace<<<grid_dim, block_dim>>>(d_out, N, M, d_in);
    }
    cudaDeviceSynchronize();
  }  
  
  // faut verifier que je fais pas de la merde ici
  if(T % 2 == 0){
    cudaMemcpy(d, d_out, n_bytes, cudaMemcpyDeviceToHost);
  } else {
    cudaMemcpy(d, d_in, n_bytes, cudaMemcpyDeviceToHost);
  }
   
  return d;
}
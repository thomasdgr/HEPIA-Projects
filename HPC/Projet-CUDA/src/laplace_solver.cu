#include <stdio.h>
#include <cassert>
#include <iostream>

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true){
   if (code != cudaSuccess){
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
   }
}

__global__ void laplace(float* d_in, int w, int h, float* d_out){
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;
  if( (row * w + col) < w * h){
    if((row < h - 1) && (row > 0) && (col < w - 1) && (col > 0)){
      d_out[row * w + col] = 0.25 * (
        d_in[(row - 1) * w + col] + d_in[(row + 1) * w + col] +
        d_in[row * w + (col - 1)] + d_in[row * w + (col + 1)] );
    }
  }
}

float* heat_solver(int N, int M, int T, float* north, float* south, float* east, float* west, dim3 grid_dim, dim3 block_dim){
  const size_t n_bytes = sizeof(float) * (N * M);

  float *d = (float*) calloc(n_bytes, sizeof(float));
  for(int k = 0; k < M; k++){
    d[k] = north[k];
    d[(N-1)*M + k] = south[k];
  }

  for(int k = 0; k < N-2; k++){
    d[(k+1)*M] = west[k];
    d[(k+2)*M - 1] = east[k];
  }

  float* d_in;
  gpuErrchk(cudaMalloc(&d_in, n_bytes));
  gpuErrchk(cudaMemcpy(d_in, d, n_bytes, cudaMemcpyHostToDevice));

  float* d_out;
  gpuErrchk(cudaMalloc(&d_out, n_bytes));
  gpuErrchk(cudaMemcpy(d_out, d, n_bytes, cudaMemcpyHostToDevice));

  for(int i = 0; i < T; i++){
    if(i % 2 == 0){
      laplace<<<grid_dim, block_dim>>>(d_in, M, N, d_out);
    } else {
      laplace<<<grid_dim, block_dim>>>(d_out, M, N, d_in);
    }
    gpuErrchk(cudaDeviceSynchronize());
  }  
  
  if(T % 2 == 0){
    gpuErrchk(cudaMemcpy(d, d_out, n_bytes, cudaMemcpyDeviceToHost));
  } else {
    gpuErrchk(cudaMemcpy(d, d_in, n_bytes, cudaMemcpyDeviceToHost));
  }

  gpuErrchk(cudaFree(d_in));
  gpuErrchk(cudaFree(d_out));
   
  return d;
}
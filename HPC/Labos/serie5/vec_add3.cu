

#include "stdio.h"
#include <iostream>
#include <vector>
#include <cuda_runtime.h>

// DOC BAOBAB
 
// Handle CUDA error messages
inline void CUDA_HandleError(cudaError_t err, const char *file, int line)
{
  if (err != cudaSuccess)
  {
    std::cout << cudaGetErrorString(err) << " in " << file << " at line " << line << std::endl;
    exit(EXIT_FAILURE);
  }
}
#define CUDA_HANDLE_ERROR( err ) (CUDA_HandleError( err, __FILE__, __LINE__ ))
 
// fonction kernel s'executant sur le device
__global__ void VecAdd(float* A, float* B, float* C, int N)
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;
  if (i < N)
    C[i] = A[i] + B[i];
}
 
// affichage d'un vecteur
void printVec(std::vector<float> &vec){
    for(auto e : vec) std::cout << e << ", ";
    std::cout << std::endl;
}
 
// code host
int main()
{
  int N = 10;
  size_t size = N * sizeof(float);
 
  // allocation de la memoire sur le host
  std::vector<float> h_A(N, 1.0);
  std::vector<float> h_B(N, 2.0);
  std::vector<float> h_C(N, -1.0);
 
  std::cout << "h_C avant execution kernel : " << std::endl;
  printVec(h_C);
 
  // allocation de la memoire sur le device
  float* d_A;
  CUDA_HANDLE_ERROR( cudaMalloc(&d_A, size) );
  float* d_B;
  cudaMalloc(&d_B, size);
  float* d_C;
  cudaMalloc(&d_C, size);
 
  // poie des vecteur h_A et h_B sur les espaces memoire du device d_A et d_B
  cudaMemcpy(d_A, h_A.data(), size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, h_B.data(), size, cudaMemcpyHostToDevice);
 
  // preparation de la configuration d'execution
  int threadsPerBlock = 256;
  int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
  // execution du kernel
  VecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
  // attendre que le kernel se termine et recuperer la derniere erreur
  CUDA_HANDLE_ERROR( cudaPeekAtLastError() );
  CUDA_HANDLE_ERROR( cudaDeviceSynchronize() );
 
  // copie des donnees du device vers le host (d_C vers h_C)
  cudaMemcpy(h_C.data(), d_C, size, cudaMemcpyDeviceToHost);
 
  std::cout << "h_C apres execution kernel : " << std::endl;
  printVec(h_C);
 
  // liberation de la memoire sur le device
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
}
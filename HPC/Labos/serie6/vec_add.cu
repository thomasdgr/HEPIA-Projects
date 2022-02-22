#include <stdio.h>
#include <cassert>
#include <iostream>

__global__ void vectorAdd(int A[BLOCK_SIZE][BLOCK_SIZE], int B[BLOCK_SIZE][BLOCK_SIZE], int C[BLOCK_SIZE][BLOCK_SIZE]){
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if(row >= h || col >= w){
        return;
    }
    C[row][col] = A[row][col] + B[row][col];
}

int main(){
    int d_A[BLOCK_SIZE][BLOCK_SIZE];
    int d_B[BLOCK_SIZE][BLOCK_SIZE];
    int d_C[BLOCK_SIZE][BLOCK_SIZE];

    int C[BLOCK_SIZE][BLOCK_SIZE];

    for(int i = 0; i < BLOCK_SIZE; i++){
        for(int j = 0; j < BLOCK_SIZE; j++){
            d_A[i][j] = i + j;
            d_B[i][j] = i + j;
        }
    }

    const dim3 BLOCK_SIZE = dim3(3, 1, 1);
    const dim3 GRID_SIZE = dim3(2, 2, 1);

    vectorAdd<<<dimGrid, dimBlock>>>(d_A, d_B, d_C);

    cudaMemcpy(C, d_C, BLOCK_SIZE * BLOCK_SIZE, cudaMemcpyDeviceToHost);

    for(int i = 0; i < BLOCK_SIZE; i++){
        for(int j = 0; j < BLOCK_SIZE; j++){
            printf("%d\n", C[i][j]);
        }
    }
}
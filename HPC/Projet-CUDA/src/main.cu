#include <cstdio>
#include <cassert>
#include <time.h>
#include "laplace_solver.cuh"

int main(int argc, const char * argv[]){
  const size_t N = atoi(argv[1]), M = atoi(argv[2]);
  float *north = (float *)malloc(sizeof(float) * M);
  float *south = (float *)malloc(sizeof(float) * M);
  float *east = (float *)malloc(sizeof(float) * (N - 2));
  float *west = (float *)malloc(sizeof(float) * (N - 2));
  
  for (int k = 0; k < M; k++) {
    north[k] = 1.0;
    south[k] = 2.0;
  }

  for (int k = 0; k < N-2; k++) {    
    west[k] = 3.0;
    east[k] = 4.0;
  }

  clock_t c = clock();
  float *heated = heat_solver(N, M, atoi(argv[3]), north, south, east, west, dim3(atoi(argv[4]), atoi(argv[5]), 1), dim3(atoi(argv[6]), atoi(argv[7]), 1));
  printf("N=%d - M=%d\nT=%d\nTime=%f\n", N,M,atoi(argv[3]), (double)(clock() - c) / CLOCKS_PER_SEC);

  /*for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      printf("%f\t", heated[i * M + j]);
    }
    printf("\n");
  }*/

  // Test: N & S
  for (int k = 0; k < M; k++) {
    assert(heated[k] == north[k]);
    assert(heated[(N-1)*M + k] == south[k]);
  }

  // Test: W & E
  for (int k = 0; k < N-2; k++) {
    assert(heated[(k+1)*M] == west[k]);
    assert(heated[(k+2)*M - 1] == east[k]);
  }

  return 0;
}

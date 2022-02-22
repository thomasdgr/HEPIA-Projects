#include <cstdio>
#include "laplace_solver.cuh"

int main(){
  const size_t N = 9, M = 9;
  float *north = (float *)malloc(sizeof(float) * M);
  float *south = (float *)malloc(sizeof(float) * M);
  float *east = (float *)malloc(sizeof(float) * (N - 2));
  float *west = (float *)malloc(sizeof(float) * (N - 2));
  // on doit faire en sorte que dim3_1.a * dim3_2.a >= M
  // et de la meme manière:     dim3_1.b * dim3_2.b >= N (peut etre inverser M et N)
  // les dim3_1.c et dim3_2.c doivent rester à 1 puisque l'on traite des matrices 2D
  float *heated = heat_solver(N, M, 100, north, south, east, west, dim3(3, 3, 1), dim3(3, 3, 1));
  //float *heated = heat_solver(N, M, 100, north, south, east, west, dim3(3, 3, 1), dim3(3, 3, 1));

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      printf("%f\t", heated[i * M + j]);
    }
    printf("\n");
  }

  return 0;
}

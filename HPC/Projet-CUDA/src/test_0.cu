#include <cstdio>
#include <cassert>
#include "laplace_solver.cuh"

// Test 0:
// Il s'agit d'un exemple de test qui sera exécuté
// lors de la correction. Lisez-le attentivement
// et comprenez bien pourquoi ce test est justifié
int main()
{
  // Initialisation des bords
  const size_t N = 20, M = 10;
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

  // Application de 0 step
  float *domaine = heat_solver(
    N, M, 
    0,
    north, south, 
    east, west,
    dim3(1, 2, 1), 
    dim3(10, 10, 1)
  );

  // Test: N & S
  for (int k = 0; k < M; k++) {
    assert(domaine[k] == north[k]);
    assert(domaine[(N-1)*M + k] == south[k]);
  }

  // Test: W & E
  for (int k = 0; k < N-2; k++) {
    assert(domaine[(k+1)*M] == west[k]);
    assert(domaine[(k+2)*M - 1] == east[k]);
  }

  return 0;
}

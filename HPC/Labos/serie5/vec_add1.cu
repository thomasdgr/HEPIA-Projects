#include <stdio.h>
#include <cassert>
#include <iostream>

// COURS

// CUDA kernel pour l'addition de vecteurs (__global__ est utilisé pour dire que c'est une fonction kernel)
// -> on aura un thread pour chaque élément dans "c"
__global__ void vectorAdd(const int* a, const int* b, int* c, int N) {
  // Thread ID globale
  int tid = (blockIdx.x*blockDim.x) + threadIdx.x;
  // blockIdx.x -> contient l'id du bloc actuel qui execute le code (.x car c'est une grille 1D)
  // Certains ne doivent rien faire !
  if (tid < N) c[tid] = a[tid] + b[tid];
}

int main() {
  // la taille est une puissance de deux, cela est simplement pour assurer
  // les divisions entières par 1024 threads par block (c'est juste du confort)
  const int N = 1 << 28;
  const size_t n_bytes = sizeof(int)*N;

  //std::cout << "Number of integers: " << N << std::endl;
  //std::cout << "Vector size: " << (double) n_bytes/1000000000.0 << " [GB]" << std::endl;

  // les trois vecteurs: C = A + B, ce sont les vecteurs du host (CPU)
  int* h_a = (int*) malloc(n_bytes);
  int* h_b = (int*) malloc(n_bytes);
  int* h_c = (int*) malloc(n_bytes);

  // Du random: 0 à 99 sur les vecteurs du host qui seront copiés sur le device
  // on copie A et B sur le device qui va nous retourner C tel que C = A copié + B copié
  for (int i = 0; i < N; i++) {
    h_a[i] = rand() % 100;
    h_b[i] = rand() % 100;
  }

  // allocation sur le device
  int* d_a; 
  int* d_b;
  int* d_c;
  // allocation de la mémoire sur le gpu -> device
  cudaMalloc(&d_a, n_bytes); // stock les entrées
  cudaMalloc(&d_b, n_bytes); // stock les entrées
  cudaMalloc(&d_c, n_bytes); // stock le résultat

  // Host -> Device
  // on copie h_a dans d_a et h_b dans d_b
  cudaMemcpy(d_a, h_a, n_bytes, cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, h_b, n_bytes, cudaMemcpyHostToDevice);

  // Threads par block (max 1024),
  // C'est la taille du block
  int NUM_THREADS = 1024;

  // Block par Grid: il faut au moins autant de threads que d'éléments.
  // Mais on a que 1024 threads par block (max), donc on n'ajoute un block
  // en plus si nécessaire (i.e. padding).
  // C'est la taille de la grille
  int NUM_BLOCKS = (N + NUM_THREADS - 1) / NUM_THREADS;

  // On lance le Kernel (il faut utiliser les chevrons): on note que c'est asynchrone
  vectorAdd<<<NUM_BLOCKS, NUM_THREADS>>>(d_a, d_b, d_c, N);

  // Device -> Host: on rammène C et on note que cudaMemcpy est synchrone
  cudaMemcpy(h_c, d_c, n_bytes, cudaMemcpyDeviceToHost);

  // Tout est ok ?
  for (int i = 0; i < N; i++) {
    assert(h_c[i] == h_a[i] + h_b[i]);
  }

  // On libère la mémoire
  free(h_a);
  free(h_b);
  free(h_c);

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

  //std::cout << "Addition de vecteurs: OK" << std::endl;

  return 0;
}
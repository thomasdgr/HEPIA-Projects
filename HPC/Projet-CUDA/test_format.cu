#include <cstdio>
#include "src/laplace_solver.cuh"

int main()
{
    int nb_size = 3;
    const size_t Ns[3] = {30, 15, 17}; // Lignes
    const size_t Ms[3] = {15, 8, 32};  // Colonnes
    // Le produit des dimensions de grids et de blocks peut dépasser MxN.
    // Vous avez la garantie que blockDim.x*gridDim.x >= M (colonnes)
    // et blockDim.y*gridDim.y >= N (lignes).
    const dim3 grids[3] = {dim3(3, 15, 1), dim3(10, 5, 1), dim3(8, 2, 1)};
    const dim3 blocks[3] = {dim3(5, 2, 1), dim3(2, 4, 1), dim3(4, 9, 1)};

    float *north, *south, *east, *west, *heated;
    size_t M, N;
    dim3 grid, block;
    for (size_t i = 0; i < nb_size; i++)
    {
        M = Ms[i];
        N = Ns[i];
        grid = grids[i];
        block = blocks[i];

        printf("MxN : %dx%d\n", M, N);
        printf("grid : %dx%d\n", grid.x, grid.y);
        printf("block : %dx%d\n", block.x, block.y);

        north = (float *)malloc(sizeof(float) * M);
        south = (float *)malloc(sizeof(float) * M);
        east = (float *)malloc(sizeof(float) * (N - 2));
        west = (float *)malloc(sizeof(float) * (N - 2));
        heated = heat_solver(
            N, M, 100,
            north, south, east, west,
            grid, block);
        // Test bidon pour être sûr que la fonction heat_solver
        // retourne bien un pointeur host.
        // Le résultat de ce test n'a pas d'importance pour
        // la vérification du format.
        // Il déclanchera un segfault en cas de non respect des consignes.
        heated[0] -= 1.0e-120;
        if (heated[0] == north[0])
        {
            printf("done for :\nMxN : %dx%d\n", M, N);
            printf("grid : %dx%d\n", grid.x, grid.y);
            printf("block : %dx%d\n", block.x, block.y);
        }
    }

    return 0;
}

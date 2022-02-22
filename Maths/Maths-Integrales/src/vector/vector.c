#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/** @brief
 *  Compute the endianness used by
 *  the architecture.
 *
 *  @return 1 if little-endian, 0 if big-endian
 */
uint8_t get_endianness()
{
    uint32_t endianness = 0x01020304;
    // Return the endianness by accessing the first byte in memory
    // which should be 1 if big-endian and 4 if little-endian
    return *((uint8_t *)(&endianness)) == 4;
}

/** @brief
 *  Create a vector of a given dimension.
 *
 *  @param N The number of dimensions.
 *  @return A dynamically allocated vector
 */
double_vector_t *init_vector(uint32_t N)
{
    double_vector_t *vec = malloc(sizeof(double_vector_t));
    vec->components = malloc(N * sizeof(double));
    vec->N = N;
    if (vec == NULL)
    {
        perror("Can't allocate memory");
        exit(EXIT_FAILURE);
    }
    return vec;
}
/** @brief
 *  Create a vector of a given dimension,
 *  with values from 0 to N excluded.
 *
 *  @param N The number of dimensions.
 *  @return A dynamically allocated vector : [0,1..N-1]
 */
double_vector_t *iota(uint32_t N)
{
    double_vector_t *vec = init_vector(N);
    for (uint32_t i = 0; i < N; i++)
    {
        vec->components[i] = i;
    }
    return vec;
}
/** @brief
 *  Apply a 1d function element-wise
 *  to a given vector, and return the
 *  result in a new vector.
 *
 *  @param vec The argument vector
 *  @param f   The 1d function to apply
 *  @return A dynamically allocated vector : f(X)
 */
double_vector_t *apply_function(double_vector_t *vec, double_function_t f)
{
    double_vector_t *res = init_vector(vec->N);
    for (uint32_t i = 0; i < vec->N; i++)
    {
        res->components[i] = f(vec->components[i]);
    }
    return res;
}
/** @brief
 *  Export a vector into a file.
 *
 *  @param filename The name of the output file
 *  @param vec      The vector to export
 */
void export_vector(const char *filename, double_vector_t *vec)
{
    FILE *output = fopen(filename, "w");

    vector_metadata_t metadata;
    metadata.endianness = get_endianness();
    metadata.size_of_a_component = sizeof(double);
    metadata.number_of_component = vec->N;

    fwrite(&metadata, sizeof(vector_metadata_t), 1, output);
    fwrite(vec->components,
           metadata.size_of_a_component,
           metadata.number_of_component,
           output);

    fclose(output);
}
/** @brief
 *  Free a vector.
 *
 *  @param vec A double pointer on a vector
 */
void destroy_vector(double_vector_t **vec)
{
    free((*vec)->components);
    free(*vec);
    *vec = NULL;
}

// conversion d'un tableau de points en une structure vecteur exportée dans un fichier 
// puis lue avec python pour l'affichage avec matplotlib
void convertArrayPointsToDoubleVector(arrayPoints arrayP, double_vector_t* vectorX, double_vector_t* vectorY){
	for (int i = 0; i < arrayP.length;i++){
      vectorX->components[i] = arrayP.array[i].x;
      vectorY->components[i] = arrayP.array[i].y;
  }
}

// exporter un tableau de points dans deux fichiers .vec (un pour la coordonée x et un pour y)
void exportArrayPointsToVector(arrayPoints data, char* nameFileX, char* nameFileY){
	double_vector_t *arrayX = init_vector(data.length);
	double_vector_t *arrayY = init_vector(data.length);
    convertArrayPointsToDoubleVector(data, arrayX, arrayY);

    export_vector(nameFileX, arrayX);
    export_vector(nameFileY, arrayY);

    destroy_vector(&arrayX);
    destroy_vector(&arrayY);
}

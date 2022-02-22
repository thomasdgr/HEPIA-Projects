#ifndef VECTOR_H
#define VECTOR_H
#include <stdint.h>

typedef struct double_vector
{
    uint32_t N; // The dimmension of the vector
    double *components;
} double_vector_t;
// Function pointer, example : double f(double x);
typedef double (*double_function_t)(double);

/*
* The attribute "packed" tells the compiler,
* that the struct should be stored in memory 
* without padding. It's highly recommended,
* if we want to serialize the structure.
* (for example to store it in a file)
*/
typedef struct vector_metadata
{
    uint8_t endianness;          // 1 = little, 0 = big
    uint8_t size_of_a_component; // in bytes
    uint32_t number_of_component;
} __attribute__((packed)) vector_metadata_t;

/** @brief 
 *  Create a vector of a given dimension.
 * 
 *  @param N The number of dimensions.
 *  @return A dynamically allocated vector
 */
double_vector_t *init_vector(uint32_t N);
/** @brief 
 *  Create a vector of a given dimension,
 *  with values from 0 to N excluded.
 * 
 *  @param N The number of dimensions.
 *  @return A dynamically allocated vector : [0,1..N-1]
 */
double_vector_t *iota(uint32_t N);
/** @brief 
 *  Apply a 1d function element-wise
 *  to a given vector, and return the
 *  result in a new vector.
 * 
 *  @param vec The argument vector
 *  @param f   The 1d function to apply
 *  @return A dynamically allocated vector : f(X)
 */
double_vector_t *apply_function(double_vector_t *vec, double_function_t f);
/** @brief 
 *  Export a vector into a file.
 * 
 *  @param filename The name of the output file
 *  @param vec      The vector to export
 */
void export_vector(const char *filename, double_vector_t *vec);
/** @brief 
 *  Free a vector.
 * 
 *  @param vec A double pointer on a vector
 */
void destroy_vector(double_vector_t **vec);

#endif
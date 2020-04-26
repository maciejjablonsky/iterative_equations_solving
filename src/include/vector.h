#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/** @file */


typedef unsigned int len_t;
typedef unsigned int uint;
typedef double element_t; /**< Type of element stored in vectors or matrices */

/**
 * @brief Struct to store data of vector
 */
struct vector {
    element_t * elements; /**< Continuous  block of memory containing elements of vector */
    len_t len; /**< Length of vector */
};

/**
 * @brief Macro simplifying initialization of \ref vector
 */
#define vector_struct(...) (struct vector){__VA_ARGS__}

/**
 * @brief Computes scalar product of two equal length vectors
 * @param vecA Elements of left vector
 * @param vecB Elements of right vector
 * @param len Length of each vector
 * @return Result of computing as scalar value
 */
element_t vector__dot_product(const element_t *vecA, const element_t *vecB, int len);

/**
 * @brief Computes euclidean norm of \ref vector (length of vector)
 * @param vec Input vector
 * @return Result norm
 */
element_t vector__norm(struct vector * vec);


#endif //VECTOR_H

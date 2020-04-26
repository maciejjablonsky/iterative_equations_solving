#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

/** @file */

/**
 * @brief Object used to store data of used matrix
 */
struct matrix {
    element_t *elements; /**< Continuous block of memory containing row-wise elements of matrix */
    len_t rows; /**< Number of rows in matrix */
    len_t cols; /**< Number of elements in each row */
};

/**
 * @brief Macro allowing initialization matrix structure
 */
#define matrix_struct(...) (struct matrix){__VA_ARGS__}

/**
 * @brief Allocates memory for matrix and \ref matrix.elements
 * @param elements_length Number of elements in created matrix
 * @return Pointer to matrix with \ref matrix.elements pointing to memory for elements
 */
struct matrix *__malloc_matrix(len_t elements_length);

/**
 * @brief Allocates zeroed memory for matrix and \ref matrix.elements
 * @param elements_length Number of elements in created matrix
 * @return Pointer to matrix with \ref matrix.elements pointing to memory for elements
 */
struct matrix *__calloc_matrix(len_t elements_length);

/**
 * @brief Initializes band matrix
 * @param[in] first_row First \p len non zero elements from first row
 * @param len Number of elements in \p first_row
 * @param rows number of rows in output matrix
 * @param cols number of rows in output matrix, must be the same as rows for now
 * @return struct matrix allocated on heap with elements set to demanded band pattern
 */
struct matrix *matrix__gen_band(element_t *first_row, len_t len, len_t rows, len_t cols);

/**
 * @brief Extracts right triangular matrix from \p mat.
 *
 * All elements of \p mat are set to zero except elements above \p start_diag diagonal
 * @param[in, out] mat Edited square matrix
 * @param start_diag Index of diagonal to start extracting, 0 means main diagonal, 1 means one above main diagonal etc.
 * @return Pointer to \p mat or NULL when error occurred
 */
struct matrix *matrix__triu(struct matrix *mat, uint start_diag);

/**
 * @brief extracts left triangular matrix from source and stores result in #mat
 * @param[in, out] mat edited square matrix
 * @param start_diagonal index of row below diagonal to start copying, 0 means diagonal
 * @return pointer to #mat or NULL when error occured
 */
struct matrix *matrix__tril(struct matrix *mat, uint start_diagonal);

/**
 *
 * @param n number of rows
 * @return vertical vector of n ones
 */
struct matrix *matrix__ones(len_t n);

struct matrix *matrix__b(len_t n, float magic_f);

/**
 * @brief sets diagonal elements to zero
 * @param[in,out] mat processed matrix
 */
void matrix__zero_diag(struct matrix *mat);

/**
 * @brief multiplies matrix element by element
 * @param[in, out] mat processed matrix
 * @param multiplier
 */
void matrix__multiply_by_scalar(struct matrix *mat, element_t multiplier);

/**
 * @brief subtracts element by element right from left matrix and stores result in left
 * @param[in,out] left left side matrix
 * @param[in] right right side matrix
 * @return pointer to left matrix, or NULL when error occured
 */
struct matrix *matrix__sub(struct matrix *left, const struct matrix *right);

/**
 * @brief multiplies two matrices
 * @param[in] A left matrix
 * @param[in] B right matrix
 * @return new allocated matrix with result
 */
struct matrix *matrix__mul(const struct matrix *A, const struct matrix *B);

/**
 * @brief copies all matrix elements into new memory
 * @param[in] original source to copy
 * @return new allocated matrix with copy of #original
 */
struct matrix *matrix__deep_copy(const struct matrix *original);

/**
 * @brief sets all elements except diagonal to zeros
 * @param[in, out] mat edited square matrix
 * @return pointer to #mat
 */
struct matrix *matrix__diag(struct matrix *mat);

/**
 * @param[in] mat source matrix
 * @return new allocated transposed matrix
 */
struct matrix *matrix__transpose(const struct matrix *mat);

/**
 * @param[in] mat
 * @return product of matrix rows and columns
 */
len_t matrix__len(const struct matrix *mat);

/**
 * @brief   multiplies two matrices row by row
 *          if C = A*B, then C = A* B_transposed if multiplied row by row
 * @param[in] left left matrix
 * @param[in] right_transposed
 * @return new allocated matrix with result
 */
struct matrix *
matrix__multiply_one_by_second_transposed(const struct matrix *left, const struct matrix *right_transposed);

/**
 * @brief frees memory of allocated matrix
 * @param mat matrix to delete
 * @return NULL
 */
struct matrix *matrix__delete(struct matrix *mat);

/**
 * @brief adds right matrix to left element by element and stores result in left matrix
 * @param[in, out] left left matrix
 * @param[in] right right matrix
 * @return pointer to left matrix or NULL when error occured
 */
struct matrix * matrix__add(struct matrix * left, const struct matrix *right);

/**
 * @brief appends print of matrix elements to file
 * @param[in] mat matrix to print
 * @param[in] filename file to store print
 */
void debug_print_matrix_to_file(const struct matrix *mat, const char *filename, const char *mode);

/**
 * @brief creates square matrix with diagonal elements set to 1 and others to 0
 * @param len number of rows or columns
 * @return heap allocated matrix object with initialized elements
 */
struct matrix * matrix__eye(uint len);

/**
 * @brief saves matrix in csv format file
 * @param mat matrix to save
 * @param path path to output file
 */
void matrix__to_csv(const struct matrix * mat, const char * path);

/**
 * @brief prints matrix to stdout max to 5 elements in rows and cols
 * @param mat matrix to print
 */
void matrix__print_compact(const struct matrix *mat, len_t max_rows_cols);
#endif // MATRIX_H

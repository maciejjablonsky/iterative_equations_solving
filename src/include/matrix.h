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
 * @param[in] values Length of non zero elements from values
 * @param len Number of elements in \p values
 * @param rows number of rows in output matrix
 * @param cols number of rows in output matrix, must be the same as rows for now
 * @return struct matrix allocated on heap with elements set to demanded band pattern
 */
struct matrix *matrix__gen_band(element_t *values, len_t len, len_t rows, len_t cols);

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
 * @brief Extracts left triangular matrix from \p mat.
 *
 * All elements of \p mat are set to zero except elements below \p start_diag diagonal
 * @param[in, out] mat Edited square matrix
 * @param start_diag Index of diagonal to start extracting, 0 means main diagonal, 1 means one below main diagonal etd.
 * @return Pointer to \p mat or NULL when error occurred
 */
struct matrix *matrix__tril(struct matrix *mat, uint start_diag);

/**
 * @brief Creates matrix of [\p n, 1] shape
 * @param n Number of rows
 * @return Vertical vector of n ones
 */
struct matrix *matrix__ones(len_t n);

/**
 * @brief Creates vector of elements equal to sin(i*(\p magic_f + 1))
 *
 * Exercise specific function, not much to say.
 * @param n Number of rows in vector.
 * @param magic_f Magic value.
 * @return New matrix with elements set to above sin() values.
 */
struct matrix *matrix__b(len_t n, float magic_f);

/**
 * @brief Sets diagonal elements to zero.
 * @param[in,out] mat Edited matrix
 */
void matrix__zero_diag(struct matrix *mat);

/**
 * @brief Multiplies matrix element by element by \p multiplier
 * @param[in, out] mat Multiplied matrix
 * @param multiplier Value by which matrix elements are multiplied
 */
void matrix__mul_by_scalar(struct matrix *mat, element_t multiplier);

/**
 * @brief Subtracts element by element right from left matrix and stores result in left
 * @param[in,out] left Left side matrix
 * @param[in] right Right side matrix
 * @return Pointer to left matrix, or NULL when error occurred
 */
struct matrix *matrix__sub(struct matrix *left, const struct matrix *right);

/**
 * @brief Multiplies two matrices
 * @param[in] A Left matrix
 * @param[in] B Right matrix
 * @return Pointer to new \ref matrix with result
 */
struct matrix *matrix__mul(const struct matrix *A, const struct matrix *B);

/**
 * @brief Copies all matrix elements into new memory
 * @param[in] original Matrix to copy
 * @return New allocated matrix with copy of \p original
 */
struct matrix *matrix__deep_copy(const struct matrix *original);

/**
 * @brief Sets all elements except diagonal to zeros
 * @param[in, out] mat Edited square matrix
 * @return Pointer to \p mat
 */
struct matrix *matrix__diag(struct matrix *mat);

/**
 * @brief Transposes matrix
 * @param[in] mat Source matrix
 * @return Pointer to new transposed matrix
 */
struct matrix *matrix__transpose(const struct matrix *mat);

/**
 * @brief Calculates number of elements in \p mat
 * @param[in] mat Matrix
 * @return Product of matrix rows and columns
 */
len_t matrix__len(const struct matrix *mat);

/**
 * @brief Multiplies two matrices row by row
 *
 * If C = A*B, then C = A* B_transposed if multiplied row by row
 * @param[in] left Left matrix
 * @param[in] Right_transposed
 * @return Pointer to new allocated matrix with result
 */
struct matrix *
matrix__multiply_one_by_second_transposed(const struct matrix *left, const struct matrix *right_transposed);

/**
 * @brief Frees memory of allocated \ref matrix and \ref matrix.elements
 * @param mat Matrix to delete
 * @return NULL, should be assigned to pointer which stored \p mat address
 */
struct matrix *matrix__delete(struct matrix *mat);

/**
 * @brief Adds right matrix to left element by element and stores result in left matrix
 * @param[in, out] left Left matrix
 * @param[in] right Right matrix
 * @return Pointer to left matrix or NULL when error occurred
 */
struct matrix * matrix__add(struct matrix * left, const struct matrix *right);

/**
 * @brief Prints matrix elements to file
 *
 * Depending on \p mode, "w" clears file before write, "a" appends to existing print
 * @param[in] mat Matrix to print
 * @param[in] path File to store print
 * @param mode String with \ref FILE like mode to open file
 */
void debug_print_matrix_to_file(const struct matrix *mat, const char *path, const char *mode);

/**
 * @brief Creates square matrix with diagonal elements set to 1 and others to 0
 * @param len Number of rows or columns
 * @return Pointer to new matrix with initialized elements
 */
struct matrix * matrix__eye(uint len);

/**
 * @brief Saves matrix in csv format file
 * @param mat Matrix to save
 * @param path Path to output file
 */
void matrix__to_csv(const struct matrix * mat, const char * path);

/**
 * @brief Prints matrix in such way so middle elements are replaced by "..." if rows/cols are too long to display
 * @param[in] mat Matrix to print
 * @param max_rows_cols Maximum number of elements to display
 */
void matrix__print_compact(const struct matrix *mat, len_t max_rows_cols);
#endif // MATRIX_H

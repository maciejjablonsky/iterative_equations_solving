#ifndef LINEAR_EQUATIONS_H
#define LINEAR_EQUATIONS_H

#include "matrix.h"

/** @file */

#ifdef TEST
#define SOLUTION_EPSILON (1e-9)
#else
/**
 * @brief Solution accuracy required to stop iterative methods
 */
#define SOLUTION_EPSILON (1e-9)
#endif

/**
 * @brief Creates matrix equal to \p A * \p solution - \p b
 * @param[in] A System matrix in linear equations system
 * @param[in] solution Solution vector
 * @param[in] b Right member vector
 * @return Pointer to new matrix with residuum
 */
struct matrix *lin_eq_sys__residuum(const struct matrix *A, const struct matrix *solution, const struct matrix *b);

/**
 * @brief Iterative method to solve \p A * x = \p b equation
 * @param[in] A System matrix
 * @param b Right member vector
 * @return Pointer to new matrix with solution
 */
struct matrix *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b);

/**
 * @brief Initializes structures in \ref lin_eq_sys__jacobi
 * @param[in] A System matrix
 * @param[in] b Right member vector
 * @param[out] x Vector of ones
 * @param[out] D Diagonal of \p A
 * @param L_U Sum of left and right triangular matrices of \p A
 */
void __lin_eq_sys_jacobi__init(struct matrix *A, struct matrix *b, struct matrix **x, struct matrix **D,
                               struct matrix **L_U);

/**
 * @brief Cleans in \ref lin_eq_sys__jacobi()
 * @param[in] D Diagonal of system matrix
 * @param[in] L_U Sum of lower and upper triangular matrices of system matrix
 */
void __lin_eq_sys_jacobi__end(struct matrix **D, struct matrix **L_U);

/**
 * @brief Computation kernel in \ref lin_eq_sys__jacobi, computes one step of method,
 * uses \ref lin_eq_sys__forward_substitution
 * @param[in] L_U Sum of lower and upper triangular matrices of system matrix
 * @param[in] D Diagonal of system matrix
 * @param[in] b Right member vector
 * @param[in, out] x Last solution vector
 */
void __lin_eq_sys_jacobi__hot_loop_step(struct matrix *L_U, struct matrix *D, struct matrix *b, struct matrix **x);

/**
 * @brief Computation kernel in \ref lin_eq_sys__jacobi optimized version, computes one step of method,
 * but uses \ref lin_eq_sys__forward_substitution_when_left_diagonal
 * @param[in] L_U Sum of lower and upper triangular matrices of system matrix
 * @param[in] D Diagonal of system matrix
 * @param[in] b Right member vector
 * @param[in, out] x Last solution vector
 */
void __lin_eq_sys_jacobi_optimized__hot_loop_step(struct matrix *L_U, struct matrix *D, struct matrix *b, struct matrix **x);

/**
 * @brief Iterative method to solve \p A * x = \p b equation
 * @param[in] A System matrix
 * @param[in] b Right member vector
 * @return Pointer to new matrix with solution
 */
struct matrix *lin_eq_sys__gauss_seidel(struct matrix *A, struct matrix *b);

/**
 * @brief Initializes structures in \ref lin_eq_sys__gauss_seidel
 * @param[in] A System matrix
 * @param[in] b Right member vector
 * @param[out] x Solution vector with ones
 * @param[out] D_L Sum of diagonal and left triagnular matrix of \p A
 * @param[out] U Right triangular matrix of \p A
 */
void __lin_eq_sys_gauss_seidel__init(struct matrix *A, struct matrix *b, struct matrix **x, struct matrix **D_L,
                                     struct matrix **U);

/**
 * @brief Computation kernel in \ref lin_eq_sys__gauss_seidel, computes one iteration,
 * uses \ref lin_eq_sys__forward_substitution
 * @param[in] U Right triangular matrix of system matrix
 * @param[in] D_L Sum of diagonal and left triagnular matrix of system matrix
 * @param[in] b Right member vector
 * @param[in, out] x Solution vector
 */
void __lin_eq_sys_gauss_seidel__hot_loop_step(struct matrix *U, struct matrix *D_L,
                                              struct matrix *b, struct matrix **x);

/**
 * @brief Cleans in \ref lin_eq_sys__gauss_seidel
 * @param[in] D_L Sum of diagonal and left triagnular matrix of system matrix
 * @param U Right triangular matrix of system matrix
 */
void __lin_eq_sys_gauss_seidel__end(struct matrix **D_L, struct matrix **U);

/**
 * @brief Calculates norm of residuum of \p A * \p x = \p b and checks if norm is below \ref SOLUTION_EPSILON
 * @param[in] A System matrix
 * @param[in] x Solution vector
 * @param[in] b Right member vector
 * @returns true if norm below epsilon, norm equals infinity of norm is NaN
 * false when norm is above or equal to epsilon
 */
bool lin_eq_sys__is_solution_close_enough(struct matrix *A, struct matrix *x, struct matrix *b);

/**
 * @brief Calculates solution of \p L * x = \p b by forward substitution
 * @param[in] L Left triangular matrix
 * @param[in, out] b Right member vector, memory used for result, requires new copy each time
 * @return Pointer to result
 */
struct matrix *lin_eq_sys__forward_substitution(struct matrix *L, struct matrix *b);

/**
 * @brief Calculates solution of L * x = \p b by forward substitution, but omits some calculations when L is diagonal
 * @param[in] diagonal Diagonal matrix
 * @param[in, out] b Right member vector, memory used for result, requires new copy each time
 * @return Pointer to result
 */
struct matrix *lin_eq_sys__forward_substitution_when_left_diagonal(struct matrix *diagonal, struct matrix *b);

/**
 * @brief Calculates solution of \p U * x = \p b by bacward substitution
 * @param[in] U Right triangular matrix
 * @param[in] b Right member vector
 * @return Pointer to new matrix with solution
 */
struct matrix *lin_eq_sys__backward_substitution(struct matrix *U, struct matrix *b);

/**
 * @brief Calculates solution of \p A * x = \b by LU decomposition
 * @param[in] A System matrix
 * @param[in] b Right member vector
 * @return Pointer to new matrix with solution
 */
struct matrix *lin_eq_sys__solve_using_LU_decomposition(struct matrix *A, struct matrix *b);

/**
 * @brief Takes two matrices of the same size and does LU decomposition
 * @param[in, out] L eye matrix, after call stores lower triangular matrix of decomposition
 * @param[in, out] U square matrix initialized to system matrix, after call stores upper triangular matrix of decomposition
 */
void lin_eq_sys__LU_decomposition(struct matrix *L, struct matrix *U);

#endif // LINEAR_EQUATIONS_H

#include "linear_equations.h"
#include "logging.h"
#include <stdlib.h>
#include <time.h>

struct matrix *lin_eq_sys__residuum(const struct matrix *A, const struct matrix *solution, const struct matrix *b) {
        struct matrix *residuum = matrix__mul(A, solution);
        if (residuum == NULL) {
                LOG_ERROR("Can't calculate residuum, multiplication returned NULL.");
                return NULL;
        }
        if (matrix__sub(residuum, b) == NULL) {
                LOG_ERROR("Can't calculate residuum, subtraction returned NULL.");
                matrix__delete(residuum);
                return NULL;
        };
        return residuum;
}

struct matrix *lin_eq_sys__forward_substitution(struct matrix *L, struct matrix *b) {
        for (int i = 0; i < b->rows; ++i) {
                element_t res = b->elements[i];
                for (int j = 0; j < i; ++j) {
                        res -= L->elements[i*L->cols +j] * b->elements[j];
                }
                b->elements[i] = res / L->elements[i*(L->cols + 1)];
        }
        return b;
}

void __lin_eq_sys_jacobi__init(struct matrix *A, struct matrix *b, struct matrix **x, struct matrix **D,
                               struct matrix **L_U) {
        *x = matrix__ones(b->rows);
        *D = matrix__deep_copy(A);
        matrix__diag(*D);
        *L_U = matrix__deep_copy(A);
        matrix__zero_diag(*L_U);
}

void __lin_eq_sys_jacobi__end(struct matrix **D, struct matrix **L_U) {
        *D = matrix__delete(*D);
        *L_U = matrix__delete(*L_U);
}

void __lin_eq_sys_jacobi__hot_loop_step(struct matrix *L_U, struct matrix *D, struct matrix *b, struct matrix **x) {
        struct matrix *x_next = matrix__mul(L_U, *x);
        matrix__delete(*x);
        matrix__multiply_by_scalar(x_next, -1);
        matrix__add(x_next, b);
        *x = lin_eq_sys__forward_substitution_when_left_diagonal(D, x_next);
        matrix__delete(x_next);
}

struct matrix *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b) {
        struct matrix *x, *D, *L_U;
        __lin_eq_sys_jacobi__init(A, b, &x, &D, &L_U);

        while (!lin_eq_sys__is_solution_close_enough(A, x, b)) {
                __lin_eq_sys_jacobi__hot_loop_step(L_U, D, b, &x);
        }
        __lin_eq_sys_jacobi__end(&D, &L_U);
        return x;
}

struct lin_eq_sys_performance __lin_eq_sys_perf__jacobi(struct matrix *A, struct matrix *b) {
        struct lin_eq_sys_performance perf_data;
        perf_data.matrix_size = A->rows;

        clock_t init_time_start = clock();
        struct matrix *x, *D, *L_U;
        __lin_eq_sys_jacobi__init(A, b, &x, &D, &L_U);
        perf_data.init_time_seconds = (double)(clock() - init_time_start)/CLOCKS_PER_SEC;

        int iterations  = 0;
        clock_t hot_loop_time = clock();
        while (!lin_eq_sys__is_solution_close_enough(A, x, b)) {
                __lin_eq_sys_jacobi__hot_loop_step(L_U, D, b, &x);
                iterations++;

//                struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
//                element_t norm = vector__norm(&vector_struct(
//                        .elements = residuum->elements, .len = residuum->rows)
//                );
//                matrix__delete(residuum);
                //printf("\rnorm: %-20.10lf", norm);
        }
        perf_data.hot_loop_time_seconds = (double)(clock() - hot_loop_time)/CLOCKS_PER_SEC;
        perf_data.iterations = iterations;
        perf_data.solution = x;

        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        element_t norm = vector__norm(&vector_struct(
                .elements = residuum->elements, .len = residuum->rows)
        );
        matrix__delete(residuum);
        perf_data.solution_norm = norm;

        clock_t cleaning_time = clock();
        __lin_eq_sys_jacobi__end(&D, &L_U);
        perf_data.cleaning_time_seconds = (double)(clock() - cleaning_time)/CLOCKS_PER_SEC;
        return perf_data;
}

struct matrix *lin_eq_sys__gauss_seidel(struct matrix *A, struct matrix *b, int *iterations) {
        struct matrix *x = matrix__ones(matrix__len(b));
        struct matrix *D_L = matrix__deep_copy(A);
        matrix__tril(D_L, 0);
        struct matrix *U = matrix__deep_copy(A);
        matrix__triu(U, 1);
        int iter = 0;
        clock_t start = clock();
        while (!lin_eq_sys__is_solution_close_enough(A, x, b)) {
                struct matrix *x_next = matrix__mul(U, x);
                matrix__delete(x);
                matrix__multiply_by_scalar(x_next, -1);
                matrix__add(x_next, b);
                x_next = lin_eq_sys__forward_substitution(D_L, x_next);
                x = x_next;
                iter++;
        }
        clock_t end = clock();
        printf("just loop time: %lf [s]\n", (double)(end - start)/CLOCKS_PER_SEC);
        *iterations = iter;
        matrix__delete(D_L);
        matrix__delete(U);
        return x;
}


bool lin_eq_sys__is_solution_close_enough(struct matrix *A, struct matrix *x, struct matrix *b) {
        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        element_t norm = vector__norm(&vector_struct(
                .elements = residuum->elements, .len = residuum->rows)
        );
        matrix__delete(residuum);
        if (__isnanl(norm)) {
                LOG_ERROR("Norm is not a number.\n");
                return true;
        } else if (__isinfl(norm)) {
                LOG_ERROR("Norm reached infinity.\n");
                return true;
        } else
                return norm <= SOLUTION_EPSILON;
}

struct matrix *lin_eq_sys__forward_substitution_when_left_diagonal(struct matrix *diagonal, struct matrix *b) {
        struct matrix *result = __calloc_matrix(matrix__len(b));
        if (result == NULL)
                return NULL;
        result->cols = 1;
        result->rows = b->rows;
        for (int i = 0; i < b->rows; ++i) {
                result->elements[i] = b->elements[i] / diagonal->elements[i * (diagonal->cols + 1)];
        }
        return result;
}

struct matrix *lin_eq_sys__backward_substitution(struct matrix *U, struct matrix *b) {
        struct matrix *result = __malloc_matrix(matrix__len(b));
        if (result == NULL)
                return NULL;
        result->cols = 1;
        result->rows = b->rows;
        for (int i = b->rows - 1; i >= 0; --i) {
                result->elements[i] = b->elements[i];
                element_t cumsum = 0;
                for (int j = i + 1; j < b->rows; ++j) {
                        cumsum += U->elements[i * U->cols + j] * result->elements[j];
                }
                result->elements[i] -= cumsum;
                result->elements[i] /= U->elements[i * (U->cols + 1)];
        }
        return result;
}

void lin_eq_sys__LU_decomposition(struct matrix *L, struct matrix *U) {
        len_t m = L->rows;
        len_t cols = L->cols;
        element_t *l = L->elements;
        element_t *u = U->elements;
        for (int col = 0; col < m - 1; ++col) {
                for (int row = col + 1; row < m; ++row) {
                        element_t l_mul = l[row * cols + col] = u[row * cols + col] / u[col * (cols + 1)];
                        for (int x = col; x < m; ++x) {
                                u[row * cols + x] -= l_mul * u[col * cols + x];
                        }
                }
        }
}

struct matrix *lin_eq_sys__solve_using_LU_decomposition(struct matrix *A, struct matrix *b) {
        struct matrix * U = A;
        struct matrix * L = matrix__eye(b->rows);
        struct matrix * b_copy = matrix__deep_copy(b);
        lin_eq_sys__LU_decomposition(L, U);
        struct matrix * y = lin_eq_sys__forward_substitution(L, b_copy);
        struct matrix * x = lin_eq_sys__backward_substitution(U, y);
        matrix__delete(L);
        matrix__delete(b_copy);
        return x;
}

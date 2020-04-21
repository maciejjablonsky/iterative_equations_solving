#include "linear_equations.h"
#include "logging.h"
#include <stdlib.h>

struct matrix *lin_eq_sys__residuum(struct matrix *A, struct matrix *solution, struct matrix *b) {
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
        struct matrix *result = __calloc_matrix(matrix__len(b));
        if (result == NULL)
                return NULL;
        result->cols = 1;
        result->rows = b->rows;
        for (int i = 0; i < b->rows; ++i) {
                result->elements[i] = b->elements[i];
                for (int j = 0; j < i; ++j) {
                        result->elements[i] -= L->elements[i * L->cols + j] * result->elements[j];
                }
                result->elements[i] /= L->elements[i * (L->cols + 1)];
        }
        return result;
}

struct matrix *lin_eq_sys__jacobi(struct matrix *A, struct matrix *b, int *iterations) {
        struct matrix *x = matrix__ones(b->rows);

        struct matrix *D = matrix__deep_copy(A);
        matrix__diag(D);
        struct matrix *L_U = matrix__deep_copy(A);
        matrix__zero_diag(L_U);

        int iter = 0;
        while (lin_eq_sys__is_solution_close_enough(A, x, b)) {
                struct matrix *x_next = matrix__mul(L_U, x);
                matrix__delete(x);
                matrix__multiply_by_scalar(x_next, -1);
                matrix__add(x_next, b);
                x = lin_eq_sys__forward_substitution_when_left_diagonal(D, x_next);
                matrix__delete(x_next);
                iter++;
        }
        matrix__delete(D);
        matrix__delete(L_U);
        *iterations = iter;
        return x;
}

struct matrix * lin_eq_sys__gauss_seidel(struct matrix * A, struct matrix * b, int *iterations) {
        struct matrix * x = matrix__ones(matrix__len(b));
        struct matrix * D_L = matrix__deep_copy(A);
        matrix__tril(D_L, 0);
        struct matrix * U = matrix__deep_copy(A);
        matrix__triu(U, 1);
        int iter = 0;
        while (lin_eq_sys__is_solution_close_enough(A, x, b)) {
                struct matrix * x_next = matrix__mul(U, x);
                matrix__delete(x);
                matrix__multiply_by_scalar(x_next, -1);
                matrix__add(x_next, b);
                x = lin_eq_sys__forward_substitution(D_L, x_next);
                matrix__delete(x_next);
                iter++;
        }
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
                exit(-1);
        } else if (__isinfl(norm)) {
                LOG_ERROR("Norm reached infinity.\n");
                exit(-1);
        } else
                return norm > SOLUTION_EPSILON;
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
        struct matrix * result = __malloc_matrix(matrix__len(b));
        if (result == NULL)
                return NULL;
        result->cols = 1;
        result->rows = b->rows;
        for (int i = b->rows - 1; i >= 0 ; --i) {
                result->elements[i] = b->elements[i];
                for (int j = i + 1; j < b->rows; ++j) {
                        result->elements[i] -= U->elements[i*U->cols + j] * result->elements[j];
                }
                result->elements[i] /= U->elements[i * (U->cols + 1)];
        }
        return result;
}

struct matrix *lin_eq_sys__lu_decomposition(struct matrix *A, struct matrix *b) {
        return NULL;

}

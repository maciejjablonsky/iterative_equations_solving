#include "linear_equations.h"
#include "logging.h"

struct matrix *lin_eq_sys__residuum(struct matrix *A, struct matrix *solution, struct matrix *b) {
        struct matrix *residuum = matrix__multiply(A, solution);
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

        struct matrix *D = matrix__diagonal(A);
        struct matrix *L_U = matrix__copy(A);
        matrix__zero_out_diagonal(L_U);

//        print_matrix_to_file(D, "diagonal.txt");
//        print_matrix_to_file(L_U, "L_U.txt");
//        print_matrix_to_file(x, "x.txt");
        int iter = 0;
        while (lin_eq_sys__is_solution_close_enough(A, x, b)) {
                struct matrix *x_next = matrix__multiply(L_U, x);
//                print_matrix_to_file(x_next, "x_after_mul.txt");
                matrix__delete(x);
                matrix__multiply_by_scalar(x_next, -1);
                matrix__add(x_next, b);
                x = lin_eq_sys__forward_substitution_when_left_diagonal(D, x_next);
                matrix__delete(x_next);
//                print_matrix_to_file(x, "x.txt");
                iter++;
        }
        matrix__delete(D);
        matrix__delete(L_U);
        *iterations = iter;
        return x;
}


bool lin_eq_sys__is_solution_close_enough(struct matrix *A, struct matrix *x, struct matrix *b) {
        struct matrix *residuum = lin_eq_sys__residuum(A, x, b);
        element_t norm = vector__norm(&vector_struct(
                .elements = residuum->elements, .len = residuum->rows)
                        );
//        print_matrix_to_file(residuum, "residuum.txt");
        printf("norm: %Lg\r", norm);
        matrix__delete(residuum);
        return norm > SOLUTION_EPSILON || __isnanl(norm) || __isinf(norm);
}

struct matrix * lin_eq_sys__forward_substitution_when_left_diagonal(struct matrix *L, struct matrix *b) {
        struct matrix *result = __calloc_matrix(matrix__len(b));
        if (result == NULL)
                return NULL;
        result->cols = 1;
        result->rows = b->rows;
        for (int i = 0; i < b->rows; ++i) {
                result->elements[i] = b->elements[i] / L->elements[i * (L->cols + 1)];
        }
        return result;
}
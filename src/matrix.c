#include <stdlib.h>
#include <matrix.h>
#include <logging.h>
#include <string.h>
#include "helper.h"

#define MAGIC_f 5


struct matrix *__malloc_matrix(len_t elements_length) {
        struct matrix *mat = malloc(sizeof(*mat));
        if (mat == NULL)
                return NULL;
        mat->elements = malloc(elements_length * sizeof(*mat->elements));
        if (mat->elements == NULL) {
                free(mat);
                return NULL;
        }
        return mat;
}


struct matrix *__calloc_matrix(len_t elements_length) {
        struct matrix *mat = calloc(1, sizeof(*mat));
        if (mat == NULL)
                return NULL;
        mat->elements = calloc(elements_length, sizeof(*mat->elements));
        if (mat->elements == NULL) {
                free(mat);
                return NULL;
        }
        return mat;
}

struct matrix *matrix__gen_band(element_t *first_row, len_t first_row_len, len_t rows, len_t cols) {
        struct matrix *result = malloc(sizeof(*result));
        element_t *elements = calloc(rows * cols, sizeof(*elements));

        result->elements = elements;
        result->rows = rows;
        result->cols = cols;

        element_t *src_vector = first_row;
        for (size_t i = 0,
                     length = rows - first_row_len + 1,
                     vector_size = first_row_len * sizeof(*elements); i < length; ++i) {
                memcpy(elements + i * (rows + 1), src_vector, vector_size);
        }

        for (size_t i = 0,
                     offset = (rows + 1) * (rows - first_row_len + 1),
                     row_step = rows + 1,
                     size = sizeof(*elements),
                     elements_length = first_row_len - 1,
                     steps = first_row_len - 1;
             i < steps; ++i) {
                memcpy(elements + offset + row_step * i, src_vector, (elements_length - i) * size);
        }

        element_t *reversed_elements = calloc(first_row_len - 1, sizeof(*reversed_elements));
        for (size_t i = 0,
                     elements_length = first_row_len - 1;
             i < elements_length; ++i) {
                reversed_elements[i] = src_vector[first_row_len - i - 1];
        }
        for (size_t offset = (first_row_len - 1) * rows,
                     steps = rows - first_row_len + 1,
                     vector_size = (first_row_len - 1) * sizeof(*reversed_elements),
                     i = 0; i < steps; ++i) {
                memcpy(elements + offset + (rows + 1) * i, reversed_elements, vector_size);
        }
        for (size_t elements_length = first_row_len - 1,
                     offset = (elements_length - 1) * rows,
                     i = 0,
                     steps = elements_length - 1,
                     size = sizeof(element_t);
             i < steps; ++i) {
                memcpy(elements + offset - rows * i, reversed_elements + i + 1, (elements_length - i - 1) * size);
        }
        free(reversed_elements);

        return result;
}

struct matrix *matrix__triu(struct matrix *mat, uint start_diagonal) {
        struct matrix *U = __calloc_matrix(mat->rows * mat->cols);
        if (U == NULL)
                return NULL;
        U->rows = mat->rows;
        U->cols = mat->cols;

        len_t cols = mat->cols;
        for (uint i = 0; i < mat->rows; ++i) {
                len_t offset = i * (cols + 1);
                memcpy(U->elements + offset + start_diagonal, mat->elements + offset + start_diagonal,
                       (cols - i - start_diagonal) * sizeof(*U->elements));
        }
        return U;
}

struct matrix *matrix__tril(struct matrix *mat, uint start_diagonal) {
        struct matrix *L = __calloc_matrix(mat->rows * mat->cols);
        if (L == NULL)
                return NULL;
        L->rows = mat->rows;
        L->cols = mat->cols;

        len_t cols = mat->cols;
        for (uint i = 0; i < mat->rows; ++i) {
                len_t n = (signed) (i + 1 - start_diagonal) < 0 ? 0 : (i + 1 - start_diagonal);
                memcpy(L->elements + i * cols, mat->elements + i * cols, n * sizeof(*L->elements));
        }
        return L;
}


struct matrix *matrix__b(len_t n) {
        struct matrix *b = __malloc_matrix(n);
        if (b == NULL)
                return NULL;
        b->rows = n;
        b->cols = 1;

        for (int i = 0; i < n; ++i) {
                b->elements[i] = sin(to_radians(i * (MAGIC_f + 1)));
        }
        return b;
}

struct matrix *matrix__ones(len_t n) {
        struct matrix *mat = __malloc_matrix(n);
        if (mat == NULL)
                return NULL;
        for (int i = 0; i < n; ++i) {
                mat->elements[i] = 1.;
        }
        mat->rows = n;
        mat->cols = 1;
        return mat;
}


struct vector *jacobi(struct matrix *system, struct matrix *b) {
        struct matrix *x = matrix__ones(b->rows);
        struct matrix *D = matrix__diagonal(system);
        struct matrix *L_U = matrix__copy(system);
        matrix__zero_out_diagonal(L_U);

}


void matrix__zero_out_diagonal(struct matrix *mat) {
        for (int i = 0; i < mat->rows; ++i) {
                mat->elements[i * (mat->cols + 1)] = 0;
        }
}


void matrix_multiply_by_scalar(struct matrix *mat, element_t value) {
        len_t len = mat->rows * mat->cols;
        for (int i = 0; i < len; ++i) {
                mat->elements[i] *= value;
        }
}

struct matrix *matrix__subtraction(struct matrix *left, struct matrix *right) {
        if (left->rows != right->rows || left->cols != right->cols) {
                LOG_ERROR("Cannot subtract matrices of different sizes. [left: %ux%u][right: %ux%u]", left->rows,
                          left->cols, right->rows, right->cols);
                return NULL;
        }
        len_t len = left->rows * left->cols;
        for (int i = 0; i < len; ++i) {
                left->elements[i] -= right->elements[i];
        }
        return left;
}

struct matrix *matrix__copy(const struct matrix *const original) {
        struct matrix *copy = __malloc_matrix(matrix__len(original));
        if (copy == NULL)
                return NULL;
        copy->rows = original->rows;
        copy->cols = original->cols;
        memcpy(copy->elements, original->elements, matrix__len(original)* sizeof(*copy->elements));
        return copy;
}

struct matrix *matrix__diagonal(struct matrix *mat) {
        if (mat->rows != mat->cols) {
                LOG_ERROR("Cannot extract diagonal from not square matrix. [rows = %u][cols = %u]", mat->rows,
                          mat->cols);
                return NULL;
        }
        struct matrix *diagonal = __calloc_matrix(mat->rows * mat->cols);
        if (diagonal == NULL)
                return NULL;
        uint limit = mat->rows * mat->cols;
        for (uint i = 0; i < limit; i += mat->cols + 1) {
                diagonal->elements[i] = mat->elements[i];
        }
        return diagonal;
}

//struct matrix *matrix__multiply(struct matrix *A, struct matrix *B) {
//        if (A->cols != B->rows) {
//                LOG_ERROR("Shapes don't match for multiplication. [left: %ux%u][right: %ux%u]", A->rows, A->cols,
//                          B->rows, B->cols);
//                return NULL;
//        }
//        struct matrix *transposed_B = matrix__transpose(B);
//        struct mat2d_shape result_shape = {A->shape.rows, B->shape.cols};
//
//        element_t *result_elements = matrix__multiply_rows(A->elements, transposed_B->elements, A->shape.rows,
//                                                           transposed_B->shape.rows,
//                                                           A->shape.cols);
//        struct matrix_ctor_params params = matrix_ctor_params(.elements = result_elements, .shape = result_shape,
//        .length = result_shape.rows * result_shape.cols,
//        .storage = SHALLOW_COPY);
//        struct matrix *result = matrix__new(&params);
//        matrix__delete(transposed_B);
//        return result;
//}
//
struct matrix *matrix__transpose(struct matrix *mat) {
        struct matrix *transposed = __malloc_matrix(matrix__len(mat));
        if (transposed == NULL) {
                return NULL;
        }
        len_t rows = transposed->cols = mat->rows;
        len_t cols = transposed->rows = mat->cols;

        for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                        transposed->elements[r + rows * c] = mat->elements[c + cols * r];
                }
        }
        return transposed;
}


len_t matrix__len(const struct matrix *mat) {
        return mat->rows * mat->cols;
}
#include <stdlib.h>
#include <matrix.h>
#include <logging.h>
#include <string.h>
#include <float.h>


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

struct matrix *matrix__gen_band(element_t *values, len_t len, len_t rows, len_t cols) {
        struct matrix *result = __calloc_matrix(rows * cols);
        result->rows = rows;
        result->cols = cols;

        // fill all possible rows from upper left to lower right with full length values
        for (size_t i = 0,
                     length = rows - len + 1,
                     vector_size = len * sizeof(*result->elements); i < length; ++i) {
                len_t row = i * rows;
                memcpy(result->elements + row + i, values, vector_size);
        }

        // fill remaining gap in right lower corner
        for (size_t i = 0, size = sizeof(*result->elements); i < len - 1; ++i) {
                len_t row = (rows + 1) * (rows - len + 1);
                len_t col = rows + 1;
                memcpy(result->elements + row + col * i, values, (len - 1 - i) * size);
        }

        // reverse values without first element
        element_t *reversed = calloc(len - 1, sizeof(*reversed));
        for (size_t i = 0, elements_length = len - 1; i < elements_length; ++i) {
                reversed[i] = values[len - i - 1];
        }

        // fill all posibile rows from lower right to upper left with reversed full length values
        for (size_t  steps = rows - len + 1, i = 0; i < steps; ++i) {
                len_t row = (len - 1 + i) * rows;
                memcpy(result->elements + row +  i, reversed, (len - 1) * sizeof(*reversed));
        }
        // fil remaining gap in left upper corner
        for (size_t elements_length = len - 1,
                     i = 0,
                     steps = elements_length - 1; i < steps; ++i) {
                len_t row =(elements_length - 1 - i) * rows;
                memcpy(result->elements + row, reversed + i + 1, (elements_length - i - 1) * sizeof(*reversed));
        }
        free(reversed);

        return result;
}

struct matrix *matrix__triu(struct matrix *mat, uint start_diag) {
        len_t cols = mat->cols;
        len_t rows = mat->rows;
        for (uint i = 0; i < rows - start_diag; ++i) {
                memset(mat->elements + i * cols, 0, (i + start_diag) * sizeof(*mat->elements));
        }
        for (uint i = rows - start_diag; i < rows; ++i) {
                memset(mat->elements + i * cols, 0, cols * sizeof(*mat->elements));
        }
        return mat;
}

struct matrix *matrix__tril(struct matrix *mat, uint start_diag) {
        len_t rows = mat->rows;
        len_t cols = mat->cols;
        for (uint i = 0; i < start_diag; ++i) {
                memset(mat->elements + i * cols, 0, cols * sizeof(*mat->elements));
        }
        for (uint i = 0; i < rows; ++i) {
                memset(mat->elements + (i + start_diag) * cols + i + 1, 0, (cols - i - 1) * sizeof(*mat->elements));
        }
        return mat;
}


struct matrix *matrix__b(len_t n, float magic_f) {
        struct matrix *b = __malloc_matrix(n);
        if (b == NULL)
                return NULL;
        b->rows = n;
        b->cols = 1;

        for (int i = 0; i < n; ++i) {
                b->elements[i] = sin(i * (magic_f + 1));
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

void matrix__zero_diag(struct matrix *mat) {
        for (int i = 0; i < mat->rows; ++i) {
                mat->elements[i * (mat->cols + 1)] = 0;
        }
}


void matrix__mul_by_scalar(struct matrix *mat, element_t multiplier) {
        len_t len = matrix__len(mat);
        for (int i = 0; i < len; ++i) {
                mat->elements[i] *= multiplier;

        }
}

struct matrix *matrix__sub(struct matrix *left, const struct matrix *right) {
        if (left->rows != right->rows || left->cols != right->cols) {
                LOG_ERROR("Cannot subtract matrices of different sizes. [left: %ux%u][right: %ux%u]", left->rows,
                          left->cols, right->rows, right->cols);
                return NULL;
        }
        len_t len = matrix__len(left);
        for (int i = 0; i < len; ++i) {
                left->elements[i] -= right->elements[i];
        }
        return left;
}

struct matrix *matrix__add(struct matrix *left, const struct matrix *right) {
        if (left->rows != right->rows || left->cols != right->cols) {
                LOG_ERROR("Cannot subtract matrices of different sizes. [left: %ux%u][right: %ux%u]", left->rows,
                          left->cols, right->rows, right->cols);
                return NULL;
        }
        len_t len = matrix__len(left);
        for (int i = 0; i < len; ++i) {
                left->elements[i] += right->elements[i];
        }
        return left;
}

struct matrix *matrix__deep_copy(const struct matrix *const original) {
        struct matrix *copy = __malloc_matrix(matrix__len(original));
        if (copy == NULL)
                return NULL;
        copy->rows = original->rows;
        copy->cols = original->cols;
        memcpy(copy->elements, original->elements, matrix__len(original) * sizeof(*copy->elements));
        return copy;
}

struct matrix *matrix__diag(struct matrix *mat) {
        if (mat->rows != mat->cols) {
                LOG_ERROR("Cannot extract diagonal from not square matrix. [rows = %u][cols = %u]", mat->rows,
                          mat->cols);
                return NULL;
        }
        len_t rows = mat->rows;
        len_t cols = mat->cols;
        for (uint i = 0; i < rows; ++i) {
                memset(mat->elements + i * cols, 0, i * sizeof(*mat->elements));
                memset(mat->elements + i * cols + i + 1, 0, (cols - i - 1) * sizeof(element_t));
        }
        return mat;
}

struct matrix *matrix__mul(const struct matrix *A, const struct matrix *B) {
        if (A->cols != B->rows) {
                LOG_ERROR("Shapes don't match for multiplication. [left: %ux%u][right: %ux%u]", A->rows, A->cols,
                          B->rows, B->cols);
                return NULL;
        }
        struct matrix *transposed_B = matrix__transpose(B);


        struct matrix *result = matrix__multiply_one_by_second_transposed(A, transposed_B);
        matrix__delete(transposed_B);
        return result;
}

struct matrix *matrix__transpose(const struct matrix *mat) {
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

struct matrix *
matrix__multiply_one_by_second_transposed(const struct matrix *left, const struct matrix *right_transposed) {
        size_t result_len = left->rows * right_transposed->rows;
        struct matrix *result = __malloc_matrix(result_len);
        if (result == NULL)
                return NULL;
        result->rows = left->rows;
        result->cols = right_transposed->rows;
        int k = 0;
        len_t row_len = left->cols;
        for (int i = 0; i < left->rows; ++i) {
                for (int j = 0; j < right_transposed->rows; ++j) {
                        result->elements[k] = vector__dot_product(left->elements + i * row_len,
                                                                  right_transposed->elements + j * row_len, row_len);
                        ++k;
                }
        }
        return result;
}

struct matrix *matrix__delete(struct matrix *mat) {
        free(mat->elements);
        free(mat);
        return NULL;
}

void debug_print_matrix_to_file(const struct matrix *mat, const char *path, const char *mode) {
        FILE *file = fopen(path, mode);
        for (int i = 0; i < mat->rows; ++i) {
                for (int j = 0; j < mat->cols; ++j) {
                        fprintf(file, "%.15lg\t", mat->elements[i * mat->cols + j]);
                }
                fputc('\n', file);
        }
        fprintf(file, "\n\n");
        fclose(file);
}

struct matrix *matrix__eye(uint len) {
        struct matrix *eye = __calloc_matrix(len * len);
        if (eye == NULL)
                return NULL;
        eye->rows = eye->cols = len;
        for (uint i = 0; i < len; ++i) {
                eye->elements[i * (len + 1)] = 1;
        }
        return eye;
}

void matrix__to_csv(const struct matrix *mat, const char *path) {
        FILE *output_file = fopen(path, "w+");
        if (output_file == NULL) {
                LOG_ERROR("Failed to open file: %s", path);
                return;
        }
        for (int i = 0; i < mat->rows; ++i) {
                for (int j = 0; j < mat->cols - 1; ++j) {
                        fprintf(output_file, "%.*lg,", DBL_DIG, mat->elements[i * mat->cols + j]);
                }
                fprintf(output_file, "%.*lg\r\n", DBL_DIG, mat->elements[i * mat->cols + mat->cols - 1]);
        }
}

void matrix__print_compact(const struct matrix *mat, len_t max_rows_cols) {
        const len_t max_lower = max_rows_cols;
        len_t max_rows_to_print = max_lower > mat->rows ? mat->rows : max_lower;
        len_t max_cols_to_print = max_lower > mat->cols ? mat->cols : max_lower;
        printf("shape: [%ux%u]\n", mat->rows, mat->cols);
        for (int i = 0; i < max_rows_to_print; ++i) {
                for (int j = 0; j < max_cols_to_print; ++j) {
                        printf("% 8.4lf\t", mat->elements[i * mat->cols + j]);
                }
                if (mat->cols > max_cols_to_print) {
                        printf("...\t% 8.4lf", mat->elements[i * mat->cols + mat->cols - 1]);
                }
                putchar('\n');
        }
        if (mat->rows > max_rows_to_print) {
                for (int i = 0; i < max_cols_to_print; ++i) {
                        printf("%8s\t", "...");
                }
                if (mat->cols > max_cols_to_print) {
                        printf("\u0971\u00b7.\t%8s", "...");
                }
                putchar('\n');
                for (int i = 0; i < max_cols_to_print; ++i) {
                        printf("% 8.4lf\t", mat->elements[(mat->rows - 1) * mat->cols + i]);
                }
                if (mat->cols > max_cols_to_print) {
                        printf("...\t% 8.4lf", mat->elements[(mat->rows - 1) * mat->cols + mat->cols - 1]);
                }
                putchar('\n');
        }
        putchar('\n');
}



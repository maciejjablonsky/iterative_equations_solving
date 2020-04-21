#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
bool diag__alloc_zero_block_and_copy_diagonal(int n) {
        struct matrix * mat = &matrix_struct(
                .elements = malloc(n*n*sizeof(element_t)),
                .rows = n, .cols = n
                );

        element_t * diagonal = calloc(n*n, sizeof(element_t));
        if (diagonal == NULL)
                return false;
        uint limit = matrix__len(mat);
        for (uint i = 0; i < limit; i += mat->cols + 1) {
                diagonal[i] = mat->elements[i];
        }
        memcpy(mat->elements, diagonal, n*n*sizeof(element_t));
        return diagonal;
}

bool diag__leave_diagonal_and_zero_out_triangulars(int n) {
        struct matrix * mat = &matrix_struct(
                .elements = malloc(n*n*sizeof(element_t)),
                .rows = n, .cols = n
        );

        len_t rows = n;
        len_t cols = n;
        for (uint i = 0; i < rows; ++i) {
                memset(mat->elements + i*cols, 0, i*sizeof(*mat->elements));
                memset(mat->elements + i*cols + i + 1, 0, (cols - i - 1) *sizeof(element_t));
        }
        return true;
}


int main(void) {
        uint n = 5000;
        clock_t start, end;
        start = clock();
        diag__alloc_zero_block_and_copy_diagonal(n);
        end = clock();
        printf("%s: %lf [s]\n", "diag__alloc_zero_block_and_copy_diagonal", (double)(end - start)/CLOCKS_PER_SEC);

        start = clock();
        diag__leave_diagonal_and_zero_out_triangulars(n);
        end = clock();
        printf("%s: %lf [s]\n", "diag__leave_diagonal_and_zero_out_triangulars", (double)(end - start)/CLOCKS_PER_SEC);
}
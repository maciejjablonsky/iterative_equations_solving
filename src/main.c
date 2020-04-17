#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "direct_gauss.h"

int main() {
        uint n = 991;
        clock_t start= clock();
        struct matrix *A = matrix__new_band(&matrix_ctor_params(
                .elements=(element_t[]){ 10, -1, -1,5 },
                .shape={ n, n },
                .length=4
        ));
        clock_t end = clock();
        for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                        printf("%6.2f ", A->elements[i * n + j]);
                }
                putchar('\n');
        }
//        element_t b[] = {1, 1, 1, 1};
//        clock_t start = clock();
//        element_t *result = direct_gauss__solve(A, b, n);
//        clock_t end = clock();
//
        printf("time: %lf\n", (double) (end - start) / CLOCKS_PER_SEC);


//        matrix__delete(result);
}
#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "direct_gauss.h"

int main() {
        uint n = 50000;
        struct matrix *A = matrix__gen_band(NULL, 0, 0, 0);
        element_t *b = malloc(n*sizeof(*b));
        for (int i = 0; i < n; ++i) {
                b[i] = 3;
        }
        printf("Start timer.\n");
        clock_t start = clock();
        element_t *result = direct_gauss__solve(A, b, n);
        clock_t end = clock();


//        for (int i = 0; i < n; ++i) {
//                for (int j = 0; j < n; ++j) {
//                        printf("%6.2f ", A->elements[i * n + j]);
//                }
//                putchar('\n');
//        }
        float percent = 0;
        for (int i = 0; i < n*n; ++i) {
                percent += A->elements[i] != 0;
        }
        printf("percent %.4f %%\n", percent/(n*n));

        printf("time: %lf [s]\n", (double) (end - start) / CLOCKS_PER_SEC);


//        matrix__delete(result);
}
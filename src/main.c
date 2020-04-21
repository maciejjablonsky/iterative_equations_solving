#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "linear_equations.h"


int main() {
        len_t n = 1000;
        struct matrix *A = matrix__gen_band((element_t[]){10, -1, -1}, 3, n, n);
        struct matrix *b = matrix__b(n);
        print_matrix_to_file(b, "b.txt", "w");
        int i = 0;
        clock_t start = clock();
        struct matrix * res = lin_eq_sys__jacobi(A, b, &i);
        clock_t end = clock();
        print_matrix_to_file(res, "jacobi_result.txt", "w");
        printf("jacobi:\n");
        printf("iterations: %d\n", i);
        printf("wall time: %lf [s]\n", (double)(end - start)/CLOCKS_PER_SEC);
        matrix__delete(res);
        start = clock();
        struct matrix * gauss_seidel = lin_eq_sys__gauss_seidel(A, b, &i);
        end = clock();
        print_matrix_to_file(gauss_seidel, "gauss_seidel_result.txt", "w");
        printf("gauss_seidel:\n");
        printf("iterations: %d\n", i);
        printf("wall time: %lf [s]\n", (double)(end - start)/CLOCKS_PER_SEC);
        matrix__delete(gauss_seidel);
        matrix__delete(A);
        matrix__delete(b);
}
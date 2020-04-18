#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "linear_equations.h"


int main() {
        len_t n = 1000;
        struct matrix *A = matrix__gen_band((element_t[]){12, -1, -1}, 3, n, n);
        struct matrix *b = matrix__b(n);
        print_matrix_to_file(b, "b.txt");
        int i = 0;
        clock_t start = clock();
        time_t start_time = time(NULL);
        struct matrix * res = lin_eq_sys__jacobi(A, b, &i);
        clock_t end = clock();
        time_t end_time = time(NULL);
        print_matrix_to_file(res, "result.txt");
        printf("iterations: %d\n", i);
        printf("proc time: %lf [s]\n", (double)(end - start)/CLOCKS_PER_SEC);
        printf("real time: %lf [s]\n", (double)(end_time - start_time)* 0.001);
        putchar('\n');
        matrix__delete(A);
        matrix__delete(b);
        matrix__delete(res);
}
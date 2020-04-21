#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include "linear_equations.h"


int main() {
        len_t n = 1000;
        struct matrix *A = matrix__gen_band((element_t[]){12, -1, -1}, 3, n, n);
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

        struct matrix * A_copy = matrix__deep_copy(A);
         start = clock();
        struct matrix * lu = lin_eq_sys__solve_using_LU_decomposition(A_copy, b);
        end = clock();
        print_matrix_to_file(lu, "lu_result.txt", "w");
        struct matrix *residuum = lin_eq_sys__residuum(A, lu, b);
        element_t norm = vector__norm(&vector_struct(
                .elements = residuum->elements, .len = residuum->rows)
        );
        printf("norm after lu decomposition: %.lg\n", norm);
        printf("wall time: %lf [s]\n", (double)(end - start)/CLOCKS_PER_SEC);
        matrix__delete(lu);

        matrix__delete(gauss_seidel);
        matrix__delete(A);
        matrix__delete(b);
}
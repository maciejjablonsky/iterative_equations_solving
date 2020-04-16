#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
int main() {
        int n = 991;
        element_t * data = malloc(n*n*sizeof(*data));
        for (int i = 0; i < n*n; ++i) {
                data[i] = i;
        }
        struct matrix * A = matrix__new(&matrix_ctor_params(
                .elements = data,
                .shape = {n, n},
                .length=(n*n)));
        struct matrix * B = matrix__new(&matrix_ctor_params(
                .elements = data,
                .shape = {n,n},
                .length=n*n));
        clock_t start= clock();
        struct matrix * result = matrix__multiplication(A,B);
        clock_t end = clock();
        matrix__delete(result);
        matrix__delete(A);
        matrix__delete(B);
        free(data);
        printf("time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);


}

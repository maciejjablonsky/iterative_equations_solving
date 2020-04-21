#ifndef EQUATIONS_MATRIX_TEST_HELPER_H
#define EQUATIONS_MATRIX_TEST_HELPER_H

#include "matrix.h"

void ASSERT_MATRIX_IS_WITHOUT_INF(struct matrix * actual);

void ASSERT_MATRIX_DEEP_COPY(struct matrix *expected, struct matrix *actual);

void ASSERT_MATRIX_SHALLOW_COPY(struct matrix *expected, struct matrix *actual);

void ASSERT__MATRIX_NOT_CHANGED(struct matrix *before, struct matrix *now);

void ASSERT_MATRIX_NOT_NAN(struct matrix * mat);

void ASSERT_MATRIX_VALID_AND_AS_EXPECTED(struct matrix * expected, struct matrix * actual);

#define print_matrix(mat) \
do {\
        char message[128];\
        TEST_MESSAGE("matrix name: "#mat);\
        for (int i = 0; i < (mat)->rows; ++i) {\
                for (int j = 0; j < (mat)->cols; ++j) {\
                        sprintf(message, "[%dx%d] = %.18Lg", i, j, (mat)->elements[i * (mat)->cols + j]);\
                        TEST_MESSAGE(message);\
                }\
        }\
} while (0)


#endif //EQUATIONS_MATRIX_TEST_HELPER_H

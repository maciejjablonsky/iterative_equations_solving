#ifndef EQUATIONS_MATRIX_TEST_HELPER_H
#define EQUATIONS_MATRIX_TEST_HELPER_H

void ASSERT_MATRIX_DEEP_COPY(struct matrix *expected, struct matrix *actual) {
        TEST_ASSERT_EQUAL(expected->rows, actual->rows);
        TEST_ASSERT_EQUAL(expected->cols, actual->cols);

        len_t len = matrix__len(expected);
        len = matrix__len(actual) > len ? matrix__len(actual) : len;
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected->elements, actual->elements, len);
        TEST_ASSERT_NOT_EQUAL(expected->elements, actual->elements);
}

bool ASSERT_MATRIX_SHALLOW_COPY(struct matrix *expected, struct matrix *actual) {
        TEST_ASSERT_EQUAL(expected->rows, actual->rows);
        TEST_ASSERT_EQUAL(expected->cols, actual->cols);
        TEST_ASSERT_EQUAL_PTR(expected->elements, actual->elements);
}

void ASSERT__MATRIX_NOT_CHANGED(struct matrix *before, struct matrix *now) {
        ASSERT_MATRIX_DEEP_COPY(before, now);
}


#define print_matrix(mat) \
do {\
        char message[128];\
        for (int i = 0; i < (mat)->rows; ++i) {\
                for (int j = 0; j < (mat)->cols; ++j) {\
                        sprintf(message, "e[%dx%d] = %.3Lg", i, j, (mat)->elements[i * (mat)->cols + j]);\
                        TEST_MESSAGE(message);\
                }\
        }\
} while (0)


#endif //EQUATIONS_MATRIX_TEST_HELPER_H

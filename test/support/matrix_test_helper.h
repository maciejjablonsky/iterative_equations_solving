#ifndef EQUATIONS_MATRIX_TEST_HELPER_H
#define EQUATIONS_MATRIX_TEST_HELPER_H

void ASSERT_MATRIX_DEEP_COPY(struct matrix *expected, struct matrix *actual) {
        TEST_ASSERT_NOT_NULL(expected);
        TEST_ASSERT_NOT_NULL(actual);
        TEST_ASSERT_EQUAL(expected->rows, actual->rows);
        TEST_ASSERT_EQUAL(expected->cols, actual->cols);

        len_t len = matrix__len(expected);
        len = matrix__len(actual) > len ? matrix__len(actual) : len;
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(expected->elements, actual->elements, len);
        TEST_ASSERT_NOT_EQUAL(expected->elements, actual->elements);
}

bool ASSERT_MATRIX_SHALLOW_COPY(struct matrix *expected, struct matrix *actual) {
        TEST_ASSERT_NOT_NULL(expected);
        TEST_ASSERT_NOT_NULL(actual);
        TEST_ASSERT_EQUAL(expected->rows, actual->rows);
        TEST_ASSERT_EQUAL(expected->cols, actual->cols);
        TEST_ASSERT_EQUAL_PTR(expected->elements, actual->elements);
}

void ASSERT__MATRIX_NOT_CHANGED(struct matrix *before, struct matrix *now) {
        TEST_ASSERT_NOT_NULL(before);
        TEST_ASSERT_NOT_NULL(now);
        ASSERT_MATRIX_DEEP_COPY(before, now);
}

void ASSERT_MATRIX_NOT_NAN(struct matrix * mat) {
        TEST_ASSERT_NOT_NULL(mat);
        bool nan_occured = false;
        for (int i = 0; i < mat->rows; ++i) {
                for (int j = 0; j < mat->cols; ++j) {
                        char message[128];
                        if (isnanl(mat->elements[i*mat->cols + j])) {
                                sprintf(message, "nan error: [%dx%d] = %Le",i, j, mat->elements[i*mat->cols + j]);
                                TEST_MESSAGE(message);
                                nan_occured = true;
                        }
                }
        }
        if (nan_occured)
                TEST_FAIL_MESSAGE("NaN value in matrix.");
}


void ASSERT_MATRIX_IS_WITHOUT_INF(struct matrix * actual) {
        for (int i = 0; i < actual->rows; ++i) {
                for (int j = 0; j < actual->cols; ++j) {
                        TEST_ASSERT_DOUBLE_IS_NOT_INF(actual->elements[i * actual->cols + j]);
                }
        }
}

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

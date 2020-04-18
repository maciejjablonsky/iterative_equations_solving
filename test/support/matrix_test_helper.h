#ifndef EQUATIONS_MATRIX_TEST_HELPER_H
#define EQUATIONS_MATRIX_TEST_HELPER_H

void one_is_another_deep_copy(struct matrix *one, struct matrix *another) {
        TEST_ASSERT_EQUAL(one->rows, another->rows);
        TEST_ASSERT_EQUAL(one->cols, another->cols);

        len_t len = matrix__len(one);
        len = matrix__len(another) > len ? matrix__len(another) : len;
        TEST_ASSERT_EQUAL_DOUBLE_ARRAY(one->elements, another->elements, len);
        TEST_ASSERT_NOT_EQUAL(one->elements, another->elements);
}

bool one_is_another_shallow_copy(struct matrix *one, struct matrix *another) {
        TEST_ASSERT_EQUAL(one->rows, another->rows);
        TEST_ASSERT_EQUAL(one->cols, another->cols);
        TEST_ASSERT_EQUAL_PTR(one->elements, another->elements);
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

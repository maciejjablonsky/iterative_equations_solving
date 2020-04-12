#include "unity.h"
#include "matrix_internals.h"
#include "matrix.h"

void test_givenElementsToCopy_thenElementsAreCopied(void) {
    // given
    matrix_t matrix;
    matrix_ctor_params_t params = matrix_ctor_params(.shape={2,4}, .elements=(matrix_e_t[]){1,2,3,4,5,6,7,8},
            .length=8);


    // then
    TEST_ASSERT_TRUE(MATRIX__copy_data(&matrix, &params));
    TEST_ASSERT_EQUAL_MEMORY(params.elements, matrix.data, params.length * sizeof(matrix_e_t));
}




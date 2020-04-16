#include "unity.h"
#include "vector.h"
#include "matrix.h"
#include "matrix_internals.h"

#undef givenTwoVectorsOfSameLength
#define givenTwoVectorsOfSameLength(vecA, vecB, len) \
element_t (vecA)[] = {1,2,3,4,5};\
element_t (vecB)[] = {5,3,2,5,4};\
size_t (len) = 5;

#undef thenScalarProductIs
#define thenScalarProductIs(expected, actual) do {\
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);\
} while(0)

void test_givenTwoVectorsOfSameLength_whenDotProduct_thenResultIsValidDotProduct(void) {
	givenTwoVectorsOfSameLength(vecA, vecB, length);

	element_t dot_product = vector__dot_product(vecA, vecB, length);

	thenScalarProductIs(57, dot_product);
}

#undef givenTwoVectorsOfSameLength
#define givenTwoVectorsOfSameLength(vecA, vecB, len) \
element_t (vecA)[] = {54123,21245,3124,456542,52554};\
element_t (vecB)[] = {24325,33243,2435,55353,43452};\
size_t (len) = 5;

#undef thenScalarProductIs
#define thenScalarProductIs(expected, actual) do {\
        TEST_ASSERT_EQUAL_FLOAT(expected, actual);\
} while(0)

void test_givenTwoVectorsOfSameLengthWithBigValues_whenDotProduct_thenResultIsValidDotProduct(void) {
        givenTwoVectorsOfSameLength(vecA, vecB, length);

        element_t dot_product = vector__dot_product(vecA, vecB, length);

        thenScalarProductIs(2.95849422e10, dot_product);
}


#undef givenMatrixLikeArraysOfVectors
#define givenMatrixLikeArraysOfVectors(arrA, arrB, vectors_in_single_array, vec_len)\
element_t (arrA)[] = {  1, 2, 3, 4, 5,\
                        2, 3, 4, 5, 6,\
                        3, 4, 5, 6, 7};\
element_t (arrB)[] = {  9, 8, 7, 6, 5,\
                        8, 7, 6, 5, 4,\
                        7, 6, 5, 4, 3};\
size_t (vectors_in_single_array) = 3;\
size_t (vec_len) = 5;

#undef thenResultVectorIs
#define thenResultVectorIs(expected, actual) do {\
        size_t num = sizeof(expected) / sizeof(*(expected));\
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, num);\
} while(0)

void test_givenTwoArraysOfVectors_whenScalarMultiplyingCorrespondingVectors_thenResultVectorIs(void) {
	givenMatrixLikeArraysOfVectors(arrA, arrB, vectors_in_single_array, vec_len);

	element_t *actual_result = vectors__dot_products(arrA, arrB, vectors_in_single_array, vec_len);

	element_t expected[] = {95, 110, 115};
	thenResultVectorIs(expected, actual_result);
}




//void test_givenTwoMatricesAsArrays_whenScalarMultiplyingWithGivenOrder_thenElementsAre(void) {
//	// given
//	element_t A[] = {1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 3, 4, 5, 6, 7};
//	element_t B_transposed[] = {1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 3, 4, 5, 6, 7};
//	size_t A_rows = 3, A_cols = 5, B_cols = 3;
//	order_t *order_of_multiplying = matrix__order_for_multiplication_with_2nd_transformed(A_rows, B_cols);
//	TEST_ASSERT_NOT_NULL(order_of_multiplying);
//
//	// when
//	// B will be transposed
//	element_t *actual = vectors__dot_products_with_order(A, B_transposed, A_rows, A_cols, order_of_multiplying,
//	                                                     A_rows * B_cols);
//
//	// then
//	element_t expected[] = {55, 70, 85, 70, 90, 110, 85, 110, 135};
//	TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, actual, A_rows * B_cols);
//}
//
//void thenOrderIs(order_t *expected, order_t *actual, size_t num) {
//	char message[1024];
//	for (int i = 0; i < num; ++i) {
//		sprintf(message, "\'row_a\' doesn't match in %d row.", i);
//		TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].row_a, actual[i].row_a, message);
//		sprintf(message, "\'row_b\' doesn't match in %d row.", i);
//		TEST_ASSERT_EQUAL_size_t_MESSAGE(expected[i].row_b, actual[i].row_b, message);
//	}
//}
//

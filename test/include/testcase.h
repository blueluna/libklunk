#ifndef ES_TESTCASE_H
#define ES_TESTCASE_H

#include <stdlib.h>

void test_assert_true(int boolean, const char* expr, const char* filename, const int line);

#define TEST_ASSERT_TRUE(expression) \
	test_assert_true(expression, #expression, __FILE__, __LINE__)

#define TEST_ASSERT_EQUAL(a, b) \
	test_assert_true(a == b, #a " == " #b, __FILE__, __LINE__)

#define TEST_ASSERT_NOT_EQUAL(a, b) \
	test_assert_true(a != b, #a " != " #b, __FILE__, __LINE__)

#define TEST_ASSERT_GT(a, b) \
	test_assert_true(a > b, #a " > " #b, __FILE__, __LINE__)

#define TEST_ASSERT_GTE(a, b) \
	test_assert_true(a >= b, #a " => " #b, __FILE__, __LINE__)

#define TEST_ASSERT_LT(a, b) \
	test_assert_true(a < b, #a " < " #b, __FILE__, __LINE__)

#define TEST_ASSERT_LTE(a, b) \
	test_assert_true(a <= b, #a " <= " #b, __FILE__, __LINE__)

#endif /* ES_TESTCASE_H */

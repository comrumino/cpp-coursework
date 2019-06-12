#include "TestHarness.h"
#include "jstronz-2-1.h"
#include <iostream>
#include <sstream>

TEST(int_ptr_swap, int) {
    int a = 1;
    int b = 2;
    std::stringstream s_expected_swap;
    s_expected_swap << b << a;
    // copy values into test values
    int test_ptr_a = a;
    int test_ptr_b = b;
    std::stringstream s_test_ptr;
    // execute swap by pointer
    int_ptr_swap(&test_ptr_a, &test_ptr_b);
    s_test_ptr << test_ptr_a << test_ptr_b;
    CHECK_EQUAL(s_expected_swap.str(), s_test_ptr.str());
}

TEST(int_ref_swap, int) {
    int a = 1;
    int b = 2;
    std::stringstream s_expected_swap;
    s_expected_swap << b << a;
    // copy values into test values
    int test_ref_a = a;
    int test_ref_b = b;
    std::stringstream s_test_ref;
    // execute swap by reference
    int_ref_swap(test_ref_a, test_ref_b);
    s_test_ref << test_ref_a << test_ref_b;
    CHECK_EQUAL(s_expected_swap.str(), s_test_ref.str());
}

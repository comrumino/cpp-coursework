#include <iostream>
#include "TestHarness.h"
#include "array.h"

TEST(Array, overload_ostream) {  // Verify the trivial case works and all other cases follow from the definition of std::vector
    std::stringstream ss;
    Array arr;
    ss << arr;
    CHECK_EQUAL("0", ss.str());
}

TEST(Array, direct_init) {
    std::stringstream ss;
    Array arr(3);
    ss << arr;
    CHECK_EQUAL("000", ss.str());
}

TEST(Array, put) {
    std::stringstream ss;
    Array arr;
    // verify overwrite
    arr.put(0, 1);
    ss << arr;
    CHECK_EQUAL("1", ss.str());
    // clear stringstream
    ss.str("");
    // verify expand
    arr.put(2, 1);
    ss << arr;
    CHECK_EQUAL("101", ss.str());
}

TEST(Array, contract_by_remove) {
    std::stringstream ss;
    Array arr;
    arr.put(0, 1);
    arr.put(2, 1);  // by put test, it follows that this is {1, 0, 1}
    arr.remove(1);  // the 1st position to the right of begin so the 0 disappears
    ss << arr;
    CHECK_EQUAL("11", ss.str());
}

TEST(Array, subscript_operator_write) {
    std::stringstream ss;
    Array arr;
    arr.put(0, 1);
    arr.put(2, 1);  // by put test, it follows that this is {1, 0, 1}  (*)
    arr[1] = 1;  // by (*) this should be {1, 1, 1}                    (+)
    ss << arr;
    CHECK_EQUAL("111", ss.str());
}

TEST(Array, subscript_operator_read) {
    Array arr;
    arr.put(0, 1);
    arr.put(2, 1);  // by put test, it follows that this is {1, 0, 1}
    CHECK_EQUAL(1, arr[0]);
    CHECK_EQUAL(0, arr[1]);
    CHECK_EQUAL(1, arr[2]);
}

TEST(Array, copy_ctor) {
    std::stringstream ss;
    Array arr;
    arr.put(0, 1);
    arr.put(2, 1);  // by put test, it follows that this is {1, 0, 1}
    Array arr2(arr);
    ss << arr2;
    CHECK_EQUAL("101", ss.str());
}

TEST(Array, assignment_operator) {
    std::stringstream ss;
    Array arr;
    arr.put(0, 1);
    arr.put(2, 1);  // by put test, it follows that this is {1, 0, 1}
    Array arr2 = arr;
    ss << arr2;
    CHECK_EQUAL("101", ss.str());
    // clear stringstream
    ss.str("");
    // Verify nothing unexpected happens
    arr[1] = 1;  // by (+) this is {1, 1, 1}
    ss << arr;
    CHECK_EQUAL("111", ss.str());
    ss.str("");
    ss << arr2;
    CHECK_EQUAL("101", ss.str());
}

/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 7.2 Array
 *  Problem Statement:
 *   + Design an array that expands as data is entered and contracts when it is removed. You will need to define a
 *     private data structure to support the array. You may use a heap memory structure using unique_ptr and
 *     make_unique, or you may use one of the STL collection classes such as vector. Support the following access
 *     methods:
 *     |  // Overwrites an existing element, or adds a new element as necessary.
 *     |  // If an element exists at index, the existing element is overwritten.
 *     |  // If an element does not exist at the index, a new element is added. If necessary, the array
 *     |  // must expand to accommodate the new element.
 *     |  void put(int index, int value);
 *     |
 *     |  // returns the element at index.
 *     |  int get(int index) const;
 *     |
 *     |  // removes the element at the specified index. The array may contract.
 *     |  void remove(int index);
 *     Provide two overloads of operator[]:
 *      1. Provide a const member function overload which returns the data at the specified array index.
 *      2. Provide a non-const member function overload which allows the data to be overwritten at the specified
 *         array index.
 *   + Write an overloaded ostream operator to display the contents of the array.
 *   + Write and test the copy constructor for the dynamic array class.
 *   + Write and test the assignment operator for the dynamic array class.
 *
 *   + In this case, why is it better to write our own copy constructor and assignment operator
 *     rather than rely on the compiler generated ones?
 *   To use a unique_ptr and a copy constructor, the solution is more straight forward to define your
 *   own copy constructor. Similarly for assignment operators in a class with unique_ptr, not using the
 *   default constructor is the most obvious solution. By not using the default constructor avoiding
 *   future recompilition is also possible. Among many other considersations is personal
 *   preferences and aggregates.
 *   
 *   + In what situation might it be better to rely on the compiler generated copy constructor and assignment operators?
 *   When a class has no non-trivially default constructors and is trivially copyable (scalar types,
 *   trivial classs types, arrays of trivial types, etc.) derived class constructors can automatically be generated.
 *   This saves time, or makes time to read reddit at work.

 */
#include <iostream>
#include "TestHarness.h"
#include "array.h"

TEST(Array, overload_ostream) {  // Verify the trivial case works and all other cases follow from the definition of std::vector
    std::stringstream ss;
    Array arr;
    ss << arr;
    CHECK_EQUAL("0", ss.str());
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
    arr[1] = 1;  // by (*) this should be {1, 1, 1}
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
}

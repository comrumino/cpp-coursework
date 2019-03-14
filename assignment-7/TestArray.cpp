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
 *   + In this case, why is it better to write our own copy constructor and assignment operator
 *     rather than rely on the compiler generated ones?
 *   + In what situation might it be better to rely on the compiler generated copy constructor and assignment operators?
 */
#include <iostream>
#include "TestHarness.h"
#include "array.h"

TEST(Array, put) {
    Array arr;
    arr.put(1, 1);
    std::cout << arr << std::endl;
}

TEST(Array, subscript_operator_write) {
    Array arr;
    arr.put(0, 1);
}

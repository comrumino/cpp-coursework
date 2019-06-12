/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 1.4
 *  Problem Statement:
 *   + Write a CppUnitLite test that uses new to allocate an array of 10 integers.
 *   + Initialize the array with the values 0 to 9.
 *   + Use CHECK_EQUAL to verify the array has the correct values.
 *   + Use delete to deallocate the array.
 */
#include <iostream>
#include <sstream>
#include "TestHarness.h"

TEST(ArrayInt, array)
{
    const int szArray = 10;
    int* myArray = new int[szArray]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Init w/ values 0 to 9 using new
    // Convert array into stringstream for CHECK_EQUAL
    std::stringstream strArray;
    for (int i = 0; i < szArray; ++i) {
        // use subscript since dynamic array cannot used range based iteration
        strArray << myArray[i] << " ";
    }
    // Verify array values
    CHECK_EQUAL("0 1 2 3 4 5 6 7 8 9 ", strArray.str());
    delete[] myArray;  // deallocate array
}

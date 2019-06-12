/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 1.5
 *  Problem Statement:
 *   + Write a CppUnitLite test that creates a std::vector of int.
 *   + Add 10 integers to the vector with the values 0-9.
 *   + Use CHECK_EQUAL to verify the vector has the correct values.
 */
#include <iostream>
#include <sstream>
#include "TestHarness.h"

TEST(VectorInt, vector)
{
    std::vector<int> myVector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // Init vector w/ values 0 to 9
    // Convector vector to string
    std::stringstream strVector;
    for (auto i : myVector) {
        strVector << i << " ";
    }
    // Verify vector values
    CHECK_EQUAL("0 1 2 3 4 5 6 7 8 9 ", strVector.str());
    // destructor of std::vector will free the memory
}

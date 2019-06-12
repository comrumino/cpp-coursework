#include "TestHarness.h"
#include <iostream>
#include <sstream>

TEST(ArrayInt, array) {
    const int szArray = 10;
    int *myArray = new int[szArray]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Init w/ values 0 to 9 using new
    // Convert array into stringstream for CHECK_EQUAL
    std::stringstream strArray;
    for (int i = 0; i < szArray; ++i) {
        // use subscript since dynamic array cannot used range based iteration
        strArray << myArray[i] << " ";
    }
    // Verify array values
    CHECK_EQUAL("0 1 2 3 4 5 6 7 8 9 ", strArray.str());
    delete[] myArray; // deallocate array
}

#include "TestHarness.h"
#include <iostream>
#include <sstream>

TEST(VectorInt, vector) {
    std::vector<int> myVector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Init vector w/ values 0 to 9
    // Convector vector to string
    std::stringstream strVector;
    for (auto i : myVector) {
        strVector << i << " ";
    }
    // Verify vector values
    CHECK_EQUAL("0 1 2 3 4 5 6 7 8 9 ", strVector.str());
    // destructor of std::vector will free the memory
}

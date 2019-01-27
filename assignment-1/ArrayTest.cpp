#include <TestHarness.h>
#include <iostream>
#include <sstream>

// Rename this file to match the functionality under test. E.g., StringTest.
// Add tests and CHECKs as required
TEST(ArrayTen, array)
{
    int* myArray = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> myVector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto el : myVector) std::cout << el << std::endl;
    std::cout << myArray[3] << std::endl;
    CHECK_EQUAL(1, 1);
}

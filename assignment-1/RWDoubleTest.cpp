#include <TestHarness.h>
#include <iostream>
#include <sstream>
#include "jstronz-1-3.h"

// Rename this file to match the functionality under test. E.g., StringTest.
// Add tests and CHECKs as required
TEST(RWDouble, double)
{
    std::stringstream is("100");
    std::stringstream os;
    rw_double(is, os);
    std::cout << "result" << os.str();
 
    CHECK_EQUAL(1, 1);
}

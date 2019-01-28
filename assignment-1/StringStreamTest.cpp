#include <iostream>
#include <sstream>
#include "TestHarness.h"
#include "jstronz-1-3.h"

TEST(RWDouble, stringstream)
{
    std::stringstream is;
    std::stringstream os;
    const double idouble = 0.00033;
    is << idouble;
    // Read from istream (is) into a double and write double to ostream (os)
    rw_double(is, os);
    double odouble;
    os >> odouble;
    // Verify the double is as expected
    if (!os) {
        CHECK_FAIL("Double conversion failed!");
    } else {
        CHECK_DOUBLES_EQUAL(idouble, odouble, 0.001);
    }
}

TEST(RWFloat, stringstream)
{
    std::stringstream is;
    std::stringstream os;
    const float ifloat = 0.00033;
    is << ifloat;
    // Read from istream (is) into a float and write float to ostream (os)
    rw_float(is, os);
    float ofloat;
    os >> ofloat;
    // Verify the float is as expected
    if (!os) {
        CHECK_FAIL("Conversion failed!");
    } else {
        CHECK_DOUBLES_EQUAL(ifloat, ofloat, 0.001);
    }
}

TEST(RWString, stringstream)
{
    const std::string istring = "This statement is false!";
    std::stringstream os;
    std::stringstream is(istring);
    // Read from istream (is) into a string and write string to ostream (os)
    rw_string(is, os);
    std::string ostring;
    getline(os, ostring);
    // Verify the string is as expected
    if (!os) {
        CHECK_FAIL("Conversion failed!");
    } else {
        CHECK_EQUAL(istring, ostring);
    }
}

TEST(helloRWInt, stringstream)
{
    const std::string istring = "Hello";
    std::stringstream os;
    std::stringstream is(istring);
    // Read from istream (is) into a int and write int to ostream (os)
    rw_int(is, os);
    int oint;
    os >> oint;
    // Verify the conversion was unsuccessful as expected
    if (is.fail()) {
        CHECK(is.fail());
    } else {
        CHECK_FAIL("Conversion succeeded when it should have failed");
    }
}

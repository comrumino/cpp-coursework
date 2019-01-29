/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 1.3
 *  Problem Statement:
 *      Write CppUnitLite tests which verifies std::stringstream. These test will follow the pattern shown in the lesson 1
 *      discussion Use stringstream instead of atoi and sprintf. Write separate tests to:
 *          + read and write a double
 *          + read and write a float
 *          + read and write a string
 *      Initialize a stringstream with the "Hello". Attempt to stream this value into an int variable.
 *      Write a check that verifies this fails. Be sure to use CHECK_DOUBLES_EQUAL for float types and CHECK_EQUAL
 *      for other types.
 */
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
    const std::string istring("This statement is false!");  // direct initialize
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
    const std::string istring("Hello");  // direct initialize
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

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
#include <string>
#include <sstream>
#include "jstronz-1-3.h"

void prompt_user(std::ostream& os, const std::string& user_prompt)
{
   os << user_prompt; 
}

void rw_double(std::istream& is, std::ostream& os)
{
    double doublein;
    is >> doublein;
    os << doublein << std::endl;
}

void rw_float(std::istream& is, std::ostream& os)
{
    float floatin;
    is >> floatin;
    os << floatin << std::endl;
}

void rw_string(std::istream& is, std::ostream& os)
{
    std::string stringin;
    std::getline(is, stringin);
    os << stringin << std::endl;
}

void rw_int(std::istream& is, std::ostream& os)
{
    int iint;
    is >> iint;
    os << iint << std::endl;
}

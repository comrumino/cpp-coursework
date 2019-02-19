/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 4.2
 *  Problem Statement:
 *  Create a C++ header file named write.h which contains function prototypes for three functions named write. 
 *  Write the implementations for each write function in a file named write.cpp. 
 *   + Each write function takes two arguments. 
 *      1. The first argument is always std::ostream& os.
 *      2. The second arguments are an int, a float, and a std::string respectively. 
 *   + Each write function should stream its second argument to the passed in std::ostream.
 *   + Write cppunitlite unit tests that pass a std::stringstream as the first argument to each function and
 *     verify its operation. 
 *   + Write non unit test code that calls each write function and passes std::cout as the first argument
 *     (the cout tests are written outside the unit test framework because verification can't easily be automated).
 *   + Here's the prototype for the first write overload:
 *     | void write(std::ostream& os, int value);
 *     Notice that both std::stringstream and std::cout may be passed as the first argument. Both inherit
 *     from std::ostream and thus may be used where ever a std::ostream& is used.
 */
#include <sstream>
#include <string>
#ifndef WRITE_H
#define WRITE_H
void write(std::ostream& os, const int& intgr);

void write(std::ostream& os, const float& flt);

void write(std::ostream& os, const std::string& strng);
#endif

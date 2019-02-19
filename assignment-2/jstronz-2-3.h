/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 2.3
 *  Problem Statement:
 *   + Write a function cat() that takes two C-style strings (i.e., char*) arguments and returns a C-style
 *     string that is the concatenation of the arguments. Use new to find store for the result.
 *   + Write a second function cat that takes two const std::string& arguments and returns a std::string that is a concatenation of the arguments. 
 *   + The std::string version does not require new.
 *   + Which is the better approach? Explain your rationale for which is the better approach?
 */
#include <string>
#ifndef JSTRONZ_2_3_H
#define JSTRONZ_2_3_H
char* cat(const char* char_arr1, const char* char_arr2);

std::string cat(const std::string& string1, const std::string& string2);
#endif

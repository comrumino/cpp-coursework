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
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "jstronz-2-3.h"

char* cat(const char* char_arr1, const char* char_arr2)
{
    // allocate a result array using the size of inputs
    auto res = new char[strlen(char_arr1) + strlen(char_arr2) + 1];
    auto p = res;
    while (*p++ = *char_arr1++) {
        std::cout << *char_arr1 << std::endl;
        if (*char_arr1 == '\0') {
            std::cout << "has a nulll" << std::endl;
            break;
        }
    }
    while (*p++ = *char_arr2++) {
        std::cout << *char_arr2 << std::endl;
    }
    return res;
}

std::string cat(const std::string& string1, const std::string& string2)
{
    return string1 + string2;
}

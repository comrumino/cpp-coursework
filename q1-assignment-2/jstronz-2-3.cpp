#include <iostream>
#include <string>
#include <cstring>
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

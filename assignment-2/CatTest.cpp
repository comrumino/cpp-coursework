/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 2.3 - unit testing
 */
#include <iostream>
#include <sstream>
#include "TestHarness.h"
#include "jstronz-2-3.h"

TEST(CatTest, cat_array)
{
    char* char_arr1 = new char[3]{'1', '2', '3'};
    char* char_arr2 = new char[3]{'4', '5', '6'};
    std::string exp_arr1_arr2();
    char* arr1_arr2 = cat(char_arr1, char_arr2);
    std::stringstream s_arr1_arr2;
    char* p = arr1_arr2;
    while (*p != NULL) s_arr1_arr2 << *p++;
    CHECK_EQUAL("123456", s_arr1_arr2.str());
}

TEST(CatTest, cat_string)
{
    std::string string1("123");
    std::string string2("456");
    std::string cat_string = cat(string1, string2);
    CHECK_EQUAL("123456", cat_string);
}

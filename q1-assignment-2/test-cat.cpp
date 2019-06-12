#include "TestHarness.h"
#include "jstronz-2-3.h"
#include <iostream>
#include <sstream>
#include <string>

TEST(CatTest, cat_trivial_case_array) {
    // initialize or declare variables
    const char *char_arr1 = new char[1]{'\0'};
    const char *char_arr2 = new char[1]{'\0'};
    // cat the arrays
    char *arr1_arr2 = cat(char_arr1, char_arr2);
    std::stringstream s_arr1_arr2(arr1_arr2);
    // check the result
    CHECK_EQUAL("", s_arr1_arr2.str());
    // dealloc it all away!
    delete[] char_arr1;
    delete[] char_arr2;
    delete[] arr1_arr2;
}

TEST(CatTest, cat_base_case_array) {
    // initialize or declare variables
    const char *char_arr1 = new char[2]{'1', '\0'};
    const char *char_arr2 = "2";
    // cat the arrays
    char *arr1_arr2 = cat(char_arr1, char_arr2);
    std::stringstream s_arr1_arr2(arr1_arr2);
    // check the result
    CHECK_EQUAL("12", s_arr1_arr2.str());
    // dealloc it all away!
    delete[] char_arr1;
    delete[] arr1_arr2;
}

TEST(CatTest, cat_inductive_case_array) {
    // initialize or declare variables
    //  const char* char_arr2 = new char[3]{'3', '4', '5'};  // this will overwrite the null !!!
    //  const std::unique_ptr<char[]> char_arr1(new char[3]{'1', '2', '5'});
    const char *char_arr1 = std::make_unique(new char[3]{'1', '2', '\0'});
    const char *char_arr2 = new char[3]{'3', '4', '\0'};
    // cat the arrays
    char *arr1_arr2 = cat(char_arr1, char_arr2);
    std::stringstream s_arr1_arr2(arr1_arr2);
    // check the result
    CHECK_EQUAL("1234", s_arr1_arr2.str());
    // dealloc it all away!
    delete[] char_arr1;
    delete[] char_arr2;
    delete[] arr1_arr2;
}

TEST(CatTest, cat_string) {
    // initialize variables
    const std::string string1("123");
    const std::string string2("456");
    // cat the strings
    std::string cat_string = cat(string1, string2);
    // check the result
    CHECK_EQUAL("123456", cat_string);
}

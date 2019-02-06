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
#include <vector>
#include <memory>


char* cat(char* char_arr1, char* char_arr2)
{
    int res_sz = 256;
    char* res = new char[res_sz];
    char* tmp_res = nullptr;
    int res_index = 0;
    char* p;
    p = char_arr1;
    bool is_arr1 = true;
    while (*p != NULL || is_arr1) {  // if arr1 and empty the this would never exec
        if (*p == NULL && is_arr1) {
            p = char_arr2;
            is_arr1 = false;
        }
        // std::cout << *p << std::endl;
        res[res_index] = *p;
        if (res_index == res_sz - 1) {
            res_sz *= 2;
            tmp_res = new char[res_sz];
            for (int i = 0; i < res_sz / 2; ++i) {
                tmp_res[i] = res[i];
            }
            delete[] res;
            res = tmp_res;
            tmp_res = nullptr;
        }
        ++p;
        res_index += 1;
    }
    //const void * address = static_cast<const void*>(res);
    //std::cout << address << std::endl;
    //std::cout << &res << std::endl;
    return res;
}

std::string cat(const std::string& string1, const std::string& string2)
{
    return string1 + string2;
}

/*int main()
{
    char* char_arr1 = new char[3]{'1', '2', '3'};
    char* char_arr2 = new char[3]{'4', '5', '6'};

    char* arr1_arr2 = cat(char_arr1, char_arr2);
    //const void * address = static_cast<const void*>(arr1_arr2);
    //std::cout << address << std::endl;
    //std::cout << &arr1_arr2 << std::endl;
    std::string string1("123");
    std::string string2("456");
    std::string cat_string = cat(string1, string2);
    // while (*p != NULL) std::cout << *p++ << std::endl;

    
    return 0;
}*/

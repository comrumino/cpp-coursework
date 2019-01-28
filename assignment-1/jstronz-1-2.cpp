/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 1.2
 *  Problem Statement:
 *      Write a program that prompts the user to enter an int, a double, and a string on the command line. Read the
 *      values into variables of the appropriate data type with std::cin. Write the 3 values to std::cout. This
 *      program does not require the use of CppUnitLite.
 *  
 */
#include <iostream>
#include <string>
#include "jstronz-1-3.h"

int main()
{
    // Prompt user for integer and store (use cout & cin, store in usr_int)
    prompt_user(std::cout, "Enter a int: ");
    rw_int(std::cin, std::cout);
    std::cin.ignore();  // discard to prevent unexpected behavior

    // Prompt user for double and store (use cout & cin, store in usr_double)
    prompt_user(std::cout, "Enter a double: ");
    rw_double(std::cin, std::cout);
    std::cin.ignore();  // discard to prevent unexpected behavior

    // Prompt user for double and store (use cout & cin, store in usr_string)
    prompt_user(std::cout, "Enter a string: ");
    rw_string(std::cin, std::cout);
    return 0;
}

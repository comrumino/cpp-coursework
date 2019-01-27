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
using namespace std;


int main()
{
    int usr_int;
    double usr_double;
    string usr_string;
    //
    cout << "Enter a integer: " << endl;
    cin >> usr_int;
    //
    cout << "Enter a double: " << endl;
    cin >> usr_double;
    //
    cout << "Enter a string: " << endl;
    cin.ignore();
    getline(cin, usr_string);
    //
    cout << usr_int << endl << usr_double << endl << usr_string << endl;
    return 0;
}

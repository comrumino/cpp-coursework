/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 4.4
 *  Problem Statement:
 *   + Define a class named SimpleClass with 
 *      1. a default constructor
 *      2. a copy constructor (i.e., a constructor that takes the single parameter: const SimpleClass& src)
 *      3. destructor 
 *   + Annotate each constructor/destructor so that it writes to cout each time it is invoked.
 *   + Declare four functions, f1, f2, f3, and f4 with the following prototypes:
 *      | void f1(SimpleClass aSimpleClass);  
 *      | void f2(SimpleClass aSimpleClass);
 *      | void f3(SimpleClass& aSimpleClass);
 *      | void f4(SimpleClass* aSimpleClass)
 *   + Declare an instance of SimpleClass in the function main and call f1 with that instance as an argument.
 *   + Declare an instance of SimpleClass in the function f1. Pass that instance by value, to function, f2.
 *   + Declare an instance of the SimpleClass in f2 that uses the copy constructor. Pass that instance by reference to function f3.
 *   + Declare a function f4 that takes a pointer to an instance of SimpleClass.
 *     Call f4 from within f3 using a pointer to the argument passed into f3.
 *  Answer:
 *   How many instances of your class were constructed? How many instances of your class were destructed? Why?
 *   + Objects are copied whenever passed by value and initialized with a value. Since pointers store a memory address
 *   the desctuctor is not called within f4 and passing by reference does not call the destructor either. So,
 *   passing by value 3 times, initialize with a value 1 time, and directly initialized 2 times creates five objects 
 *   which are eventually desconstructed as they leave each scope they were constructed within.
 */
#include <iostream>
#include <algorithm>
#include "jstronz-4-4.h"

void f1(SimpleClass aSimpleClass)
{
    std::cout << "Enter f1" << std::endl;
    SimpleClass f1_sc("sc_f1");
    f2(f1_sc);
    std::cout << "Exit f1" << std::endl;
}

void f2(SimpleClass aSimpleClass)
{
    std::cout << "Enter f2" << std::endl;
    SimpleClass f2_sc = aSimpleClass;
    f3(f2_sc);
    std::cout << "Exit f2" << std::endl;
}

void f3(SimpleClass& aSimpleClass)
{
    std::cout << "Enter f3" << std::endl;
    f4(&aSimpleClass);
    std::cout << "Exit f3" << std::endl;
}

void f4(SimpleClass* aSimpleClass)
{
    std::cout << "Enter-exit f4" << std::endl;
}

int main()
{
    // Five instances are constructed, all of them
    SimpleClass main_sc("sc_main");
    f1(main_sc);
}

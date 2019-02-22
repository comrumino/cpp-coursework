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
 *   How many instances of your class were constructed? How many instances of your class were destructed? Why?
 */
#pragma once
#include <iostream>
#include <string>

class SimpleClass {
    public:
        SimpleClass(std::string sc_id = "default sc")
            :id{sc_id}
        {
            std::cout << "  Constructed: " << id << std::endl;
        }

        SimpleClass(const SimpleClass& src)
            :id{src.id + " copy"}
        {
            std::cout << "  Copied: " << id << std::endl;
        }

        ~SimpleClass()
        {
              std::cout << "  Deconstructed: " << id << std::endl;
        }
    private:
        const std::string id;
};

void f1(SimpleClass aSimpleClass);

void f2(SimpleClass aSimpleClass);

void f3(SimpleClass& aSimpleClass);

void f4(SimpleClass* aSimpleClass);

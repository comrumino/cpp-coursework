/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 7.2 Array
 *  Problem Statement:
 *   + Design an array that expands as data is entered and contracts when it is removed. You will need to define a
 *     private data structure to support the array. You may use a heap memory structure using unique_ptr and
 *     make_unique, or you may use one of the STL collection classes such as vector. Support the following access
 *     methods:
 *     |  // Overwrites an existing element, or adds a new element as necessary.
 *     |  // If an element exists at index, the existing element is overwritten.
 *     |  // If an element does not exist at the index, a new element is added. If necessary, the array
 *     |  // must expand to accommodate the new element.
 *     |  void put(int index, int value);
 *     |
 *     |  // returns the element at index.
 *     |  int get(int index) const;
 *     |
 *     |  // removes the element at the specified index. The array may contract.
 *     |  void remove(int index);
 *     Provide two overloads of operator[]:
 *      1. Provide a const member function overload which returns the data at the specified array index.
 *      2. Provide a non-const member function overload which allows the data to be overwritten at the specified
 *         array index.
 *   + Write an overloaded ostream operator to display the contents of the array.
 *   + Write and test the copy constructor for the dynamic array class.
 *   + Write and test the assignment operator for the dynamic array class.
 *
 *   (Most recent prompt)
 *   + Describe why you chose to either use the default copy constructor and copy assignment or provide your own implementations.
 *   To allow for direct initialization and avoid ambiguity which results in compilation errors, the ctor is implemented.
 *   As for the copy ctor and assignment operator, explicit default was used for brevity.
 *
 *   (Originally copied prompts)
 *   + In this case, why is it better to write our own copy constructor and assignment operator
 *     rather than rely on the compiler generated ones?
 *   To use a unique_ptr and a copy constructor, the solution is more straight forward to define your
 *   own copy constructor. Similarly for assignment operators in a class with unique_ptr, not using the
 *   default constructor is the most obvious solution. By not using the default constructor avoiding
 *   future recompilation is also possible. Among many other considerations is personal
 *   preferences and aggregates.
 *   
 *   + In what situation might it be better to rely on the compiler generated copy constructor and assignment operators?
 *   When a class has no non-trivially default constructors and is trivially copyable (scalar types,
 *   trivial class types, arrays of trivial types, etc.) derived class constructors can automatically be generated.
 *   This saves time, or makes time to read Reddit at work.
 */
#include <iostream>
#include <vector>
#include <type_traits>
#include "array.h"

Array::Array(int i)
    :myArray(i)
{
}

void Array::put(int index, int value) {
    int idx_adjust = 1;  // account for starting at 0
    if (myArray.size() < index + idx_adjust) {
        myArray.resize(index + idx_adjust);
    }
    myArray[index] = value;
}

int Array::get(int index) const {
    return myArray[index];
}

void Array::remove(int index) {
    myArray.erase(myArray.begin() + index);
}

int& Array::operator[](std::vector<int>::size_type index) {  // allow for overwriting values
    return myArray[index];
}

int Array::operator[](std::vector<int>::size_type index) const {
    return myArray[index];
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    for (auto i : arr.myArray ) {
        os << i;
    }
    return os;
}

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
 *   + In this case, why is it better to write our own copy constructor and assignment operator
 *     rather than rely on the compiler generated ones?
 *   + In what situation might it be better to rely on the compiler generated copy constructor and assignment operators?
 */
#include <iostream>
#include "array.h"

Array::Array(int i)
    :myArray(i)
{
}

Array::Array(const Array& arr) 
    :myArray(arr.myArray)
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

Array& Array::operator=(Array arr) {
    if (this == &arr) {
        return *this;
    }
    myArray = arr.myArray;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    for (auto i : arr.myArray ) {
        os << i;
    }
    return os;
}

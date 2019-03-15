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
 *   + In this case, why is it better to write our own copy constructor and assignment operator
 *     rather than rely on the compiler generated ones?
 *   To use a unique_ptr and a copy constructor, the solution is more straight forward to define your
 *   own copy constructor. Similarly for assignment operators in a class with unique_ptr, not using the
 *   default constructor is the most obvious solution. By not using the default constructor avoiding
 *   future recompilition is also possible. Among many other considersations is personal
 *   preferences and aggregates.
 *   
 *   + In what situation might it be better to rely on the compiler generated copy constructor and assignment operators?
 *   When a class has no non-trivially default constructors and is trivially copyable (scalar types,
 *   trivial classs types, arrays of trivial types, etc.) derived class constructors can automatically be generated.
 *   This saves time, or makes time to read reddit at work.
 */
#pragma once
#include <vector>

class Array {
public:
    Array(int i=1);  // constructed as `Array arr;`
    Array(const Array& arr);  // copy constructor

    void put(int index, int value);
    int get(int index) const;
    void remove(int index);
    int& operator[](std::vector<int>::size_type index);
    int operator[](std::vector<int>::size_type index) const;
    Array& operator=(Array arr);

    friend std::ostream& operator<<(std::ostream& os, const Array& arr);

private:
    std::vector<int> myArray;
};

#pragma once
#include <vector>

class Array {
public:
    Array(int i=1);  // Allow direct initialization of array size for intuitive use and avoid ambiguity
    Array(const Array& arr) = default;  // default copy ctor is ok for for vector object with integral elements

    void put(int index, int value);
    int get(int index) const;
    void remove(int index);
    int& operator[](std::vector<int>::size_type index);
    int operator[](std::vector<int>::size_type index) const;
    Array& operator=(Array&) = default;  // default assignment is ok for for vector object with integral elements

    friend std::ostream& operator<<(std::ostream& os, const Array& arr);

private:
    std::vector<int> myArray;
};

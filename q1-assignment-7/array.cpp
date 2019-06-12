#include "array.h"
#include <iostream>
#include <type_traits>
#include <vector>

Array::Array(int i) : myArray(i) {}

void Array::put(int index, int value) {
    int idx_adjust = 1; // account for starting at 0
    if (myArray.size() < index + idx_adjust) {
        myArray.resize(index + idx_adjust);
    }
    myArray[index] = value;
}

int Array::get(int index) const { return myArray[index]; }

void Array::remove(int index) { myArray.erase(myArray.begin() + index); }

int &Array::operator[](std::vector<int>::size_type index) { // allow for overwriting values
    return myArray[index];
}

int Array::operator[](std::vector<int>::size_type index) const { return myArray[index]; }

std::ostream &operator<<(std::ostream &os, const Array &arr) {
    for (auto i : arr.myArray) {
        os << i;
    }
    return os;
}

/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 2.1
 *  Problem Statement:
 *   + Write a function that swaps (exchanges the values of two integers). 
 *   + Use int* as the argument type.
 *   + Write a second swap function using a reference (i.e., int&) as the argument type.
 */
#include <iostream>
#include <string>
#include <vector>

// int* a, a is an object which stores a memory address
// int& b, alias to object provided
//
void int_ptr_swap(int* a, int* b) {
    int tmp_a = *a;  // a is an address. so, dereference and copy the object of type int that it points to
    *a = *b;  // overwrite object a by assigning object b (obtained by dereferencing the pointer)
    *b = tmp_a;  // overwrite b with tmp_a
}

void int_ref_swap(int& a, int& b) {
    int tmp_a = a;  //
    a = b;
    b = tmp_a;
}

int main()
{
    std::vector<int> swapints(4, 0);
    swapints[1] = 1;
    swapints[3] = 1;

    for (auto i : swapints) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
    int_ptr_swap(&swapints[0], &swapints[1]);
    int_ref_swap(swapints[2], swapints[3]);
    for (auto i : swapints) {
        std::cout << i << std::endl;
    }
    return 0;
}

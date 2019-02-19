/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 2.1
 *  Problem Statement:
 *   + Write a function that swaps (exchanges the values of two integers). 
 *   + Use int* as the argument type.
 *   + Write a second swap function using a reference (i.e., int&) as the argument type.
 */
#include "jstronz-2-1.h"

void int_ptr_swap(int* a, int* b)
{
    int tmp_a = *a;  // a is an address. so, dereference and copy the object of type int that it points to
    *a = *b;  // overwrite object a by assigning object b (obtained by dereferencing the pointer)
    *b = tmp_a;  // overwrite b with tmp_a
}

void int_ref_swap(int& a, int& b)
{
    int tmp_a = a;  // a is reference to an object, so copy the object to tmp_a
    a = b;
    b = tmp_a;
}

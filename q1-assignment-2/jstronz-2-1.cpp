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

#include <iostream>
int main()
{
    int* p;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    p = arr;
    while (p != &arr[10])
    {
        std::cout << *p++ << std::endl; 
    }
}

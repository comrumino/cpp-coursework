#include "jstronz-4-4.h"
#include <algorithm>
#include <iostream>

void f1(SimpleClass aSimpleClass) {
    std::cout << "Enter f1" << std::endl;
    SimpleClass f1_sc("sc_f1");
    f2(f1_sc);
    std::cout << "Exit f1" << std::endl;
}

void f2(SimpleClass aSimpleClass) {
    std::cout << "Enter f2" << std::endl;
    SimpleClass f2_sc = aSimpleClass;
    f3(f2_sc);
    std::cout << "Exit f2" << std::endl;
}

void f3(SimpleClass &aSimpleClass) {
    std::cout << "Enter f3" << std::endl;
    f4(&aSimpleClass);
    std::cout << "Exit f3" << std::endl;
}

void f4(SimpleClass *aSimpleClass) { std::cout << "Enter-exit f4" << std::endl; }

int main() {
    // Five instances are constructed, all of them
    SimpleClass main_sc("sc_main");
    f1(main_sc);
}

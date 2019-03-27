#include <functional>
#include <string>
#include <iostream>
#include "license.h"

void jedi() {
    std::cout << "mind fuck!" << std::endl;
}

int main() {
   License lic(jedi); 
   lic.run();
}

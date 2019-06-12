#include "jstronz-1-3.h"
#include <iostream>
#include <string>

int main() {
    // Prompt user for integer and store (use cout & cin, store in usr_int)
    prompt_user(std::cout, "Enter a int: ");
    rw_int(std::cin, std::cout);
    std::cin.ignore(); // discard to prevent unexpected behavior

    // Prompt user for double and store (use cout & cin, store in usr_double)
    prompt_user(std::cout, "Enter a double: ");
    rw_double(std::cin, std::cout);
    std::cin.ignore(); // discard to prevent unexpected behavior

    // Prompt user for double and store (use cout & cin, store in usr_string)
    prompt_user(std::cout, "Enter a string: ");
    rw_string(std::cin, std::cout);

    return 0;
}

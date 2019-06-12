#include "write.h"
#include <iostream>
#include <string>
int main() {
    const std::string newline("\n"); // streams convert to \r\n for windows automatically

    write(std::cout, 1);
    write(std::cout, newline);
    write(std::cout, -1);
    write(std::cout, newline);
    write(std::cout, 1.01f);
    write(std::cout, newline);
    write(std::cout, -1.101f);
    write(std::cout, newline);
    write(std::cout, "this is a false statement");
    write(std::cout, newline);
    write(std::cout, "");
    write(std::cout, newline);
}

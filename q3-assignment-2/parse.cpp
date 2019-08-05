#include "parse.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

void trim(std::string &sourceString, std::string const &trimmables) {
    // drop contiguous edibles from start AND end of source until first not if edibles
    sourceString.erase(0, sourceString.find_first_not_of(trimmables));
    sourceString.erase(sourceString.find_last_not_of(trimmables) + 1);
}
void eat(std::istream &sourceStream, std::string const &edibles) {
    // drop contiguous edibles from start of source until first not if edibles
    int nextchar;
    if (sourceStream) {

        while ((nextchar = sourceStream.peek()) != EOF) {
            if (edibles.find(static_cast<char>(nextchar)) != std::string::npos) {
                sourceStream.get();
            } else {
                break;
            }
        }

    } else {
        std::cout << "An istream with error state was provided to eat. Skipping it..." << std::endl;
    }
}

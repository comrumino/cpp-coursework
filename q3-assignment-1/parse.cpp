#include "parse.h"
#include <string>
#include <iostream>
#include <sstream>
#include <limits>

void trim(std::string& sourceString, std::string const& trimmables) {
    for (auto rit=sourceString.rbegin(); rit != sourceString.rend(); ++rit){
        if (trimmables.find(*rit) != -1)
            sourceString.erase((rit + 1).base());
    }
};
void eat(std::istream& sourceStream, std::string const& edibles) {
    char lead_char = '\0';
    if (sourceStream) {
        while (sourceStream.cur != sourceStream.end) {
            lead_char = sourceStream.peek();
            if (edibles.find(lead_char) != -1) {
                sourceStream.seekg(1, sourceStream.cur);
            } else {
                break;
            }
    
        }
    } else {
        std::cout << "An istream with error state was provided to eat. Skipping it..." << std::endl;
    }
};


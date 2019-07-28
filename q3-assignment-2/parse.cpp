#include "parse.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

void trim(std::string &sourceString, std::string const &trimmables) {
    // drop contiguous edibles from start and end of source until first not if edibles
    std::string::size_type substr_start = sourceString.find_first_not_of(trimmables);
    std::string::size_type substr_end = sourceString.find_last_not_of(trimmables);
    if (substr_start == substr_end) {  // if start and end are same, then set empty
        sourceString = "";
    }
    if (substr_start == npos) {  // never matched so start at 0
        substr_start = 0;
    }
    if (substr_end == npos) {  // never matched so start at end
        substr_end = sourceString.length();
    }
    sourceString = sourceString.substr(substr_start, substr_end - substr_start + 1);  // +1 to account offset

}
void eat(std::istream &sourceStream, std::string const &edibles) {
    // drop contiguous edibles from start of source until first not if edibles
    char lead_char = '\0';
    if (sourceStream) {
        while (sourceStream.cur != sourceStream.end) {
            lead_char = static_cast<char>(sourceStream.peek());
            if (edibles.find(lead_char) != npos) {
                sourceStream.seekg(1, sourceStream.cur);
            } else {
                break;
            }
        }
    } else {
        std::cout << "An istream with error state was provided to eat. Skipping it..." << std::endl;
    }
}

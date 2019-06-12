#include "jstronz-1-3.h"
#include <iostream>
#include <sstream>
#include <string>

void prompt_user(std::ostream &os, const std::string &user_prompt) { os << user_prompt; }

void rw_double(std::istream &is, std::ostream &os) {
    double doublein;
    is >> doublein;
    os << doublein << std::endl;
}

void rw_float(std::istream &is, std::ostream &os) {
    float floatin;
    is >> floatin;
    os << floatin << std::endl;
}

void rw_string(std::istream &is, std::ostream &os) {
    std::string stringin;
    std::getline(is, stringin);
    os << stringin << std::endl;
}

void rw_int(std::istream &is, std::ostream &os) {
    int iint;
    is >> iint;
    os << iint << std::endl;
}

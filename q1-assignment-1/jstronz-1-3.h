#ifndef JSTRONZ_1_3_H
#define JSTRONZ_1_3_H
#include <string>
#include <sstream>

void prompt_user(std::ostream& os, const std::string& user_prompt);

void rw_double(std::istream& is, std::ostream& os);

void rw_float(std::istream& is, std::ostream& os);

void rw_string(std::istream& is, std::ostream& os);

void rw_int(std::istream& is, std::ostream& os);
#endif

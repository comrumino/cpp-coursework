#include <sstream>
#include <string>
#ifndef WRITE_H
#define WRITE_H
void write(std::ostream& os, const int& intgr);

void write(std::ostream& os, const float& flt);

void write(std::ostream& os, const std::string& strng);
#endif

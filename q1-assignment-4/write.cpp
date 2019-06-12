#include <sstream>
#include <string>

void write(std::ostream& os, const int& intgr)
{
    os << intgr;
}

void write(std::ostream& os, const float& flt)
{
    os << flt;
}

void write(std::ostream& os, const std::string& strng)
{
    os << strng;
}

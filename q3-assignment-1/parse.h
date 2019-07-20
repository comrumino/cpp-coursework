#pragma once
#include <string>
#include <istream>

void trim(std::string& sourceString, std::string const& trimmables=" ");
void eat(std::istream& sourceStream, std::string const& edibles=" ");

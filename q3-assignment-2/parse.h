#pragma once
#include "vectorgraphic.h"
#include "tinyxml2.h"
#include <istream>
#include <string>
#include <vector>

static std::string::size_type sz;
static const size_t npos = std::string::npos;

void trim(std::string &sourceString, std::string const &trimmables = " ");
void eat(std::istream &sourceStream, std::string const &edibles = " ");
bool xml_from_file(tinyxml2::XMLDocument& doc, const std::string infile);
bool xml_to_file(tinyxml2::XMLDocument& doc, const std::string outfile, bool compact=false);

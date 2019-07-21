#pragma once
#include "vectorgraphic.h"
#include <istream>
#include <string>
#include <vector>

static std::string::size_type sz;
static const size_t npos = std::string::npos;

void trim(std::string &sourceString, std::string const &trimmables = " ");
void eat(std::istream &sourceStream, std::string const &edibles = " ");

size_t xml_find(std::vector<std::string> &attributes, const std::string &value);
void tag_context(bool &elmnt, bool &exit, const std::string msg, bool expected_elmnt);
bool parse_xml(std::string complete_xml, std::vector<VectorGraphic> &vector_graphics);
void tag_context(bool &elmnt, bool &exit, const std::string msg, bool &expected_elmnt);
bool from_file(const std::string infile, std::vector<VectorGraphic> &vgs);
bool to_file(const std::string outfile, std::vector<VectorGraphic> &vgs);
bool read_file(const std::string infile, std::ostream &fcontent);

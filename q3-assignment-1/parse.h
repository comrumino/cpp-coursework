#pragma once
#include "vectorgraphic.h"
#include <istream>
#include <map>
#include <string>
#include <vector>

void trim(std::string &sourceString, std::string const &trimmables = " ");
void eat(std::istream &sourceStream, std::string const &edibles = " ");

// bool valid_tag_open(std::string::iterator &it);
// bool valid_element_close(std::string::iterator &it, const std::string tag_name);
// bool valid_tag_close(std::string::iterator &it, const std::string tag_name);
// std::map<std::string, int> pickup_attributes(std::string::iterator &it);
void parse_xml(std::string complete_xml, std::vector<VectorGraphic> &vector_graphics);
void tag_context(bool &elmnt, bool &exit, const std::string msg, bool &expected_elmnt);

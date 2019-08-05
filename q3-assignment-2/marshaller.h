#pragma once
#pragma clang diagnostic ignored "-Wc++17-extensions"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>

namespace marshaller {

enum class Markup { xml, human_readable };
static Markup output_markup{Markup::xml};
template <typename ToClass> void set_xml_attr() { // specialize
}
template <class M> std::ostream &markup_stream(std::ostream &os, const M &m) {
    if (marshaller::output_markup == marshaller::Markup::xml) {
        os << m.get_xml();
    } else if (marshaller::output_markup == marshaller::Markup::human_readable) {
        os << m.get_human_readable();
    } else {
        throw std::runtime_error{"The current output markup set is not implemented in operator overload for string."};
    }
    return os;
}
} // namespace marshaller
namespace marshaller::file {

bool read(tinyxml2::XMLDocument &doc, const std::string infile);
bool write(tinyxml2::XMLDocument &doc, const std::string outfile, bool compact = false);
} // namespace marshaller::file

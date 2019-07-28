#pragma once
#pragma clang diagnostic ignored "-Wc++17-extensions"
#include "tinyxml2.h"
#include <string>

namespace marshaller {
    enum class Markup { xml, human_readable };
}
namespace marshaller::file {

bool read(tinyxml2::XMLDocument& doc, const std::string infile);

bool write(tinyxml2::XMLDocument& doc, const std::string outfile, bool compact=false);

}


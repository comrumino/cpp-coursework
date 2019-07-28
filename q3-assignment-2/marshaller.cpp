#pragma clang diagnostic ignored "-Wc++17-extensions"
#include "tinyxml2.h"
#include <string>

namespace marshaller::file {

bool read(tinyxml2::XMLDocument& doc, const std::string infile) {
    doc.LoadFile(infile.c_str());
    tinyxml2::XMLError error_id = doc.ErrorID();
    if (error_id != 0) {
        return error_id;
    } else {
        return 0;
    }
}

bool write(tinyxml2::XMLDocument& doc, const std::string outfile, bool compact) {
    return doc.SaveFile(outfile.c_str(), compact);
}


}


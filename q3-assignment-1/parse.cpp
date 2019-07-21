#include "parse.h"
#include "vectorgraphic.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <string>

const std::string vectorgraphic_regex = "(?:<VectorGraphic\\s+(?:(closed)\\s*)=\\s*\"(?:(false|true)\"|'(false|true)')"
                                        "\\s*(>|/>)|</VectorGraphic>)";
const std::string point_regex = "<Point\\s+(x|y)\\s*?=\\s*?(?:\"([^\"]*)\"|'([^']*)')\\s*"
                                "\\s+(x|y)\\s*?=\\s*?(?:\"([^\"]*)\"|'([^']*)')(>(?:\\s*\\n?)</Point>|(?:\\s*\\n?)/>)";
const std::regex xml("(?:" + vectorgraphic_regex + "|" + point_regex + ")");

void trim(std::string &sourceString, std::string const &trimmables) {
    // drop contiguous edibles from start and end of source until first not if edibles
    std::string::reverse_iterator tmp = sourceString.rend();
    bool read_only = false;
    for (auto rit = sourceString.rbegin(); rit != sourceString.rend(); ++rit) {
        if (trimmables.find(*rit) != npos) {
            if (!read_only) {
                sourceString.erase((rit + 1).base());
            }
        } else {
            tmp = rit + 1;
            read_only = true;
        }
    }
    for (auto rit = tmp; rit != sourceString.rend(); ++rit) {
        sourceString.erase((rit + 1).base());
    }
}
void eat(std::istream &sourceStream, std::string const &edibles) {
    // drop contiguous edibles from start of source until first not if edibles
    char lead_char = '\0';
    if (sourceStream) {
        while (sourceStream.cur != sourceStream.end) {
            lead_char = static_cast<char>(sourceStream.peek());
            if (edibles.find(lead_char) != npos) {
                sourceStream.seekg(1, sourceStream.cur);
            } else {
                break;
            }
        }
    } else {
        std::cout << "An istream with error state was provided to eat. Skipping it..." << std::endl;
    }
}
size_t xml_find(std::vector<std::string> &attributes, const std::string &value) {
    // search vector for attribute and return npos if not found
    size_t offset = 0;
    for (auto el : attributes) {
        if (el == value) {
            break;
        }
        offset += 1;
    }
    if (attributes.size() == offset) {
        return npos;
    } else {
        return offset;
    }
}
void tag_context(bool &elmnt, bool &exit, const std::string msg, bool expected_elmnt) {
    // validate context of parsed tag and report malformed cases
    if (elmnt == expected_elmnt) {
        elmnt = !elmnt;
    } else {
        std::cout << msg << std::endl;
        exit = true;
    }
}

template <class T, class T2> void move_back(T &&t, T2 &&t2) {
    // explicitly show that vector push back is moving the object
    t.push_back(std::forward<T2>(t2));
}

void set_point(Point &point, std::string coord, std::vector<std::string> &attributes, bool &exit) {
    // validate attribute values and set point
    int coord_value = 0;
    std::string tmp_attr_value = "";
    try {
        if (exit)
            return;
        tmp_attr_value = attributes.at(xml_find(attributes, coord) + 1);
        coord_value = std::stoi(tmp_attr_value, &sz);
        if (std::to_string(coord_value) != tmp_attr_value) {
            throw std::invalid_argument("Inaccurate parse by stoi");
        }
        if (coord == "x") {
            point.setX(coord_value);
        } else {
            point.setY(coord_value);
        }
    } catch (...) {
        tag_context(exit, exit, "Malformed xml: invalid Point value for " + coord, true);
    }
}

void set_vectorgraphic(VectorGraphic &vectorgraphic, std::vector<std::string> &attributes, bool &exit) {
    // validate attribute values and set vectorgraphic accordingly
    std::string tmp_attr_value = "";
    try {
        tmp_attr_value = attributes.at(xml_find(attributes, "closed") + 1);
        if (tmp_attr_value == "true") {
            vectorgraphic.closeShape();
        } else {
            vectorgraphic.openShape();
        }
    } catch (...) {
        tag_context(exit, exit, "Malformed xml: Failed to parse VectorGraphic", true);
    }
}

bool parse_xml(std::string complete_xml, std::vector<VectorGraphic> &vector_graphics) {
    // validate and populate vector graphics
    std::smatch match;
    std::string group = "";
    std::vector<std::string> attributes;
    VectorGraphic vg;
    Point pt;
    bool vg_elmnt = false;
    bool pt_elmnt = false;
    bool exit = false;
    for (auto it = std::sregex_iterator(complete_xml.begin(), complete_xml.end(), xml); it != std::sregex_iterator();
         it++) {
        for (auto iit = it->begin(); iit != it->end(); iit++) {
            group = *iit;
            if (group == "")
                continue;
            if (group.find("</VectorGraphic>") != npos && group.find("<VectorGraphic") == -1) {
                tag_context(vg_elmnt, exit, "Malformed xml: VectorGraphic end tag before start tag", true);
                if (!exit) {
                    move_back(vector_graphics, vg);
                }
            } else if (group.find("<VectorGraphic") != npos) {
                tag_context(vg_elmnt, exit, "Malformed xml: nested VectorGraphic is not supported", false);
            } else if (group.find("<Point ") != npos) {
                tag_context(pt_elmnt, exit, "Malformed xml: nested Point is not supported", false);
            } else if (vg_elmnt && pt_elmnt) { // point subelement
                if (attributes.size() <= 5) {  //
                    attributes.push_back(group);
                }
                if (attributes.size() == 5 && xml_find(attributes, "x") != npos && xml_find(attributes, "y") != npos) {
                    attributes.push_back(group);
                    set_point(pt, "x", attributes, exit);
                    set_point(pt, "y", attributes, exit);
                    if (!exit) {
                        vg.addPoint(pt);
                        attributes.clear();
                        pt_elmnt = !pt_elmnt;
                    }
                } else if (attributes.size() >= 5) {
                    tag_context(exit, exit, "Malformed xml: Failed to parse Point", true);
                }
            } else if (group.find("</Point>") != npos) {
                tag_context(pt_elmnt, exit, "Malformed xml: Point end tag before a start tag", true);
            } else if (vg_elmnt) { // VectorGraphic tag
                if (group != ">" && attributes.size() < 1) {
                    attributes.push_back(group);
                } else if (attributes.size() == 1) {
                    attributes.push_back(group);
                    set_vectorgraphic(vg, attributes, exit);
                } else if (group == "/>") {
                    attributes.clear();
                    move_back(vector_graphics, vg);
                    vg_elmnt = !vg_elmnt;
                } else if (group == ">") {
                    attributes.clear();
                }
            } else {
                tag_context(exit, exit, "Malformed xml: non-empty but not in VectorGraphic or Point", true);
            }
            if (exit)
                break;
        }
        if (exit) {
            break;
        }
    }
    return !exit;
}
bool read_file(const std::string infile, std::ostream &fcontent) {
    // reads file into fcontent returns success as bool
    std::ifstream fhandle(infile, std::ios::in);
    std::string line;
    bool success = false;
    fcontent.clear();
    if (!fhandle.good()) {
        std::cout << "File not found: " << infile << std::endl;
    } else if (fhandle.is_open()) {
        while (std::getline(fhandle, line)) {
            trim(line, " \t\n\r");
            fcontent << line;
        }
        fhandle.close();
        success = true;
    }
    return success;
}
bool from_file(const std::string infile, std::vector<VectorGraphic> &vector_graphics) {
    // reads file into fcontent and calls parse_xml on fcontent then returns success as bool
    std::stringstream fcontent;
    if (!read_file(infile, fcontent)) {
        return false;
    } else if (!parse_xml(fcontent.str(), vector_graphics)) {
        return false;
    } else {
        return true;
    }
}
bool to_file(const std::string outfile, std::vector<VectorGraphic> &vector_graphics) {
    // streams vector_graphics into outfile and returns success as bool
    std::ofstream fhandle(outfile);
    bool success = false;
    if (!fhandle.good()) {
        std::cout << "Failed to create output file " << outfile << std::endl;
    } else if (fhandle.is_open()) {
        for (auto vg : vector_graphics) {
            fhandle << vg << std::endl;
        }
        success = true;
    }
    return success;
}

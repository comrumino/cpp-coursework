#include "parse.h"
#include "vectorgraphic.h"
#include <iostream>
#include <limits>
#include <map>
#include <regex>
#include <sstream>
#include <string>

void trim(std::string &sourceString, std::string const &trimmables) {
    for (auto rit = sourceString.rbegin(); rit != sourceString.rend(); ++rit) {
        if (trimmables.find(*rit) != -1)
            sourceString.erase((rit + 1).base());
    }
};

void eat(std::istream &sourceStream, std::string const &edibles) {
    char lead_char = '\0';
    if (sourceStream) {
        while (sourceStream.cur != sourceStream.end) {
            lead_char = sourceStream.peek();
            if (edibles.find(lead_char) != -1) {
                sourceStream.seekg(1, sourceStream.cur);
            } else {
                break;
            }
        }
    } else {
        std::cout << "An istream with error state was provided to eat. Skipping it..." << std::endl;
    }
};
std::string::size_type sz;
/*bool valid_tag_open(std::string::iterator &it) {
    return false;
}
bool valid_tag_close() {
    return false;
}
bool valid_start_tag() {
    // valid_tag_open
    // valid_tag_close
    return false;
}
bool is_empty() {
    return false;
}

bool valid_element_close(std::string::iterator &it, const std::string tag_name) {
    // "/>" or "</tag_name>"
    return false;
}

bool valid_tag_close(std::string::iterator &it, const std::string tag_name) {
    // >
    return false;
}*/

/*std::map<std::string, int> pickup_attributes(std::string::iterator &it){
    std::map<std::string, int> attributes;
    return attributes;
}*/

std::string vectorgraphic_regex =
    "(?:<VectorGraphic\\s+(?:(closed)\\s*)=\\s*\"(?:(false|true)\"|'(false|true)')\\s*(>|/>)|</VectorGraphic>)";
std::string point_regex = "<Point\\s+(x|y)\\s*?=\\s*?(?:\"([0-9]*)\"|'([0-9]*)')\\s*\\s+(x|y)\\s*?=\\s*?(?:\"([0-9]*)"
                          "\"|'([0-9]*)')(>(?:\\s*\\n?)</Point>|(?:\\s*\\n?)/>)";
std::regex xml("(?:" + vectorgraphic_regex + "|" + point_regex + ")");

int xml_find(std::vector<std::string> &attributes, const std::string &value) {
    int offset = 0;
    for (auto el : attributes) {
        if (el == value) {
            break;
        }
        offset += 1;
    }
    if (attributes.size() == offset) {
        return -1;
    } else {
        return offset;
    }
}

void tag_context(bool &elmnt, bool &exit, const std::string msg, bool expected_elmnt) {
    if (elmnt == expected_elmnt) {
        elmnt = !elmnt;
    } else {
        std::cout << msg << std::endl;
        exit = true;
    }
}

void parse_xml(std::string complete_xml, std::vector<VectorGraphic> &vector_graphics) {
    std::smatch match;
    std::string group = "";
    std::vector<std::string> attributes;
    VectorGraphic vg;
    Point pt;
    int attr_value = 0;
    std::string tmp_attr_value = "";
    bool vg_elmnt = false;
    bool pt_elmnt = false;
    bool exit = false;
    for (auto it = std::sregex_iterator(complete_xml.begin(), complete_xml.end(), xml); it != std::sregex_iterator();
         it++) {
        for (auto iit = it->begin(); iit != it->end(); iit++) {
            group = *iit;
            if (group != "") {
                if (group.find("</VectorGraphic>") != -1) {
                    tag_context(vg_elmnt, exit, "Malformed xml: VectorGraphic end tag before start tag", true);
                    if (exit) {
                        break;
                    } else {
                        vector_graphics.push_back(vg);
                        vg = VectorGraphic();
                    }
                } else if (group.find("<VectorGraphic") != -1) {
                    tag_context(vg_elmnt, exit, "Malformed xml: nested VectorGraphic is not supported", false);
                    if (exit)
                        break;
                } else if (group.find("<Point ") != -1) {
                    tag_context(pt_elmnt, exit, "Malformed xml: nested Point is not supported", false);
                    if (exit)
                        break;
                } else if (vg_elmnt && pt_elmnt) { // point subelement
                    if (attributes.size() <= 4 + 1) {
                        attributes.push_back(group);
                    }
                    if (attributes.size() == 5 && xml_find(attributes, "x") != -1 && xml_find(attributes, "y") != -1) {
                        try {
                            attributes.push_back(group);
                            tmp_attr_value = attributes.at(xml_find(attributes, "x") + 1);
                            if (tmp_attr_value.find_first_not_of("0123456789") == std::string::npos) {
                                attr_value = std::stoi(tmp_attr_value, &sz);
                                pt.setX(attr_value);
                            } else {
                                tag_context(exit, exit, "Malformed xml: invalid Point x value", true);
                                if (exit)
                                    break;
                            }
                            tmp_attr_value = attributes.at(xml_find(attributes, "y") + 1);
                            if (tmp_attr_value.find_first_not_of("0123456789") == std::string::npos) {
                                attr_value = std::stoi(tmp_attr_value, &sz);
                                pt.setY(attr_value);
                            } else {
                                tag_context(exit, exit, "Malformed xml: invalid Point y value", true);
                                if (exit)
                                    break;
                            }
                        } catch (...) {
                            tag_context(exit, exit, "Malformed xml: invalid Point values", true);
                            if (exit)
                                break;
                        }
                        vg.addPoint(pt); // move?
                        pt = Point(0, 0);
                        attributes.clear();
                        pt_elmnt = !pt_elmnt;
                    } else if (attributes.size() >= 5) {
                        tag_context(exit, exit, "Malformed xml: Failed to parse Point", true);
                        if (exit)
                            break;
                    }
                } else if (group.find("</Point>") != -1) {
                    tag_context(pt_elmnt, exit, "Malformed xml: Point end tag before a start tag", true);
                    if (exit)
                        break;
                } else if (vg_elmnt) { // VectorGraphic tag
                    if (group != ">" && attributes.size() < 1) {
                        attributes.push_back(group);
                    } else if (attributes.size() == 1) {
                        attributes.push_back(group);
                        try {
                            tmp_attr_value = attributes.at(xml_find(attributes, "closed") + 1);
                            if (tmp_attr_value == "true") {
                                vg.closeShape();
                            } else {
                                vg.openShape();
                            }
                        } catch (...) {
                            tag_context(exit, exit, "Malformed xml: Failed to parse VectorGraphic", true);
                            if (exit)
                                break;
                        }
                    } else if (group == "/>") {
                        attributes.clear();
                        vector_graphics.push_back(vg);
                        vg = VectorGraphic();
                        vg_elmnt = !vg_elmnt;
                    } else if (group == ">") {
                        attributes.clear();
                    }
                } else if (group == ">") {
                    ; // nothing to do
                } else {
                    tag_context(exit, exit, "Malformed xml: non-empty but not in VectorGraphic or Point", true);
                    if (exit)
                        break;
                }
            }
        }
        if (exit) {
            break;
        }
    }
}

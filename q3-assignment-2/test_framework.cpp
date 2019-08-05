#include "TestHarness.h"
#include "parse.h"
#include "point.h"
#include "vectorgraphic.h"
#include "framework.h"
#include "tinyxml2.h"
#include "test_xml_case.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

/*
class Attribute {
    public:
        Attribute(const std::string &attr_name, const std::string &attr_value) : name{attr_name}, value{attr_value} {}
        const std::string &getName() const { return name; }
        const std::string &getStrValue() const { return value; }
        const int getIntValue() const;
    private:
        std::string name;
        std::string value;
};

class Element {
    public:
        Element(const std::string &elmnt_name) : name{elmnt_name} {}
        const std::string &getName() const { return name; }
        const std::vector<Attribute> &getAllAttributes() const { return attributes; }
        void addAttribute(const Attribute &attr) { attributes.push_back(attr); }
        const std::vector<Element> &getChildren() const { return children; }
        void addChild(const Element &elmnt) { children.push_back(elmnt); }
    private:
        std::string name;
        std::vector<Attribute> attributes;
        std::vector<Element> children;
};*/

TEST(framework_Attribute, getStr_getInt) {
    framework::Attribute attr_x("x", "0");
    framework::Attribute attr_y("y", "1");
    CHECK_EQUAL("0", attr_x.getStrValue());
    CHECK_EQUAL(1, attr_y.getIntValue());
    framework::Attribute attr_z("z", "z");
    bool caught = false;
    try {
        CHECK_EQUAL("z", attr_z.getStrValue());
        attr_z.getIntValue();
    } catch (...) {
        caught = true;
    }
    CHECK_EQUAL(true, caught);
}
TEST(framework_Attribute, getBool) {
    framework::Attribute attr_closed("closed", "false");
    framework::Attribute attr_closed2("closed", "0");
    framework::Attribute attr_open("closed", "true");
    framework::Attribute attr_open2("closed", "1");
    framework::Attribute attr_bad("closed", "bad");
    CHECK_EQUAL(false, attr_closed.getBoolValue());
    CHECK_EQUAL(false, attr_closed2.getBoolValue());
    CHECK_EQUAL(true, attr_open.getBoolValue());
    CHECK_EQUAL(true, attr_open2.getBoolValue());
    bool caught = false;
    try {
        attr_bad.getBoolValue();
    } catch (...) {
        caught = true;
    }
    CHECK_EQUAL(true, caught);
}
TEST(framework_Element, getName) {
    framework::Element framework_elmnt(geom::Point::name);
    CHECK_EQUAL(geom::Point::name, framework_elmnt.getName());
}
TEST(framework_Element, addAttribute_getAttributeCount_getAllAttributes_getAttribute) {
    using namespace framework;
    using AttrsColl = std::vector<std::vector<Attribute>>;
    Element framework_elmnt(geom::Point::name);
    AttrsColl attrs_coll = {{Attribute("x", "0"), Attribute("y", "1")}, 
                            {Attribute("x", "1"), Attribute("y", "0")}};
    std::vector<Element> elmnts;
    // addAttribute && getAttributeCount
    for (auto attrs : attrs_coll) {
        framework_elmnt = Element(geom::Point::name);
        CHECK_EQUAL(0, framework_elmnt.getAttributeCount());
        for (auto attr : attrs) {
            framework_elmnt.addAttribute(attr);
        }
        CHECK_EQUAL(attrs.size(), framework_elmnt.getAttributeCount());
        elmnts.push_back(framework_elmnt);
    }
    // getAllAttributes
    for (int i = 0; i < elmnts.size(); i++) {  // element iteration
        auto elmnt = elmnts.at(i);
        auto elmnt_attrs = elmnt.getAllAttributes();
        auto expected_attr_vec = attrs_coll.at(i);
        for (int j = 0; j < expected_attr_vec.size(); j++) {  // attrs of element iteration
            auto expected_attr = expected_attr_vec.at(j);
            CHECK_EQUAL(expected_attr.getName(), elmnt_attrs.at(j).getName());
            CHECK_EQUAL(attrs_coll.at(i).at(j).getIntValue(), elmnt_attrs.at(j).getIntValue());
        }
    }
    // getAttribute
    for (int i = 0; i < elmnts.size(); i++) {  // element iteration
        auto elmnt = elmnts.at(i);
        auto expected_attr_vec = attrs_coll.at(i);
        for (int j = 0; j < expected_attr_vec.size(); j++) {  // attrs of element iteration
            auto expected_attr = expected_attr_vec.at(j);
            auto elmnt_attr = elmnt.getAttribute(expected_attr.getName());
            CHECK_EQUAL(expected_attr.getName(), elmnt_attr.getName());
            CHECK_EQUAL(expected_attr.getIntValue(), elmnt_attr.getIntValue());
        }
    }
}
TEST(framework_Element, addChild_getChildCount_getAllChildren_getChild) {
    using namespace framework;
    using AttrsColl = std::vector<std::vector<Attribute>>;
    Element pt_elmnt(geom::Point::name);
    AttrsColl attrs_coll = {{Attribute("x", "0"), Attribute("y", "4")}, 
                            {Attribute("x", "4"), Attribute("y", "0")},
                            {Attribute("x", "2"), Attribute("y", "2")}};
    std::vector<Element> expected_children;
    Element vg_elmnt(geom::VectorGraphic::name);
    vg_elmnt.addAttribute(Attribute("closed", "false"));
    // addChild && getChildCount
    CHECK_EQUAL(0, vg_elmnt.getChildCount());
    for (auto attrs : attrs_coll) {
        pt_elmnt = Element(geom::Point::name);
        for (auto attr : attrs) {
            pt_elmnt.addAttribute(attr);
        }
        expected_children.push_back(pt_elmnt);
        vg_elmnt.addChild(pt_elmnt);
    }
    CHECK_EQUAL(expected_children.size(), vg_elmnt.getChildCount());
    // getAllChildren
    auto actual_children = vg_elmnt.getAllChildren();
    for (int i = 0; i < expected_children.size(); i++) {  // element iteration
        auto expected_child = expected_children.at(i);
        auto actual_child = actual_children.at(i);
        CHECK_EQUAL(expected_child.getName(), actual_child.getName());
        CHECK_EQUAL(expected_child.getAttribute("x").getName(), actual_child.getAttribute("x").getName());
        CHECK_EQUAL(expected_child.getAttribute("x").getIntValue(), actual_child.getAttribute("x").getIntValue());
    }
    // getChild
    for (int i = 0; i < expected_children.size(); i++) {  // element iteration
        auto expected_child = expected_children.at(i);
        auto actual_child = vg_elmnt.getChild(i);
        CHECK_EQUAL(expected_child.getName(), actual_child.getName());
        CHECK_EQUAL(expected_child.getAttribute("x").getName(), actual_child.getAttribute("x").getName());
        CHECK_EQUAL(expected_child.getAttribute("x").getIntValue(), actual_child.getAttribute("x").getIntValue());
    }
}
TEST(framework_io, elementFromXML_unknown) {
    tinyxml2::XMLDocument doc;
    std::string doc_input(xml_case::unknown + xml_case::play);
    doc.Parse(doc_input.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.FirstChild());
    CHECK_EQUAL("unknown", framework_elmnt.getName());
    CHECK_EQUAL(xml_case::unknown, framework_elmnt.getAttribute("value").getStrValue());
    CHECK_EQUAL(true, framework_elmnt.isUnknown());
    CHECK_EQUAL(false, framework_elmnt.isElement());
}
TEST(framework_io, elementFromXML_declaration) {
    tinyxml2::XMLDocument doc;
    std::string doc_input(xml_case::declaration + xml_case::play);
    doc.Parse(doc_input.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.FirstChild());
    CHECK_EQUAL("declaration", framework_elmnt.getName());
    CHECK_EQUAL(xml_case::declaration, framework_elmnt.getAttribute("value").getStrValue());
    CHECK_EQUAL(true, framework_elmnt.isDeclaration());
    CHECK_EQUAL(false, framework_elmnt.isElement());
}
TEST(framework_io, elementFromXML_text) {
    tinyxml2::XMLDocument doc;
    std::string doc_input(xml_case::text + xml_case::play);
    doc.Parse(doc_input.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.FirstChild());
    CHECK_EQUAL("text", framework_elmnt.getName());
    CHECK_EQUAL(true, framework_elmnt.isText());
    CHECK_EQUAL(false, framework_elmnt.isElement());
}
TEST(framework_io, elementFromXML_comment) {
    tinyxml2::XMLDocument doc;
    std::string doc_input(xml_case::comment + xml_case::play);
    doc.Parse(doc_input.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.FirstChild());
    CHECK_EQUAL("comment", framework_elmnt.getName());
    CHECK_EQUAL(xml_case::comment, framework_elmnt.getAttribute("value").getStrValue());
    CHECK_EQUAL(true, framework_elmnt.isComment());
    CHECK_EQUAL(false, framework_elmnt.isElement());
}
TEST(framework_io, elementFromXML_document) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::play.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.ToDocument());
    CHECK_EQUAL("document", framework_elmnt.getName());
    CHECK_EQUAL(0, framework_elmnt.getAttributeCount());
    CHECK_EQUAL(1, framework_elmnt.getChildCount());
    auto doc_child = framework_elmnt.getChild(0);
    CHECK_EQUAL("Play", doc_child.getName());
    CHECK_EQUAL(0, doc_child.getAttributeCount());
    CHECK_EQUAL(0, doc_child.getChildCount());
    CHECK_EQUAL(true, framework_elmnt.isDocument());
    CHECK_EQUAL(false, framework_elmnt.isElement());
}
TEST(framework_io, elementFromXML_point_good) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::point_good.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.RootElement());
    CHECK_EQUAL("Point", framework_elmnt.getName());
    CHECK_EQUAL(true, framework_elmnt.isElement());
    for (auto attr : framework_elmnt.getAllAttributes()) {
        if (attr.getName() == "x") {
            CHECK_EQUAL(1, attr.getIntValue()); 
        } else if (attr.getName() == "y") {
            CHECK_EQUAL(2, attr.getIntValue());
        } else {
            CHECK_EQUAL(false, true);  // unexpected attribute name
        }
    }
}
TEST(framework_io, elementFromXML_count_1_uncommented) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::good_count_1_uncommented.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.ToDocument());
    CHECK_EQUAL("document", framework_elmnt.getName());
    // Scene
    framework_elmnt = framework_elmnt.getChild(0);
    CHECK_EQUAL("Scene", framework_elmnt.getName());
    CHECK_EQUAL(800, framework_elmnt.getAttribute("width").getIntValue());
    CHECK_EQUAL(600, framework_elmnt.getAttribute("height").getIntValue());
    CHECK_EQUAL(2, framework_elmnt.getAttributeCount());
    CHECK_EQUAL(1, framework_elmnt.getChildCount());
    // Layer
    framework_elmnt = framework_elmnt.getChild(0);
    CHECK_EQUAL("Layer", framework_elmnt.getName());
    CHECK_EQUAL("sky", framework_elmnt.getAttribute("alias").getStrValue());
    CHECK_EQUAL(1, framework_elmnt.getAttributeCount());
    CHECK_EQUAL(1, framework_elmnt.getChildCount());
    // PlacedGraphic
    framework_elmnt = framework_elmnt.getChild(0);
    CHECK_EQUAL("PlacedGraphic", framework_elmnt.getName());
    CHECK_EQUAL(0, framework_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(0, framework_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, framework_elmnt.getAttributeCount());
    CHECK_EQUAL(1, framework_elmnt.getChildCount());
    // VectorGraphic
    framework_elmnt = framework_elmnt.getChild(0);
    CHECK_EQUAL("VectorGraphic", framework_elmnt.getName());
    CHECK_EQUAL(true, framework_elmnt.getAttribute("closed").getBoolValue());
    CHECK_EQUAL(1, framework_elmnt.getAttributeCount());
    CHECK_EQUAL(3, framework_elmnt.getChildCount());
    // Point 1 of 3
    auto pt_elmnt = framework_elmnt.getChild(0);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(1, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 2 of 3
    pt_elmnt = framework_elmnt.getChild(1);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(3, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(4, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 3 of 3
    pt_elmnt = framework_elmnt.getChild(2);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(5, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(6, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
}
TEST(framework_io, elementFromXML_count_2_uncommented) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::good_count_2_uncommented.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.ToDocument());
    // Scene
    framework_elmnt = framework_elmnt.getChild(0);
    // Layer (L1)
    auto layer_elmnt = framework_elmnt.getChild(0);
    CHECK_EQUAL("Layer", layer_elmnt.getName());
    CHECK_EQUAL("sky", layer_elmnt.getAttribute("alias").getStrValue());
    CHECK_EQUAL(2, layer_elmnt.getChildCount());
    // PlacedGraphic (L1.1)
    auto pg_elmnt = layer_elmnt.getChild(0);
    CHECK_EQUAL("PlacedGraphic", pg_elmnt.getName());
    CHECK_EQUAL(0, pg_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(0, pg_elmnt.getAttribute("y").getIntValue());
    // VectorGraphic
    auto vg_elmnt = pg_elmnt.getChild(0);
    CHECK_EQUAL("VectorGraphic", vg_elmnt.getName());
    CHECK_EQUAL(true, vg_elmnt.getAttribute("closed").getBoolValue());
    // Point 1 of 3
    auto pt_elmnt = vg_elmnt.getChild(0);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(1, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 2 of 3
    pt_elmnt = vg_elmnt.getChild(1);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(3, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(4, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 3 of 3
    pt_elmnt = vg_elmnt.getChild(2);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(5, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(6, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // PlacedGraphic (L1.2)
    pg_elmnt = layer_elmnt.getChild(1);
    CHECK_EQUAL("PlacedGraphic", pg_elmnt.getName());
    CHECK_EQUAL(700, pg_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(0, pg_elmnt.getAttribute("y").getIntValue());
    // VectorGraphic
    vg_elmnt = pg_elmnt.getChild(0);
    CHECK_EQUAL("VectorGraphic", vg_elmnt.getName());
    CHECK_EQUAL(false, vg_elmnt.getAttribute("closed").getBoolValue());
    // Point 1 of 3
    pt_elmnt = vg_elmnt.getChild(0);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(7, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(8, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 2 of 3
    pt_elmnt = vg_elmnt.getChild(1);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(9, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(10, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 3 of 3
    pt_elmnt = vg_elmnt.getChild(2);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(11, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(12, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Layer (L2)
    layer_elmnt = framework_elmnt.getChild(1);
    CHECK_EQUAL("Layer", layer_elmnt.getName());
    CHECK_EQUAL("mountains", layer_elmnt.getAttribute("alias").getStrValue());
    CHECK_EQUAL(1, layer_elmnt.getChildCount());
    // PlacedGraphic (L2.1)
    pg_elmnt = layer_elmnt.getChild(0);
    CHECK_EQUAL("PlacedGraphic", pg_elmnt.getName());
    CHECK_EQUAL(250, pg_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(250, pg_elmnt.getAttribute("y").getIntValue());
    // VectorGraphic
    vg_elmnt = pg_elmnt.getChild(0);
    CHECK_EQUAL("VectorGraphic", vg_elmnt.getName());
    CHECK_EQUAL(false, vg_elmnt.getAttribute("closed").getBoolValue());
    // Point 1 of 3
    pt_elmnt = vg_elmnt.getChild(0);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(13, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(14, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 2 of 3
    pt_elmnt = vg_elmnt.getChild(1);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(15, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(16, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
    // Point 3 of 3
    pt_elmnt = vg_elmnt.getChild(2);
    CHECK_EQUAL("Point", pt_elmnt.getName());
    CHECK_EQUAL(17, pt_elmnt.getAttribute("x").getIntValue());
    CHECK_EQUAL(18, pt_elmnt.getAttribute("y").getIntValue());
    CHECK_EQUAL(2, pt_elmnt.getAttributeCount());
    CHECK_EQUAL(0, pt_elmnt.getChildCount());
}
TEST(framework_io, io_Point_VectorGraphic_PlacedGraphic_Layer_Scene) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::good_count_2_uncommented.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.ToDocument());
    auto scene_elmnt = framework_elmnt.getChild(0);
    auto layer_elmnt = scene_elmnt.getChild(0);
    auto pg_elmnt = layer_elmnt.getChild(0);
    auto vg_elmnt = pg_elmnt.getChild(0);
    auto pt_elmnt = vg_elmnt.getChild(0);
    // readPoint
    auto pt = framework::io::readPoint(pt_elmnt);
    CHECK_EQUAL(pt_elmnt.getAttribute("x").getIntValue(), pt.getX());
    // readVectorGraphic
    auto vg = framework::io::readVectorGraphic(vg_elmnt);
    CHECK_EQUAL(true, vg->isClosed());
    CHECK_EQUAL(4, vg->getWidth());
    CHECK_EQUAL(4, vg->getHeight());
    CHECK_EQUAL(3, vg->getPointCount());
    // readPlacedGraphic
    auto pg = framework::io::readPlacedGraphic(pg_elmnt);
    auto pg_placement = pg.getPlacementPoint();
    CHECK_EQUAL(0, pg_placement.getX());
    CHECK_EQUAL(0, pg_placement.getY());
    CHECK_EQUAL(vg->getWidth(), pg.getGraphic()->getWidth());
    CHECK_EQUAL(vg->getHeight(), pg.getGraphic()->getHeight());
    CHECK_EQUAL(vg->isClosed(), pg.getGraphic()->isClosed());
    // readLayer
    auto layer = framework::io::readLayer(layer_elmnt);
    CHECK_EQUAL("sky", layer.getAlias());
    CHECK_EQUAL(2, layer.getPlacedGraphicCount());
    // readScene
    auto scene = framework::io::readScene(scene_elmnt);
    CHECK_EQUAL(800, scene.getWidth());
    CHECK_EQUAL(2, scene.getLayerCount());
    // writePoint
    auto written_pt_elmnt = framework::io::writePoint(pt);
    auto pt_x = written_pt_elmnt.getAttribute("x").getIntValue();
    CHECK_EQUAL(pt_elmnt.getAttribute("x").getIntValue(), pt_x);
    CHECK_EQUAL(0, written_pt_elmnt.getChildCount());
    // writeVectorGraphic
    auto written_vg_elmnt = framework::io::writeVectorGraphic(vg);
    auto vg_closed = written_vg_elmnt.getAttribute("closed").getBoolValue();
    CHECK_EQUAL(vg_elmnt.getAttribute("closed").getBoolValue(), vg_closed);
    CHECK_EQUAL(pt_x, written_vg_elmnt.getChild(0).getAttribute("x").getIntValue());
    CHECK_EQUAL(3, written_vg_elmnt.getChildCount());
    // writePlacedGraphic
    auto written_pg_elmnt = framework::io::writePlacedGraphic(pg);
    auto pg_x = written_pg_elmnt.getAttribute("x").getIntValue();
    CHECK_EQUAL(pg_elmnt.getAttribute("x").getIntValue(), pg_x);
    CHECK_EQUAL(vg_closed, written_pg_elmnt.getChild(0).getAttribute("closed").getBoolValue());
    CHECK_EQUAL(pg_elmnt.getChildCount(), written_pg_elmnt.getChildCount());
    // writeLayer
    auto written_layer_elmnt = framework::io::writeLayer(layer);
    auto layer_alias = written_layer_elmnt.getAttribute("alias").getStrValue();
    CHECK_EQUAL(layer_elmnt.getAttribute("alias").getStrValue(), layer_alias);
    CHECK_EQUAL(pg_x, written_layer_elmnt.getChild(0).getAttribute("x").getIntValue());
    CHECK_EQUAL(layer_elmnt.getChildCount(), written_layer_elmnt.getChildCount());
    // writeScene
    auto written_scene_elmnt = framework::io::writeScene(scene);
    CHECK_EQUAL(scene_elmnt.getAttribute("height").getIntValue(), written_scene_elmnt.getAttribute("height").getIntValue());
    CHECK_EQUAL(scene_elmnt.getChildCount(), written_scene_elmnt.getChildCount());
}
TEST(framework_io, elementFromXML_bad) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::point_bad.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.RootElement());
    bool thrown = false;
    try {
        for (auto attr : framework_elmnt.getAllAttributes()) {
            attr.getIntValue();
        }
    } catch (...) {
        thrown = true;
    }
    CHECK_EQUAL(true, thrown);
}
TEST(framework_io, elementToXML_good) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml_case::point_good.c_str()); 
    auto framework_elmnt = framework::io::elementFromXML(doc.RootElement());
    doc.Clear();
    auto xml_elmnt = framework::io::elementToXML(framework_elmnt, doc);
    tinyxml2::XMLPrinter printer;
    xml_elmnt->Accept( &printer );
    std::string xml_str(printer.CStr());
    trim(xml_str, "\n\t\r");
    CHECK_EQUAL(xml_case::point_good, xml_str);
}

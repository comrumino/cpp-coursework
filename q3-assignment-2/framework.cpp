#include "framework.h"

#include "point.h"
#include "vectorgraphic.h"
#include <algorithm>
#include <cctype>
#include <memory>
#include <string>
#include <vector>

namespace framework {
// class PlacedGraphic
void PlacedGraphic::setPlacementPoint(const geom::Point &placement) { placementPoint = placement; }
const geom::Point &PlacedGraphic::getPlacementPoint() const { return placementPoint; }
void PlacedGraphic::setGraphic(const HVectorGraphic &param_graphic) { graphic = param_graphic; }
HVectorGraphic const &PlacedGraphic::getGraphic() const { return graphic; }
void Layer::addGraphic(PlacedGraphic &pg) { graphics.push_back(std::move(pg)); }
bool operator==(const PlacedGraphic &lhs, const PlacedGraphic &rhs) {
    return rhs.getPlacementPoint() == lhs.getPlacementPoint() && rhs.getGraphic() == lhs.getGraphic();
}
bool operator!=(const PlacedGraphic &lhs, const PlacedGraphic &rhs) { return !(lhs == rhs); }

// class Layer
const std::string &Layer::getAlias() const { return alias; }
void Layer::setAlias(const std::string &new_alias) { alias = new_alias; }
bool Layer::operator==(const Layer &rhs) const { // scope to class and used stdlib equality check
    return rhs.getAlias() == getAlias() && rhs.graphics == graphics;
}
bool operator!=(const Layer &lhs, const Layer &rhs) { return !(lhs == rhs); }

// class Scene
void Scene::addLayer(Layer &layer) { layers.push_back(std::move(layer)); }
void Scene::setWidth(const int newWidth) { width = newWidth; }
const int Scene::getWidth() const { return width; }
void Scene::setHeight(const int newHeight) { height = newHeight; }
const int Scene::getHeight() const { return height; }
bool Scene::operator==(const Scene &rhs) const { // scope to class and used stdlib equality check
    return rhs.getWidth() == getWidth() && rhs.layers == layers;
}
bool operator!=(const Scene &lhs, const Scene &rhs) { return !(lhs == rhs); }

const int Attribute::getIntValue() const {
    int result = std::stoi(value);
    if (std::to_string(result) != value) {
        throw std::invalid_argument{"Inaccurate parse by stoi"};
    }
    return result;
};
const bool Attribute::getBoolValue() const {
    auto lower_value = value;
    std::transform(lower_value.begin(), lower_value.end(), lower_value.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if (lower_value == "false" || lower_value == "0") {
        return false;
    } else if (lower_value == "true" || lower_value == "1") {
        return true;
    } else {
        throw std::invalid_argument{"Value is no an acceptable value (0, 1, false, true)"};
    }
};

const Attribute &Element::getAttribute(const std::string name) const {
    auto it = std::find_if(attributes.begin(), attributes.end(),
                           [&](const Attribute &attr) { return attr.getName() == name; });
    if (it != attributes.end()) {
        return *it;
    } else {
        throw std::invalid_argument{"No attribute with the name " + name + " was found"};
    }
}

} // namespace framework

namespace framework::io {

framework::Element elementFromXML(const tinyxml2::XMLNode *xml_node) {
    framework::Element framework_elmnt("unknown", framework::ElementType::unknown);
    tinyxml2::XMLPrinter printer;
    // throw for invalid values, if not Document or Element create framework::Element and return
    // otherwise, convert both Document and Element to Element and create framework::Element
    if (xml_node == nullptr) {
        throw std::invalid_argument{"For elementFromXML xml_node must not be a nullptr"};
    } else if (xml_node->ToText() != nullptr) {
        framework_elmnt = framework::Element("text", framework::ElementType::text);
        xml_node->Accept(&printer);
        framework_elmnt.addAttribute(Attribute("value", printer.CStr()));
        return framework_elmnt;
    } else if (xml_node->ToUnknown() != nullptr) {
        framework_elmnt = framework::Element("unknown", framework::ElementType::unknown);
        xml_node->Accept(&printer);
        framework_elmnt.addAttribute(Attribute("value", printer.CStr()));
        return framework_elmnt;
    } else if (xml_node->ToDeclaration() != nullptr) {
        framework_elmnt = framework::Element("declaration", framework::ElementType::declaration);
        xml_node->Accept(&printer);
        framework_elmnt.addAttribute(Attribute("value", printer.CStr()));
        return framework_elmnt;
    } else if (xml_node->ToComment() != nullptr) {
        framework_elmnt = framework::Element("comment", framework::ElementType::comment);
        xml_node->Accept(&printer);
        framework_elmnt.addAttribute(Attribute("value", printer.CStr()));
        return framework_elmnt;
    } else if (xml_node->ToDocument() != nullptr) {
        auto xml_elmnt = xml_node->ToDocument()->FirstChild();
        framework_elmnt = framework::Element("document", framework::ElementType::document);
        framework_elmnt.addChild(elementFromXML(xml_elmnt));
        return framework_elmnt;
        // return elementFromXML(xml_elmnt);
    } else if (xml_node->ToElement() != nullptr) {
        auto xml_elmnt = xml_node->ToElement();
        framework_elmnt = framework::Element(xml_elmnt->Name());
        // add attributes
        for (const tinyxml2::XMLAttribute *attr = xml_elmnt->FirstAttribute(); attr; attr = attr->Next()) {
            auto framework_attr = Attribute(attr->Name(), attr->Value());
            framework_elmnt.addAttribute(framework_attr);
        }
        // add children
        if (!xml_elmnt->NoChildren()) {
            for (const tinyxml2::XMLNode *c = xml_elmnt->FirstChild(); c; c = c->NextSibling()) {
                auto framework_child = elementFromXML(c);
                framework_elmnt.addChild(framework_child);
            }
        }
        return framework_elmnt;
    } else {
        throw std::invalid_argument{"Failed to determine element type within elementFromXML"};
    }
}

tinyxml2::XMLNode *elementToXML(const framework::Element &framework_elmnt, tinyxml2::XMLDocument &doc) {
    if (framework_elmnt.isElement()) {
        auto isValidTag = false;
        auto name = framework_elmnt.getName();
        auto xml_elmnt = doc.NewElement(name.c_str());
        isValidTag |= name == framework::Scene::name;
        isValidTag |= name == framework::Layer::name;
        isValidTag |= name == framework::PlacedGraphic::name;
        isValidTag |= name == geom::VectorGraphic::name;
        isValidTag |= name == geom::Point::name;
        if (isValidTag) {
            for (auto attr : framework_elmnt.getAllAttributes()) {
                xml_elmnt->SetAttribute(attr.getName().c_str(), attr.getStrValue().c_str());
            }
            for (auto child : framework_elmnt.getAllChildren()) {
                auto xml_child = elementToXML(child, doc);
                xml_elmnt->InsertEndChild(xml_child);
            }
            return xml_elmnt;
        } else {
            throw std::invalid_argument{"Invalid elementToXML elemnt tag " + name};
        }
    } else if (framework_elmnt.isDocument()) {
        for (auto child : framework_elmnt.getAllChildren()) {
            if (!framework::io::isSaneElement(child, "Scene"))
                continue;
            auto scene = framework::io::readScene(child);
            auto scene_elmnt = framework::io::writeScene(scene);
            auto xml_scene = framework::io::elementToXML(scene_elmnt, doc);
            doc.InsertEndChild(xml_scene);
        }
        return nullptr;
    } else if (framework_elmnt.isComment()) {
        auto comment = framework_elmnt.getAttribute("value").getStrValue();
        std::cout << "converting framework element comment to xml comment (\"" << comment << "\")" << std::endl;
        return doc.NewComment(comment.c_str());
    } else if (framework_elmnt.isDeclaration()) {
        return doc.NewComment(framework_elmnt.getAttribute("value").getStrValue().c_str());
    } else if (framework_elmnt.isUnknown()) {
        return doc.NewUnknown(framework_elmnt.getAttribute("value").getStrValue().c_str());
    } else if (framework_elmnt.isText()) {
        return doc.NewText(framework_elmnt.getAttribute("value").getStrValue().c_str());
    } else {
        throw std::invalid_argument{"Unexpected framework element type!"};
    }
}

bool isSaneElement(const framework::Element &elmnt, const std::string &name) {
    if (!elmnt.isElement()) {
        if (elmnt.isComment()) {
            std::cout << "comment: " << elmnt.getAttribute("value").getStrValue() << std::endl;
        } else {
            std::cout << "Expected node to be of type Element but found " << elmnt.getName() << std::endl;
        }
        return false;
    } else if (elmnt.getName() != name) {
        std::cout << "Expected element to be " << name << " but it was " << elmnt.getName() << std::endl;
        return false;
    } else {
        return true;
    }
}
// framework::io read
geom::Point readPoint(const framework::Element &pointElmnt) {
    if (pointElmnt.getName() != geom::Point::name)
        throw std::runtime_error{"Expected tag " + geom::Point::name};
    if (pointElmnt.getAttributeCount() != 2)
        throw std::runtime_error{"Malformed element attributes for " + geom::Point::name};
    if (pointElmnt.getChildCount() != 0)
        throw std::runtime_error{"Malformed element children for " + geom::Point::name};
    auto x = pointElmnt.getAttribute("x").getIntValue();
    auto y = pointElmnt.getAttribute("y").getIntValue();
    return geom::Point(x, y);
}
HVectorGraphic readVectorGraphic(const framework::Element &vectorGraphicElmnt) {
    if (vectorGraphicElmnt.getName() != geom::VectorGraphic::name)
        throw std::runtime_error{"Expected tag " + geom::VectorGraphic::name};
    if (vectorGraphicElmnt.getAttributeCount() != 1)
        throw std::runtime_error{"Malformed element attributes for " + geom::VectorGraphic::name};
    geom::VectorGraphic vectorGraphic;
    if (vectorGraphicElmnt.getAttribute("closed").getBoolValue()) {
        vectorGraphic.closeShape();
    } else {
        vectorGraphic.openShape();
    }
    for (auto child_elmnt : vectorGraphicElmnt.getAllChildren()) {
        if (!isSaneElement(child_elmnt, "Point"))
            continue;
        vectorGraphic.addPoint(readPoint(child_elmnt));
    }
    const auto hVectorGraphic = std::make_shared<geom::VectorGraphic>(vectorGraphic);
    return hVectorGraphic;
}
framework::PlacedGraphic readPlacedGraphic(const framework::Element &placedGraphicElmnt) {
    if (placedGraphicElmnt.getName() != framework::PlacedGraphic::name)
        throw std::runtime_error{"Expected tag " + framework::PlacedGraphic::name};
    if (placedGraphicElmnt.getAttributeCount() != 2)
        throw std::runtime_error{"Malformed element attributes for " + framework::PlacedGraphic::name};
    framework::PlacedGraphic placedGraphic;
    auto x = placedGraphicElmnt.getAttribute("x").getIntValue();
    auto y = placedGraphicElmnt.getAttribute("y").getIntValue();

    placedGraphic.setPlacementPoint(geom::Point{x, y});

    for (const auto &vectorGraphicElmnt : placedGraphicElmnt.getAllChildren()) {
        if (!isSaneElement(vectorGraphicElmnt, "VectorGraphic"))
            continue;
        const auto hVectorGraphic = readVectorGraphic(vectorGraphicElmnt);
        placedGraphic.setGraphic(hVectorGraphic);
    }

    return placedGraphic;
}
framework::Layer readLayer(const framework::Element &layerElmnt) {
    if (layerElmnt.getName() != framework::Layer::name)
        throw std::runtime_error{"Expected tag " + framework::Layer::name};
    if (layerElmnt.getAttributeCount() != 1)
        throw std::runtime_error{"Malformed element attributes for " + framework::Layer::name};
    Layer layer;
    layer.setAlias(layerElmnt.getAttribute("alias").getStrValue());
    for (const auto &placedGraphicElmnt : layerElmnt.getAllChildren()) {
        if (!isSaneElement(placedGraphicElmnt, "PlacedGraphic"))
            continue;
        auto placedGraphic = readPlacedGraphic(placedGraphicElmnt);
        layer.addGraphic(placedGraphic);
    }
    return layer;
}
framework::Scene readScene(const framework::Element &sceneElmnt) {
    if (sceneElmnt.getName() != framework::Scene::name)
        throw std::runtime_error{"Expected tag " + framework::Scene::name};
    if (sceneElmnt.getAttributeCount() != 2)
        throw std::runtime_error{"Malformed element attributes for " + framework::Scene::name};
    framework::Scene scene;
    auto width = sceneElmnt.getAttribute("width").getIntValue();
    auto height = sceneElmnt.getAttribute("height").getIntValue();
    scene.setWidth(width);
    scene.setHeight(height);
    for (const auto &layerElmnt : sceneElmnt.getAllChildren()) {
        if (!isSaneElement(layerElmnt, "Layer"))
            continue;
        auto layer = readLayer(layerElmnt);
        scene.addLayer(layer);
    }
    return scene;
}
// framework::io write
framework::Element writePoint(const geom::Point &point) {
    framework::Element pt_elmnt(geom::Point::name);
    std::stringstream ss;
    ss << point.getX();
    pt_elmnt.addAttribute(framework::Attribute("x", ss.str()));
    ss.str("");
    ss << point.getY();
    pt_elmnt.addAttribute(framework::Attribute("y", ss.str()));
    return pt_elmnt;
}
framework::Element writeVectorGraphic(const HVectorGraphic &vectorGraphic) {
    framework::Element vg_elmnt(geom::VectorGraphic::name);
    std::string is_closed = (vectorGraphic->isClosed()) ? "true" : "false";
    vg_elmnt.addAttribute(framework::Attribute("closed", is_closed));
    for (int i = 0; i < vectorGraphic->getPointCount(); i++) {
        auto pt_elmnt = writePoint(vectorGraphic->getPoint(i));
        vg_elmnt.addChild(pt_elmnt);
    }
    return vg_elmnt;
}
framework::Element writePlacedGraphic(const framework::PlacedGraphic &placedGraphic) {
    framework::Element pg_elmnt(framework::PlacedGraphic::name);
    // placement attributes
    auto pg_placement = placedGraphic.getPlacementPoint();
    std::stringstream ss;
    ss << pg_placement.getX();
    pg_elmnt.addAttribute(framework::Attribute("x", ss.str()));
    ss.str("");
    ss << pg_placement.getY();
    pg_elmnt.addAttribute(framework::Attribute("y", ss.str()));
    // vector graphic child element
    const auto hVectorGraphic = placedGraphic.getGraphic();
    auto vg_elmnt = writeVectorGraphic(hVectorGraphic);
    pg_elmnt.addChild(vg_elmnt);
    return pg_elmnt;
}
framework::Element writeLayer(const framework::Layer &layer) {
    framework::Element layer_elmnt(framework::Layer::name);
    layer_elmnt.addAttribute(Attribute("alias", layer.getAlias()));
    for (auto graphic : layer.getGraphicCollection()) {
        auto graphic_elmnt = writePlacedGraphic(graphic);
        layer_elmnt.addChild(graphic_elmnt);
    }
    return layer_elmnt;
}
framework::Element writeScene(const framework::Scene &scene) {
    framework::Element scene_elmnt(framework::Scene::name);
    std::stringstream ss;
    ss << scene.getWidth();
    scene_elmnt.addAttribute(framework::Attribute("width", ss.str()));
    ss.str("");
    ss << scene.getHeight();
    scene_elmnt.addAttribute(framework::Attribute("height", ss.str()));
    for (auto layer : scene.getLayerCollection()) {
        auto layer_elmnt = writeLayer(layer);
        scene_elmnt.addChild(layer_elmnt);
    }
    return scene_elmnt;
}
} // namespace framework::io

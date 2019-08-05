#pragma once
#include "point.h"
#include "vectorgraphic.h"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace framework {

using HVectorGraphic = std::shared_ptr<geom::VectorGraphic>;

class PlacedGraphic {
  public:
    static inline const std::string name{"PlacedGraphic"};
    void setPlacementPoint(geom::Point const &placement);
    geom::Point const &getPlacementPoint() const;
    void setGraphic(const HVectorGraphic &graphic);
    HVectorGraphic const &getGraphic() const;

  private:
    geom::Point placementPoint;
    HVectorGraphic graphic;
};
bool operator==(const PlacedGraphic &lhs, const PlacedGraphic &rhs);
bool operator!=(const PlacedGraphic &lhs, const PlacedGraphic &rhs);

class Layer {
  private:
    typedef std::vector<PlacedGraphic> PlacedGraphicCollection;

  public:
    static inline const std::string name{"Layer"};
    typedef PlacedGraphicCollection::iterator PlacedGraphicIterator;

    void addGraphic(PlacedGraphic &pg);
    const PlacedGraphicCollection &getGraphicCollection() const { return graphics; }

    const std::string &getAlias() const;
    void setAlias(const std::string &alias);
    PlacedGraphicIterator begin() { return graphics.begin(); }
    PlacedGraphicIterator end() { return graphics.end(); }
    int getPlacedGraphicCount() { return graphics.size(); }
    bool operator==(const Layer &rhs) const;

  private:
    PlacedGraphicCollection graphics;
    std::string alias;
};
bool operator!=(const Layer &lhs, const Layer &rhs);

class Scene {
  private:
    typedef std::vector<Layer> LayerCollection;

  public:
    static inline const std::string name{"Scene"};
    typedef LayerCollection::iterator LayerIterator;

    void addLayer(Layer &layer);
    void setWidth(const int &newWidth);
    const int &getWidth() const;
    void setHeight(const int &newHeight);
    const int &getHeight() const;
    const LayerCollection &getLayerCollection() const { return layers; }
    LayerIterator begin() { return layers.begin(); }
    LayerIterator end() { return layers.end(); }
    int getLayerCount() { return static_cast<int>(std::distance(begin(), end())); }
    bool operator==(const Scene &rhs) const;

  private:
    LayerCollection layers;
    int width{0};
    int height{0};
};
bool operator!=(const Scene &lhs, const Scene &rhs);

class Attribute {
  public:
    Attribute(const std::string &attr_name, const std::string &attr_value) : name{attr_name}, value{attr_value} {}
    const std::string &getName() const { return name; }
    const std::string &getStrValue() const { return value; }
    const int getIntValue() const;
    const bool getBoolValue() const;

  private:
    std::string name;
    std::string value;
};

enum class ElementType { element, document, comment, declaration, text, unknown };
class Element {
  public:
    Element(const std::string &elmnt_name, const ElementType &elmnt_type = ElementType::element)
        : name{elmnt_name}, type{elmnt_type} {}
    const std::string &getName() const { return name; }
    const std::vector<Attribute> &getAllAttributes() const { return attributes; }
    int getAttributeCount() const { return attributes.size(); }
    const Attribute &getAttribute(const std::string name) const;
    void addAttribute(const Attribute &attr) { attributes.push_back(attr); }
    int getChildCount() const { return children.size(); }
    const std::vector<Element> &getAllChildren() const { return children; }
    const Element getChild(const unsigned int &i) const { return children.at(i); }
    void addChild(const Element &elmnt) { children.push_back(elmnt); }
    bool isElement() const { return (type == ElementType::element); }
    bool isDocument() const { return type == ElementType::document; }
    bool isComment() const { return type == ElementType::comment; }
    bool isDeclaration() const { return type == ElementType::declaration; }
    bool isText() const { return type == ElementType::text; }
    bool isUnknown() const { return type == ElementType::unknown; }

  private:
    std::string name;
    ElementType type;
    std::vector<Attribute> attributes;
    std::vector<Element> children;
};
} // namespace framework

namespace framework::io {
// translate framework elements from/to XML
framework::Element elementFromXML(const tinyxml2::XMLNode *elmnt);
tinyxml2::XMLNode *elementToXML(const framework::Element &framework_elmnt, tinyxml2::XMLDocument &doc);
// sanity check helper
bool isSaneElement(const framework::Element &elmnt, const std::string &name);
// read
geom::Point readPoint(const framework::Element &pointElmnt);
HVectorGraphic readVectorGraphic(const framework::Element &vectorGraphicElmnt);
framework::PlacedGraphic readPlacedGraphic(const framework::Element &placedGraphicElmnt);
framework::Layer readLayer(const framework::Element &layerElmnt);
framework::Scene readScene(const framework::Element &sceneElmnt);
// write
framework::Element writePoint(const geom::Point &point);
framework::Element writeVectorGraphic(const HVectorGraphic &vectorGraphic);
framework::Element writePlacedGraphic(const framework::PlacedGraphic &placedGraphic);
framework::Element writeLayer(const framework::Layer &layer);
framework::Element writeScene(const framework::Scene &scene);
} // namespace framework::io

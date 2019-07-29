#include "vectorgraphic.h"
#include "marshaller.h"
#include "point.h"
#include <algorithm>
#include <vector>

namespace geom {
void VectorGraphic::openShape() { is_open = true; }
void VectorGraphic::closeShape() { is_open = false; }
void VectorGraphic::addPoint(const Point &point) { points.push_back(point); }
void VectorGraphic::removePoint(const Point &point) {
    // removes point if it is in points, otherwise nop
    points.erase(std::remove(points.begin(), points.end(), point), points.end());
}
void VectorGraphic::erasePoint(int index) {
    // given an index take return the point at (index mod size), error is thrown if size is 0
    removePoint(getPoint(index)); // use removePoint to ensure error handling
}
int VectorGraphic::getWidth() const {
    // return the x_coord distance as max(points) - min(points)
    Point point;
    int min = 0;
    int max = 0;

    for (int i = 0; i < getPointCount(); ++i) {
        point = getPoint(i);
        if (i != 0) {
            min = std::min(point.getX(), min);
            max = std::max(point.getX(), max);
        } else {
            min = point.getX();
            max = point.getX();
        }
    }
    return max - min;
}
int VectorGraphic::getHeight() const {
    // return the y_coord distance as max(points) - min(points)
    Point point;
    int min = point.getY();
    int max = point.getY();

    for (int i = 0; i < getPointCount(); ++i) {
        point = getPoint(i);
        if (i != 0) {
            min = std::min(point.getY(), min);
            max = std::max(point.getY(), max);
        } else {
            min = point.getY();
            max = point.getY();
        }
    }
    return max - min;
}
int VectorGraphic::getPointCount() const { return static_cast<int>(points.size()); }
const Point &VectorGraphic::getPoint(unsigned int index) const { return points.at(index); }
std::ostream &operator<<(std::ostream &os, const VectorGraphic &vg) {
    return marshaller::markup_stream<VectorGraphic>(os, vg);
}
std::string VectorGraphic::get_human_readable() const {
    std::stringstream ss;
    ss << "VectorGraphic" << (isClosed() ? " is closed" : " is not closed");
    if (getPointCount() == 0) {
        ss << " and does not have points.";
    } else {
        ss << " and has points:";
        for (auto i = 0; i < getPointCount(); ++i) {
            ss << std::endl << "  " << (getPoint(i)).get_human_readable();
        }
    }
    ss << std::endl;
    return ss.str();  // copy elision
}
std::string VectorGraphic::get_xml() const {
    std::stringstream ss;
    std::string closed = (isClosed()) ? "true" : "false";
    ss << "<VectorGraphic closed=\"" << closed << "\"";
    if (getPointCount() == 0) {
        ss << "/>" << std::endl;
    } else {
        ss << ">" << std::endl;
        for (auto i = 0; i < getPointCount(); ++i) {
            ss << (getPoint(i)).get_xml() << std::endl;
        }
        ss << "</VectorGraphic>";
    }
    return ss.str();  // copy elision
}
} // namespace geom

namespace marshaller {
} // namespace marshaller

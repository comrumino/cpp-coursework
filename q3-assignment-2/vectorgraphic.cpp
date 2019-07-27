#include "vectorgraphic.h"
#include "point.h"
#include <algorithm>
#include <vector>

VectorGraphic::VectorGraphic() {
    // std::cout << "Point default ctor" << std::endl;
}
VectorGraphic::~VectorGraphic() {
    // std::cout << "Point default dtor" << std::endl;
}
VectorGraphic::VectorGraphic(const VectorGraphic &rhs) : points{rhs.points}, is_open{rhs.is_open} {
    // std::cout << "VectorGraphic direct ctor" << std::endl;
}
VectorGraphic::VectorGraphic(VectorGraphic &&other) noexcept
    : points{std::exchange(other.points, Points())}, is_open{std::exchange(other.is_open, false)},
      stream_as{std::exchange(other.stream_as, stream_as)} {
    // std::cout << "VectorGraphic move ctor" << std::endl;
}
VectorGraphic &VectorGraphic::operator=(const VectorGraphic &rhs) {
    // std::cout << "VectorGraphic assign ctor" << std::endl;
    if (this != &rhs) {
        this->points = rhs.points;
        this->is_open = rhs.is_open;
        this->stream_as = rhs.stream_as;
    }
    return *this;
}
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
Point VectorGraphic::getPoint(unsigned int index) const {
    return points.at(index);
}
std::ostream &VectorGraphic::as_human_readable(std::ostream &os) const {
    std::string closed = (isClosed()) ? " is closed" : " is not closed";
    os << "VectorGraphic" << closed;
    if (getPointCount() == 0) {
        os << " and does not have points." << std::endl;
    } else {
        os << " and has points:" << std::endl;;
        for (auto pt : points) {
            os << "  ";
            pt.as_human_readable(os);
            os << "\n";
        }
    }
    return os;
}
std::ostream &VectorGraphic::as_xml(std::ostream &os) const {
    std::string closed = (isClosed()) ? "true" : "false";
    os << "<VectorGraphic closed=\"" << closed << "\"";
    if (getPointCount() == 0) {
        os << "/>\n";
    } else {
        os << ">\n";
        for (auto pt : points) {
            os << pt << "\n";
        }
        os << "</VectorGraphic>";
    }
    return os;
}
std::ostream &operator<<(std::ostream &os, const VectorGraphic &vg) {
    if (vg.stream_as == "xml") {
        return vg.as_xml(os);
    } else {
        return os;
    }
}

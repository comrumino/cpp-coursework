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
    : points{std::exchange(other.points, Points())}, is_open{std::exchange(other.is_open, false)} {
    // std::cout << "VectorGraphic move ctor" << std::endl;
}
VectorGraphic &VectorGraphic::operator=(const VectorGraphic &rhs) {
    // std::cout << "VectorGraphic assign ctor" << std::endl;
    if (this != &rhs) {
        this->points = rhs.points;
        this->is_open = rhs.is_open;
    }
    return *this;
}
VectorGraphic &VectorGraphic::operator=(VectorGraphic &&other) noexcept {
    // std::cout << "VectorGraphic move assign ctor" << std::endl;
    std::swap(points, other.points);
    std::swap(is_open, other.is_open);
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
    int min = point.getX();
    int max = point.getX();

    for (int i = 0; i < getPointCount(); ++i) {
        point = getPoint(i);
        if (i != 0) {
            if (point.getX() < min) { // new min x
                min = point.getX();
            } else if (point.getX() > max) { // new max x
                max = point.getX();
            }
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
            if (point.getY() < min) { // new min x
                min = point.getY();
            } else if (point.getY() > max) { // new max x
                max = point.getY();
            }
        } else {
            min = point.getY();
            max = point.getY();
        }
    }
    return max - min;
}
int VectorGraphic::getPointCount() const { return static_cast<int>(points.size()); }
Point VectorGraphic::getPoint(int index) const {
    int points_sz = getPointCount();
    if (points_sz == 0) { // modulo operation is undefined if modulus is zero
        return points.at(points_sz);
    }
    index %= points_sz;
    if (index < 0) { // shift negative values so it is a valid offset
        index += points_sz;
    }
    return points.at(index);
}
std::ostream &operator<<(std::ostream &os, const VectorGraphic &vg) {
    std::string closed = (vg.isClosed()) ? "true" : "false";
    os << "<VectorGraphic closed=\"" << closed << "\"";
    if (vg.getPointCount() == 0) {
        os << "/>\n";
    } else {
        os << ">\n";
        for (auto pt : vg.points) {
            os << pt << "\n";
        }
        os << "</VectorGraphic>";
    }
    return os;
}

#include "vectorgraphic.h"
#include "point.h"
#include <algorithm>
#include <vector>
/*
class BaseException {
  public:
    BaseException() {}
    virtual ~BaseException() {}

    virtual const char *message() const noexcept = 0;
};

class VectorGraphicEmptyException : public BaseException {
  public:
    VectorGraphicEmptyException() = default;
    const char *message() const noexcept override;
};

const char *VectorGraphicEmptyException::message() const noexcept { return "VectorGraphicEmpty"; }
VectorGraphic::VectorGraphic() {
}
VectorGraphic::~VectorGraphic() {
}
*/
VectorGraphic::VectorGraphic(const VectorGraphic &rhs) : points{rhs.points}, is_open{rhs.is_open} {
    // std::cout << "VectorGraphic direct ctor" << std::endl;
}
VectorGraphic &VectorGraphic::operator=(const VectorGraphic &rhs) {
    // std::cout << "VectorGraphic assign ctor" << std::endl;
    if (this != &rhs) {
        this->points = rhs.points;
        this->is_open = rhs.is_open;
    }
    return *this;
}

void VectorGraphic::addPoint(const Point &point) { points.push_back(point); }
void VectorGraphic::removePoint(const Point &point) {
    points.erase(std::remove(points.begin(), points.end(), point), points.end());
}
void VectorGraphic::erasePoint(int index) {
    removePoint(getPoint(index)); // use removePoint to ensure error handling
}
void VectorGraphic::openShape() { is_open = true; }
void VectorGraphic::closeShape() { is_open = false; }
bool VectorGraphic::isOpen() const { return is_open; }
bool VectorGraphic::isClosed() const { return !isOpen(); }

int VectorGraphic::getWidth() const {
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
int VectorGraphic::getPointCount() const { return points.size(); }
Point VectorGraphic::getPoint(int index) const {
    int points_sz = points.size();
    if (points_sz == 0) { // modulo operation is undefined if modulus is zero
        return points.at(points_sz);
    }
    index %= points_sz;
    if (index < 0) { // shift negative values so it is a valid offset
        index += points_sz;
    }
    return points.at(index);
}

#include "point.h"
#include <sstream>

Point::Point(const float x, const float y) : x(x), y(y) {}

std::ostream &operator<<(std::ostream &os, const Point &pt) {
    os << pt.x << "," << pt.y;
    return os;
}

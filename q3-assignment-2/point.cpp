#include "point.h"
#include "marshaller.h"
#include <iostream>
#include <utility>

namespace geom {
void Point::setX(int rhs_x_coord) { x_coord = rhs_x_coord; }
void Point::setY(int rhs_y_coord) { y_coord = rhs_y_coord; }
std::ostream &operator<<(std::ostream &os, const Point &point) {
    return marshaller::markup_stream<Point>(os, point);
}
bool operator==(const Point &lhs, const Point &rhs) { return rhs.getX() == lhs.getX() && rhs.getY() == lhs.getY(); }
bool operator!=(const Point &lhs, const Point &rhs) { return !(lhs == rhs); }

std::string Point::get_human_readable() const {
    std::stringstream ss;
    ss << "(" << getX() << ", " << getY() << ")";
    return ss.str(); // copy elision
}

std::string Point::get_xml() const {
    std::stringstream ss;
    ss << "<Point x=\"" << getX() << "\" y=\"" << getY() << "\"/>";
    return ss.str(); // copy elision
}
} // namespace geom

namespace marshaller {

} // namespace marshaller

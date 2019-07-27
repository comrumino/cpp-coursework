#include "point.h"
#include <iostream>
#include <utility>

Point::Point() {
    // std::cout << "Point Default Ctor " << *this << std::endl;
}
Point::~Point() {
    // std::cout << "Point Dtor" << std::endl;
}
Point::Point(int x, int y) : x_coord{x}, y_coord{y} {
    // std::cout << "Point arg ctor " << *this << std::endl;
}
Point::Point(const Point &other) : x_coord{other.x_coord}, y_coord{other.y_coord} {
    // std::cout << "Point copy ctor " << *this << std::endl;
}
Point::Point(Point &&other) noexcept
    : x_coord{std::exchange(other.x_coord, 0)}, y_coord{std::exchange(other.y_coord, 0)},
      stream_as{std::exchange(other.stream_as, "xml")} {
    // std::cout << "Point move ctor " << *this << std::endl;
}
Point &Point::operator=(const Point &rhs) {
    // std::cout << "Point Assign Ctor " << *this << std::endl;
    if (this != &rhs) {
        this->x_coord = rhs.x_coord;
        this->y_coord = rhs.y_coord;
    }
    return *this;
}
bool Point::operator==(const Point &rhs) {
    bool equivalent = true;
    if (this != &rhs) {
        equivalent &= this->x_coord == rhs.x_coord;
        equivalent &= this->y_coord == rhs.y_coord;
        equivalent &= this->stream_as == rhs.stream_as;
    }
    return equivalent;
}
void Point::setX(int rhs_x_coord) { x_coord = rhs_x_coord; }
void Point::setY(int rhs_y_coord) { y_coord = rhs_y_coord; }
std::ostream &Point::as_human_readable(std::ostream &os) const {
    os << "(" << x_coord << ", " << y_coord << ")";
    return os;
}
std::ostream &Point::as_xml(std::ostream &os) const {
    os << "<Point x=\"" << x_coord << "\" y=\"" << y_coord << "\"/>";
    return os;
}
std::ostream &operator<<(std::ostream &os, const Point &point) {
    if (point.stream_as == "xml") {
        return point.as_xml(os);
    } else {
        return os;
    }
}

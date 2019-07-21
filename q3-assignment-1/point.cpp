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
    : x_coord{std::exchange(other.x_coord, 0)}, y_coord{std::exchange(other.y_coord, 0)} {
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
Point &Point::operator=(Point &&other) noexcept {
    std::swap(x_coord, other.x_coord);
    std::swap(y_coord, other.y_coord);
    // std::cout << "Point move assignment " << *this << std::endl;
    return *this;
}
bool Point::operator==(const Point &rhs) {
    bool equivalent = true;
    if (this != &rhs) {
        equivalent &= this->x_coord == rhs.x_coord;
        equivalent &= this->y_coord == rhs.y_coord;
    }
    return equivalent;
}
void Point::setX(int rhs_x_coord) { x_coord = rhs_x_coord; }
void Point::setY(int rhs_y_coord) { y_coord = rhs_y_coord; }
std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "<Point x=\"" << point.x_coord << "\" y=\"" << point.y_coord << "\"/>";
    return os;
}

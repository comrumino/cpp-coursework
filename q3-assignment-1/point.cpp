#include "point.h"
#include <iostream>
#include <utility>

Point::Point() {
    // std::cout << "Point Default Ctor " << *this << std::endl;
}

Point::Point(int x, int y) : x_coord{x}, y_coord{y} {
    // std::cout << "Point arg Ctor " << *this << std::endl;
}

Point::Point(const Point &other)
    : x_coord{other.x_coord}, y_coord{other.y_coord} { // std::cout << "Point Copy Ctor " << *this << std::endl;
}

Point::Point(Point &&other) : x_coord(std::exchange(other.x_coord, 0)), y_coord(std::exchange(other.y_coord, 0)) {
    // std::cout << "Point Move Ctor " << *this << std::endl;
}

Point::~Point() {
    // std::cout << "Point Dtor" << std::endl;
}

int Point::getX() const { return x_coord; }
int Point::getY() const { return y_coord; }
void Point::setX(int rhs_x_coord) { x_coord = rhs_x_coord; }
void Point::setY(int rhs_y_coord) { y_coord = rhs_y_coord; }

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
    }
    return equivalent;
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x_coord << "," << point.y_coord << ")";
    return os;
}

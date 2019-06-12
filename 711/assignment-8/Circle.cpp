/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 8.1 Shapes
 *  Problem Statement:
 *      Define classes Triangle, Circle, and Rectangle:
 *       + Subclass each from base class Shape.
 *       + Add the appropriate constructor to set the geometry for each subclass.
 *       + Add appropriate accessor member functions to get the geometry for each class.
 *       + Overload the virtual member functions inherited from Shape.
 *      Note the virtual member function draw is somewhat contrived here as it will not actually draw the geometry;
 *      Instead draw will output the geometry in text format to the specified ostream.
 */
#include "Circle.h"
#include <ostream>

Circle::Circle(const Point& pnt, const float rad)
    :Shape(), pnt(pnt), rad(rad)
{
}

const Point& Circle::getPoint() const {
    return pnt;
}

const float& Circle::getRadius() const {
    return rad;
}

void Circle::draw(std::ostream& os) const {
    os << "draw circle: " << getPoint() << "," << getRadius();
}

void Circle::stream(std::ostream& os) const {
    draw(os);
}

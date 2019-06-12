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
#include "Triangle.h"
#include <ostream>

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3)
    :Shape(), v1(v1), v2(v2), v3(v3)
{
}

const Point& Triangle::getV1() const {
    return v1;
}

const Point& Triangle::getV2() const {
    return v2;
}

const Point& Triangle::getV3() const {
    return v3;
}

void Triangle::draw(std::ostream& os) const {
    os << "draw triangle: ";
    os << getV1() << ",";
    os << getV2() << ",";
    os << getV3();
}

void Triangle::stream(std::ostream& os) const {
    draw(os);
}

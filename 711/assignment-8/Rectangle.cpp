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
#include "Rectangle.h"
#include <ostream>

Rectangle::Rectangle(const Point& ul_pt, const Point& lr_pt)
    :Shape(), ul_pt(ul_pt), lr_pt(lr_pt)
{
}

const Point& Rectangle::getUpperLeftPoint() const {
    return ul_pt;
}

const Point& Rectangle::getLowerRightPoint() const {
    return lr_pt;
}

void Rectangle::draw(std::ostream& os) const {
    os << "draw rectangle: ";
    os << getUpperLeftPoint() << ",";
    os << getLowerRightPoint();
}

void Rectangle::stream(std::ostream& os) const {
    draw(os);
}

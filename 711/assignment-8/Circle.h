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
#pragma once
#include "Point.h"
#include "Shape.h"
#include <ostream>

class Circle : public Shape
{
public:
    Circle(const Point& pnt, const float rad);
    ~Circle() = default;  // Points are a trivial classes, so okay to use the to default
    const Point& getPoint() const;
    const float& getRadius() const;
    void draw(std::ostream& os) const;
    void stream(std::ostream& os) const;

private:
    const Point pnt;
    const float rad;
};

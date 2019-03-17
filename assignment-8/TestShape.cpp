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
#include "TestHarness.h"

#include "Point.h"
#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

#include <memory>
#include <sstream>

TEST(Point, test) {
    Point pt(1, 2);
    std::stringstream ss;
    ss << pt;
    CHECK_EQUAL("1,2", ss.str());
}

TEST(Triangle, ctor) {
    const Point pt1(0, 0);
    const Point pt2(1, 1);
    const Point pt3(2, 2);
    Triangle trngl(pt1, pt2, pt3);
    std::stringstream ss;
    ss << trngl;
    CHECK_EQUAL("draw triangle: 0,0,1,1,2,2", ss.str());
}

TEST(Rectangle, ctor) {
    const Point pt1(0, 0);
    const Point pt2(1, 1);
    Rectangle rctngl(pt1, pt2);
    std::stringstream ss;
    ss << rctngl;
    CHECK_EQUAL("draw rectangle: 0,0,1,1", ss.str());
}

TEST(Circle, ctor) {
    const Point pt1(0, 0);
    Circle crcl(pt1, 1);
    std::stringstream ss;
    ss << crcl;
    CHECK_EQUAL("draw circle: 0,0,1", ss.str());
}

TEST(Shape, dynamic_triangle) {
    std::stringstream message;
    Shape* shp = new Triangle(Point(11.1, 22.2), Point(33.3, 44.4), Point(55.5, 66.6));
    shp->draw(message);
    CHECK_EQUAL("draw triangle: 11.1,22.2,33.3,44.4,55.5,66.6", message.str());
    delete shp;
    message.str("");
    shp = new Rectangle(Point(11.1, 22.2), Point(33.3, 44.4));
    shp->draw(message);
    CHECK_EQUAL("draw rectangle: 11.1,22.2,33.3,44.4", message.str());
    delete shp;
}

TEST(drawUnique, Shape)
{
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Triangle>(Point(11.1, 22.2), Point(33.3, 44.4), Point(55.5, 66.6)));
    shapes.push_back(std::make_unique<Rectangle>(Point(11.1, 22.2), Point(33.3, 44.4)));
    shapes.push_back(std::make_unique<Circle>(Point(111.1, 222.2), 333.3));

    std::stringstream message;

    for (auto& shape: shapes)
    {
        shape->draw(message);
    }

    CHECK_EQUAL("draw triangle: 11.1,22.2,33.3,44.4,55.5,66.6draw rectangle: 11.1,22.2,33.3,44.4draw circle: 111.1,222.2,333.3", message.str());
}

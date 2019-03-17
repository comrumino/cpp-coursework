#pragma once
#include "Point.h"
#include "Shape.h"
#include <ostream>

class Circle : public Shape
{
public:
    Circle(const Point& pnt, const float rad);
    const Point& getPoint() const;
    const float& getRadius() const;
    void draw(std::ostream& os) const;
    void stream(std::ostream& os) const;

private:
    const Point pnt;
    const float rad;
};

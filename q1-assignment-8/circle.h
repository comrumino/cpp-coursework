#pragma once
#include "point.h"
#include "shape.h"
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

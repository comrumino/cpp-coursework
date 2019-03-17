#pragma once
#include "Point.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(const Point& ul_pt, const Point& br_pt);
    ~Rectangle() = default;
    void draw(std::ostream& os) const;
    void stream(std::ostream& os) const;

private:
    const Point& ul_pt;
    const Point& br_pt;
};

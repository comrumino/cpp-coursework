#pragma once
#include "point.h"
#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(const Point& ul_pt, const Point& lr_pt);
    ~Rectangle() = default;  // Points are a trivial classes, so okay to use the to default
    const Point& getUpperLeftPoint() const;
    const Point& getLowerRightPoint() const;
    void draw(std::ostream& os) const;
    void stream(std::ostream& os) const;

private:
    const Point ul_pt;
    const Point lr_pt;
};

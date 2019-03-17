#pragma once
#include "Point.h"
#include "Shape.h"
#include <ostream>

class Triangle : public Shape
{
public:
    Triangle(const Point& v1, const Point& v2, const Point& v3);
    ~Triangle() = default;
    void draw(std::ostream& os) const;
    void stream(std::ostream& os) const;
    const Point& getV1() const;
    const Point& getV2() const;
    const Point& getV3() const;

private:
    const Point v1;
    const Point v2;
    const Point v3;
};

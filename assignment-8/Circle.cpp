#include "Circle.h"

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

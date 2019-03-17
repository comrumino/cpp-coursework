#include "Circle.h"

Circle::Circle(const Point& pnt, const float flt)
    :Shape(), pnt(pnt), flt(flt)
{
}

void Circle::draw(std::ostream& os) const {
    os << "draw circle: " << pnt << "," << flt;
}

void Circle::stream(std::ostream& os) const {
    draw(os);
}

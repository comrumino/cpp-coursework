#include "Triangle.h"
#include <sstream>

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3)
    :v1(v1), v2(v2), v3(v3), Shape()
{
}

const Point& Triangle::getV1() const {
    return v1;
}

const Point& Triangle::getV2() const {
    return v2;
}

const Point& Triangle::getV3() const {
    return v3;
}

void Triangle::draw(std::ostream& os) const {
    os << "draw triangle: " << v1 << "," << v2 << "," << v3;
}

void Triangle::stream(std::ostream& os) const {
    draw(os);
}

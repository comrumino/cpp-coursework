#include "Rectangle.h"
#include <ostream>


Rectangle::Rectangle(const Point& ul_pt, const Point& br_pt)
    :Shape(), ul_pt(ul_pt), br_pt(br_pt)
{
}

const Point& Rectangle::getUpperLeftPoint() const {
    return ul_pt;
}

const Point& Rectangle::getLowerRightPoint() const {
    return br_pt;
}

void Rectangle::draw(std::ostream& os) const {
    os << "draw rectangle: " << ul_pt << "," << br_pt;
}

void Rectangle::stream(std::ostream& os) const {
    draw(os);
}

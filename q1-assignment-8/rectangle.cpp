#include "rectangle.h"
#include <ostream>

Rectangle::Rectangle(const Point& ul_pt, const Point& lr_pt)
    :Shape(), ul_pt(ul_pt), lr_pt(lr_pt)
{
}

const Point& Rectangle::getUpperLeftPoint() const {
    return ul_pt;
}

const Point& Rectangle::getLowerRightPoint() const {
    return lr_pt;
}

void Rectangle::draw(std::ostream& os) const {
    os << "draw rectangle: ";
    os << getUpperLeftPoint() << ",";
    os << getLowerRightPoint();
}

void Rectangle::stream(std::ostream& os) const {
    draw(os);
}

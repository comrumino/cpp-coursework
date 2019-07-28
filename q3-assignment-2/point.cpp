#include "point.h"
#include "marshaller.h"
#include <iostream>
#include <utility>

namespace geom {
    bool operator==(const Point& lhs, const Point& rhs)
    {
        return rhs.getX() == lhs.getX() && rhs.getY() == lhs.getY();
    }
    
    bool operator!=(const Point& lhs, const Point& rhs)
    {
        return ! (lhs == rhs);
    }

void Point::setX(int rhs_x_coord) { x_coord = rhs_x_coord; }
void Point::setY(int rhs_y_coord) { y_coord = rhs_y_coord; }
std::ostream &operator<<(std::ostream &os, const Point &point) {
    if (point.markup == marshaller::Markup::xml) {
        return marshaller::xml(os, point);
    } else {
        return marshaller::human_readable(os, point);
    }
}
}

namespace marshaller {
    std::ostream &human_readable(std::ostream &os, const geom::Point &pt) {
        os << "(" << pt.getX() << ", " << pt.getY() << ")";
        return os;
    }

    std::ostream &xml(std::ostream &os, const geom::Point &pt) {
        os << "<Point x=\"" << pt.getX() << "\" y=\"" << pt.getY() << "\"/>";
        return os;
    }

}

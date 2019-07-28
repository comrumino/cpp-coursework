#include "vectorgraphic.h"
#include "point.h"
#include "marshaller.h"
#include <algorithm>
#include <vector>

namespace geom {
void VectorGraphic::openShape() { is_open = true; }
void VectorGraphic::closeShape() { is_open = false; }
void VectorGraphic::addPoint(const Point &point) { points.push_back(point); }
void VectorGraphic::removePoint(const Point &point) {
    // removes point if it is in points, otherwise nop
    points.erase(std::remove(points.begin(), points.end(), point), points.end());
}
void VectorGraphic::erasePoint(int index) {
    // given an index take return the point at (index mod size), error is thrown if size is 0
    removePoint(getPoint(index)); // use removePoint to ensure error handling
}
int VectorGraphic::getWidth() const {
    // return the x_coord distance as max(points) - min(points)
    Point point;
    int min = 0;
    int max = 0;

    for (int i = 0; i < getPointCount(); ++i) {
        point = getPoint(i);
        if (i != 0) {
            min = std::min(point.getX(), min);
            max = std::max(point.getX(), max);
        } else {
            min = point.getX();
            max = point.getX();
        }
    }
    return max - min;
}
int VectorGraphic::getHeight() const {
    // return the y_coord distance as max(points) - min(points)
    Point point;
    int min = point.getY();
    int max = point.getY();

    for (int i = 0; i < getPointCount(); ++i) {
        point = getPoint(i);
        if (i != 0) {
            min = std::min(point.getY(), min);
            max = std::max(point.getY(), max);
        } else {
            min = point.getY();
            max = point.getY();
        }
    }
    return max - min;
}
int VectorGraphic::getPointCount() const { return static_cast<int>(points.size()); }
const Point &VectorGraphic::getPoint(unsigned int index) const {
    return points.at(index);
}
std::ostream &operator<<(std::ostream &os, const VectorGraphic &vg) {
    if (vg.markup == marshaller::Markup::xml) {
        return marshaller::xml(os, vg);
    } else {
        return marshaller::human_readable(os, vg);
    }
}
}


namespace marshaller {
std::ostream &human_readable(std::ostream &os, const geom::VectorGraphic &vg) {
    std::string closed = (vg.isClosed()) ? " is closed" : " is not closed";
    os << "VectorGraphic" << closed;
    if (vg.getPointCount() == 0) {
        os << " and does not have points." << std::endl;
    } else {
        os << " and has points:" << std::endl;;
        for (auto i = 0; i < vg.getPointCount(); ++i) {
            auto& pt = vg.getPoint(i);
            os << "  ";
            marshaller::human_readable(os, pt);
            os << std::endl;
        }
    }
    return os;
}
std::ostream &xml(std::ostream &os, const geom::VectorGraphic &vg) {
    std::string closed = (vg.isClosed()) ? "true" : "false";
    os << "<VectorGraphic closed=\"" << closed << "\"";
    if (vg.getPointCount() == 0) {
        os << "/>" << std::endl;
    } else {
        os << ">" << std::endl;
        for (auto i = 0; i < vg.getPointCount(); ++i) {
            auto& pt = vg.getPoint(i);
            marshaller::xml(os, pt);
            os << std::endl;
        }
        os << "</VectorGraphic>";
    }
    return os;
}
}


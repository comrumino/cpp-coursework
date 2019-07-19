#include "vectorgraphic.h"
#include "point.h"
#include <vector>

VectorGraphic::VectorGraphic() {
}
VectorGraphic::~VectorGraphic() {
}
void VectorGraphic::addPoint(const Point& p) {
}
void VectorGraphic::removePoint(const Point& p) {
}
void VectorGraphic::erasePoint(int index) {
}
void VectorGraphic::openShape() {
}
void VectorGraphic::closeShape() {
}
bool VectorGraphic::isOpen() const {
    return false;
}
bool VectorGraphic::isClosed() const {
    return false;
}
int VectorGraphic::getWidth() const {
    return 0;
}
int VectorGraphic::getHeight() const {
    return 0;
}
int VectorGraphic::getPointCount() const {
    return 0;
}
Point VectorGraphic::getPoint(int index) const {
    return Point();
}

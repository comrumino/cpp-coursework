#pragma once
#include "point.h"
#include "shape.h"
#include <ostream>

class Triangle : public Shape {
  public:
    Triangle(const Point &v1, const Point &v2, const Point &v3);
    ~Triangle() = default; // Points are a trivial classes, so okay to use the to default
    const Point &getV1() const;
    const Point &getV2() const;
    const Point &getV3() const;
    void draw(std::ostream &os) const;
    void stream(std::ostream &os) const;

  private:
    const Point v1;
    const Point v2;
    const Point v3;
};

#pragma once
#include "point.h"
#include <vector>
using Points = std::vector<Point>;

class VectorGraphic {
  public:
    VectorGraphic() = default;
    ~VectorGraphic() = default;
    VectorGraphic(const VectorGraphic &rhs);
    VectorGraphic &operator=(const VectorGraphic &rhs);

    void addPoint(const Point &point);
    void removePoint(const Point &point);
    void erasePoint(int index);

    void openShape();
    void closeShape();

    bool isOpen() const;
    bool isClosed() const;

    int getWidth() const;
    int getHeight() const;

    int getPointCount() const;
    Point getPoint(int index) const;

  private:
    Points points;
    bool is_open = false;
};

#pragma once
#include "point.h"
#include <vector>

using Points = std::vector<Point>;

class VectorGraphic {
  public:
    // Rule of 5, in this case default definitions would have sufficed. Even so
    VectorGraphic();                                        // default ctor
    ~VectorGraphic();                                       // default dtor
    VectorGraphic(const VectorGraphic &rhs);                // copy ctor
    VectorGraphic(VectorGraphic &&rhs) noexcept;            // copy ctor
    VectorGraphic &operator=(const VectorGraphic &rhs);     // assign ctor
    VectorGraphic &operator=(VectorGraphic &&rhs) noexcept; // move assign ctor

    constexpr bool isOpen() const { return is_open; }
    constexpr bool isClosed() const { return !isOpen(); }
    void openShape();
    void closeShape();

    void addPoint(const Point &point);
    void removePoint(const Point &point);
    void erasePoint(int index);
    int getWidth() const;
    int getHeight() const;
    int getPointCount() const;
    Point getPoint(int index) const;

    friend std::ostream &operator<<(std::ostream &os, const VectorGraphic &vg);

  private:
    Points points;
    bool is_open = false;
};

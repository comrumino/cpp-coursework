#pragma once
#include "point.h"
#include <vector>

namespace geom {
using Points = std::vector<Point>;

class VectorGraphic {
  public:
    // Rule of 5, in this case default definitions would have sufficed. Even so
    VectorGraphic() = default;                                    // default ctor
    ~VectorGraphic() = default;                                   // default dtor
    VectorGraphic(const VectorGraphic &rhs) = default;            // copy ctor
    VectorGraphic(VectorGraphic &&rhs) noexcept = default;        // copy ctor
    VectorGraphic &operator=(const VectorGraphic &rhs) = default; // assign ctor
    // considerations of move assignment operator
    // http://scottmeyers.blogspot.com/2014/06/the-drawbacks-of-implementing-move.html
    VectorGraphic &operator=(VectorGraphic &&rhs) noexcept = default; // move assign ctor
    std::string get_human_readable() const;
    std::string get_xml() const;

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
    const Point &getPoint(unsigned int index) const;

    friend std::ostream &operator<<(std::ostream &os, const VectorGraphic &vg);

  private:
    Points points;
    bool is_open = false;
};
} // namespace geom

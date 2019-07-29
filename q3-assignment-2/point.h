#pragma once
#include "marshaller.h"
#include <iostream>
#include <sstream>
#include <string>

namespace geom {
class Point {
  public:
    // Rule of 5, in this case default definitions would have sufficed. Even so
    constexpr Point(int x, int y) : x_coord{x}, y_coord{y} {}

    Point() = default;                                // default ctor
    ~Point() = default;                               // default dtor
    Point(const Point &other) = default;              // copy ctor
    Point(Point &&other) noexcept = default;          // move ctor
    Point &operator=(const Point &rhs) = default;     // assign ctor
    Point &operator=(Point &&rhs) noexcept = default; // move assign ctor
    std::string get_human_readable() const;
    std::string get_xml() const;

    constexpr int getX() const { return x_coord; }
    constexpr int getY() const { return y_coord; }

    void setX(int rhs_x_coord);
    void setY(int rhs_y_coord);

    friend std::ostream &operator<<(std::ostream &os, const Point &point);

  private:
    marshaller::Markup markup{marshaller::Markup::xml};
    int x_coord{0};
    int y_coord{0};
};
bool operator==(const Point &lhs, const Point &rhs);
bool operator!=(const Point &lhs, const Point &rhs);
} // namespace geom

namespace marshaller {
} // namespace marshaller

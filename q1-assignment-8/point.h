#pragma once
#include <sstream>

class Point {
  public:
    Point() = delete;
    Point(const float x, const float y);
    Point(const Point &src) = default;            // direct copy constructor
    Point &operator=(const Point &rhs) = default; // assignment copy constructor
    const float x;
    const float y;
    friend std::ostream &operator<<(std::ostream &os, const Point &pt);
};

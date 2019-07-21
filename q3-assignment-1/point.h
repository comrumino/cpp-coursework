#pragma once
#include <iostream>

class Point {
  public:
    // Rule of 5, in this case default definitions would have sufficed. Even so
    Point();                                // default ctor
    ~Point();                               // default dtor
    Point(int x, int y);                    // direct ctor
    Point(const Point &other);              // copy ctor
    Point(Point &&other) noexcept;          // move ctor
    Point &operator=(const Point &rhs);     // assign ctor
    Point &operator=(Point &&rhs) noexcept; // move assign ctor

    constexpr int getX() const { return x_coord; }
    constexpr int getY() const { return y_coord; }

    void setX(int rhs_x_coord);
    void setY(int rhs_y_coord);
    bool operator==(const Point &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Point &point);

  private:
    int x_coord{0};
    int y_coord{0};
};

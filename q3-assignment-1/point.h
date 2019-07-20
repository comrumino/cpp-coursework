#pragma once
#include <iostream>

class Point {
  public:
    Point(); // default ctor

    Point(int x, int y); // direct ctor

    Point(const Point &other); // copy ctor

    Point(Point &&other); // move ctor

    ~Point();
    int getX() const;
    int getY() const;
    void setX(int rhs_x_coord);
    void setY(int rhs_y_coord);
    Point &operator=(const Point &rhs);
    bool operator==(const Point &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Point &point);

  private:
    int x_coord{0};
    int y_coord{0};
};

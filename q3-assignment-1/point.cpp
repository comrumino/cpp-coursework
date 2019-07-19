#include "point.h"
#include <iostream>
Point::Point() { std::cout << "Point Default Ctor " << myX << "," << myY << std::endl; }
Point::Point(int x, int y) : myX{ x }, myY{ y }
 {
  std::cout << "Point arg Ctor" << myX << "," << myY << std::endl;
 }

Point::Point(const Point& other) : myX{ other.myX }, myY{ other.myY }
 { std::cout << "Point Copy Ctor " << myX << "," << myY << std::endl; }

Point::Point(Point &&other) { std::cout << "Point Move Ctor " << myX << "," << myY << std::endl; }

Point::~Point() { std::cout << "Point Dtor" << std::endl; }

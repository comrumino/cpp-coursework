#pragma once
#include <iostream>
class Point
{
public:

 Point();

 Point(int x, int y);

 Point(const Point& other);

 Point(Point &&other);

 ~Point();
 
private:
 int myX{ 0 };
 int myY{ 0 };
};

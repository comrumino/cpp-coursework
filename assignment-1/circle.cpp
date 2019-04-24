#include "circle.h"
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

// Extra Credit (1pt): use this preprocessor token to enable either assignment
Circle::Circle(int radius, int xCoord, int yCoord, const char *name)
    : mRadius(radius), mXCoord(xCoord), mYCoord(yCoord) {
  SetName(name);
}
Circle::Circle(const Circle &other)
    : mRadius(other.GetRadius()), mXCoord(other.GetX()), mYCoord(other.GetY()) {
  SetName(other.GetName());
}
Circle::~Circle() {
  if (mName != nullptr)
    delete[] mName;
}

#ifdef SWAP_SEMANTICS
// assignment pass by value to create a copy
Circle &Circle::operator=(Circle other) {
  SetName(other.GetName()); // shallow copy of character buffer
  mRadius = other.GetRadius();
  mXCoord = other.GetX();
  mYCoord = other.GetY();
  return *this;
}
#else
// this is another way to overload assignment by reference instead
Circle &Circle::operator=(const Circle &other) {
  mName = other.GetName(); // shallow copy of character buffer
  mRadius = other.GetRadius();
  mXCoord = other.GetX();
  mYCoord = other.GetY();
  return *this;
}
#endif

Circle &Circle::operator++() {
  ++mRadius;
  return *this;
}

Circle Circle::operator++(int) {
  Circle nCircle = *this;
  ++*this;
  return nCircle;
}

Circle Circle::operator+(const Circle &other) const {
  auto name = new char[MaxNameSize];
  strncpy(name, GetName(), MaxNameSize);
  strncat(name, "_PLUS_", MaxNameSize);
  strncat(name, other.GetName(), MaxNameSize);
  Circle nCirc(GetRadius() + other.GetRadius(), GetX(), GetY(), name);
  delete[] name;
  return nCirc;
}

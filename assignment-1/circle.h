#pragma once
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

// Extra Credit (1pt): use this preprocessor token to enable either assignment
// overload
#define SWAP_SEMANTICS

class Circle {
public:
  Circle(int radius, int xCoord = 0, int yCoord = 0,
         const char *name = nullptr);
  Circle(const Circle &other);
  ~Circle() = default;

#ifdef SWAP_SEMANTICS
  Circle &operator=(Circle other);
#else
  Circle &operator=(const Circle &other);
#endif

  Circle operator+(const Circle &other) const;
  Circle &operator++();   // pre increment
  Circle operator++(int); // post increment with a dummy int argument

  const char *GetName() const;
  void SetName(const char *name);
  int GetRadius() const;
  int GetX() const;
  int GetY() const;
  void swap(Circle &other);

private:
  int mXCoord;
  int mYCoord;
  int mRadius;
  const char *mName;
};

inline const char *Circle::GetName() const { return mName; }

inline void Circle::SetName(const char *name) {
  if (name != nullptr)
    mName = name;
}

inline int Circle::GetRadius() const { return mRadius; }

inline int Circle::GetX() const { return mXCoord; }

inline int Circle::GetY() const { return mYCoord; }

inline ostream &operator<<(ostream &os, const Circle &c) {
  os << c.GetName() << endl;
  os << " radius: " << c.GetRadius() << endl;
  os << " x: " << c.GetX() << endl;
  os << " y: " << c.GetY() << endl;
  return os;
}
/*
#ifndef SWAP_SEMANTICS
// assignment pass by value to create a copy
Circle &Circle::operator=(Circle other);
#else
// this is another way to overload assignment by reference instead
Circle &Circle::operator=(const Circle &other);
#endif

Circle &Circle::operator++();

Circle Circle::operator++(int);

Circle Circle::operator+(const Circle &other) const;*/

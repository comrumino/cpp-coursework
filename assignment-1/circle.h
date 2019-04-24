#pragma once
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

// Extra Credit (1pt): use this preprocessor token to enable either assignment overload
#define SWAP_SEMANTICS

class Circle{
  public:
  Circle(int radius, int xCoord=0, int yCoord=0, const char * name=nullptr);
  Circle(const Circle & other);
 ~Circle();
 
 Circle& operator=(Circle other);
 Circle& operator=(const Circle & other);
 
  Circle  operator + ( const Circle & other ) const;
  Circle& operator ++ ();       // pre increment
  Circle  operator ++ ( int );  // post increment with a dummy int argument

 const char * GetName() const;
 void SetName(const char * name);
 int GetRadius() const;
 int GetX() const;
 int GetY() const;
  void   swap( Circle & other );


private:
 int    mXCoord;
 int    mYCoord;
 int    mRadius;
 char * mName;
};

inline const char * Circle::GetName() const;

inline void Circle::SetName(const char * name);

inline int Circle::GetRadius() const;

inline int Circle::GetX() const;

inline int Circle::GetY() const;

Circle::Circle( int radius, int xCoord, int yCoord, const char * name );

Circle::Circle( const Circle & other );

Circle::~Circle();

ostream & operator << ( ostream & os, const Circle & c );

#ifdef SWAP_SEMANTICS
// assignment pass by value to create a copy
Circle & Circle::operator = ( Circle other );
#else
// this is another way to overload assignment by reference instead
Circle & Circle::operator = ( const Circle & other );
#endif

Circle& Circle::operator ++( );

Circle Circle::operator ++( int );

Circle Circle::operator +( const Circle & other ) const;

#include <iostream>
#include <cstring>
#include <algorithm>
#include "circle.h"
using namespace std;

// Extra Credit (1pt): use this preprocessor token to enable either assignment overload


// assignment pass by value to create a copy
Circle & Circle::operator = ( Circle other )
{
  // empty
}

// this is another way to overload assignment by reference instead
Circle & Circle::operator = ( const Circle & other )
{
  // empty
}

Circle& Circle::operator ++( )
{
  // empty
}

Circle Circle::operator ++( int )
{
  // empty
}

Circle Circle::operator +( const Circle & other ) const
{
  // empty    
}

// Please do not modify anything below this line.
const int kMaxNameSize = 128;

// 1) Write an output overload (2pt)
void outputTest(){
  Circle c1(2, 1, 1, "MyCircle");
  cout << "Expected:" << endl;
  cout << "MyCircle" << endl;
  cout << " radius: 2" << endl;
  cout << " x: 1" << endl;
  cout << " y: 1" << endl;
  cout << "Actual:" << endl;
  cout << c1;
}

// 2) Write a robust constructor (2pt)
void constructorTest(){
  char * name = new char [kMaxNameSize];
  const char * kName1 = "Circle1";
  const char * kName2 = "Circle2";

  strncpy(name, kName1, kMaxNameSize); 
  Circle c1( 1, 2, 3, name );

  strncpy(name, kName2, kMaxNameSize); 
  Circle c2( 4, 5, 6, name );

  cout << "c1 is:" << endl << c1 << endl;
  cout << "c2 is:" << endl << c2 << endl;

  delete [] name;
}

// 3) Write an assignment overload (2pt)
void assignmentTest(){
  Circle c1( 1, 2, 3, "Circle1" );
  Circle c2 = c1;
  
  const char * name = "Circle2";
  c1.SetName(name);
  
  cout << "c1 is " << c1 << endl;
  cout << "c2 is " << c2 << endl;
}

// 4) Write an increment overload (2pt)
void incrementTest(){
  Circle c1( 1, 2, 3, "MyCircle" );
  
  c1++;

  cout << "After increment, c1 is " << c1 << endl;
}

// 5) Write an addition overload (2pt)
void additionTest(){
  Circle c1( 1, 2, 3, "Circle1" );
  Circle c2( 4, 5, 6, "Circle2" );
  cout << "c1 before addition is " << c1 << endl;
  cout << "c2 before addition is " << c2 << endl;
  
  c1 = c1 + c2;
  cout << "c1 after c1 = c1 + c2 is " << c1 << endl;
}

/* 
 * Use the Circle class given as a starting point. You will need to implement the constructor and destructor and any other methods that you add (2pts).
 * Add the following operators to the Circle class (each worth 2pts): 
 * Operator << (output operator) 2pts: This should be able to output a circle to an output stream (cout or a file stream).
 * Example:
 *  cout << c1 << endl;
 * MyCircle
 *  radius: 2
 *  x: 1
 *  y: 1
 * Assignment operator :
 *  Assume your assignment operator must ensure that the assigned circle does not share a pointer to the same resources as the rvalue.
 * Operator + :
 *  This should add two circles, which means create a new circle that has a radius which is the sum of the radius of the operands.
 *  Concatenate the two names of the circles with "<first circle>_PLUS_<second circle>". Example: c3 = c1 + c2;
 * Operator ++ (both post and pre increment):
 *  This will increment the radius by one, and return the Circle object (by reference in case of pre increment, and by value in case of post increment).
 *  Example: c1++ or ++c1 increments the radius of circle c1 by 1 unit.
 * Extra Credit (1pt):
 *  Implement both overloads for the assignment operator. One which functions by value passing and the other by reference. For credit,
 *  I must be able to comment out line 7 and still have all green tests!
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;


int main() {
  int input;
  bool done = false;
  while (!done)
  {
    cout << "Enter test number :" << endl;
    cin >> input;
    switch(input){
      case 1:
        outputTest();
        break;
      case 2:
        constructorTest();
        break;
      case 3:
        assignmentTest();
        break;
      case 4:
        incrementTest();
        break;
      case 5:
        additionTest();
        break;
      default:
        done = true;
        break;
    }
  }
}

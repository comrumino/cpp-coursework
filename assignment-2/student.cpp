#include "student.h"
#include <iostream>
#include <string>
using namespace std;

Student::Student(const string &fName, const string &lName, int id) : mFirstName(fName), mLastName(lName), mID(id) {}

const string &Student::GetLastName() const { return mLastName; }

const string &Student::GetFirstName() const { return mFirstName; }

int Student::GetId() const { return mID; }

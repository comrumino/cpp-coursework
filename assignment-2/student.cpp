#include "student.h"
#include <string>
#include <iostream>
using namespace std;


Student::Student(const string& fName, const string& lName, int id)
    :mFirstName(fName), mLastName(lName), mID(id)
{
    std::cout << "Ctor: " << mFirstName << std::endl;
}

Student::~Student()
{
    std::cout << "Dtor: " << mFirstName << std::endl;
}

const string& Student::GetLastName() const
{
    return mLastName;
}


const string& Student::GetFirstName() const
{
    return mFirstName;
}


int Student::GetId() const
{
    return mID;
}

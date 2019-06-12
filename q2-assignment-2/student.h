#pragma once
#include <string>
using namespace std;

class Student {
  public:
    Student(const string &fName = "", const string &lName = "", int id = -1);
    ~Student() = default; // trivial class so this is okay
    const string &GetLastName() const;
    const string &GetFirstName() const;
    int GetId() const;

  private:
    std::string mFirstName;
    std::string mLastName;
    int mID;
};

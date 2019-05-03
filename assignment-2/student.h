#ifndef __STUDENT_H__
#define __STUDENT_H__
#include <string>
using namespace std;

class Student {
  public:
    Student(const string &fName = "", const string &lName = "", int id = -1);

    ~Student();
    const string &GetLastName() const;
    const string &GetFirstName() const;
    int GetId() const;

  private:
    std::string mFirstName;
    std::string mLastName;
    int mID;
};

#endif

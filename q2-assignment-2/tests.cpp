#include "tests.h"
#include "student.h"
#include <string>

using namespace std;

string Tests::CreateStudent() {
    string fName, lName;
    fName = "John";
    lName = "Doe";

    Student student(fName, lName, 123);

    if (student.GetFirstName() == fName)
        return "CreateStudent() passed";

    return "CreateStudent() failed";
}

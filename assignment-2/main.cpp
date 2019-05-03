#include "TestHarness.h"
#include "studentprocessor.h"
#include "tests.h"
#include <iostream>
using namespace std;

int DoAssignment();

int DoAssignment() {
    int status = 0;

    StudentProcessor sp;
    TCollStudents rawCollStudents;
    if (sp.LoadStudents("/home/archie/repo/cprogrm712/assignment-2/studentinfo.txt", rawCollStudents)) {
        auto stdn = *rawCollStudents.back();
        sp.ProcessStudents(rawCollStudents);
        auto coll = *sp.mCCStudents.back();
        stdn = *coll.back();

        sp.PrintStudents(std::cout);
    } else {
        // normally would print or return a specific status code
        status = -1;
    }
    return status;
}

TEST(Main, MainTest) {
    Tests t;
    cout << t.CreateStudent() << endl;

    cout << endl << "Complete results:" << endl;
    CHECK_EQUAL(DoAssignment(), 0);
}

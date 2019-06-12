#include "TestHarness.h"
#include "studentprocessor.h"
#include "tests.h"
#include <fstream>
#include <iostream>

using namespace std;

int DoAssignment();

int DoAssignment() {
    int status = 0;

    StudentProcessor sp;
    TCollStudents rawCollStudents;
    // try to load, then process so output is ready. otherwise, return -1
    if (sp.LoadStudents("/home/archie/repo/cprogrm712/assignment-2/studentinfo.txt", rawCollStudents)) {
        auto stdn = *rawCollStudents.back();
        sp.ProcessStudents(rawCollStudents);
        auto coll = *sp.mCCStudents.back();
        stdn = *coll.back();
        // output
        std::ofstream a2out;
        a2out.open("A2Out.txt", std::ofstream::out | std::ofstream::trunc);
        sp.PrintStudents(a2out);
        a2out.close();
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

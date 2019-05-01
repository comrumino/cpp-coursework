#include "studentprocessor.h"
#include "tests.h"
#include "TestHarness.h"
#include <iostream>
using namespace std;

int DoAssignment();

int DoAssignment()
{
	int status = 0;

	StudentProcessor	sp;
	TCollStudents	rawCollStudents;
	if ( sp.LoadStudents( "/home/archie/repo/cprogrm712/assignment-2/studentinfo.txt", rawCollStudents ) )
	{
        auto stdn = *rawCollStudents.back();
        std::cout << "test 1 " << stdn.GetFirstName() << std::endl;
		sp.ProcessStudents( rawCollStudents );
        auto coll = *sp.mCCStudents.back();
        stdn = *coll.back();

        std::cout << "test 2 " << stdn.GetFirstName() << std::endl;
		sp.PrintStudents( std::cout );
	}
	else
	{
    // normally would print or return a specific status code
		status = -1;
	}
	return status;
}

TEST(Main, MainTest)
{
  Tests t;
  cout << t.CreateStudent() << endl;

  cout << endl << "Complete results:" << endl;
   CHECK_EQUAL(DoAssignment(), 0);
}

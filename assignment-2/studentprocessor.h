#ifndef __STUDENT_PROCESSOR_H__
#define __STUDENT_PROCESSOR_H__

#include <ostream>
#include <string>
#include <vector>
#include <map>

#include "types.h"
#include "student.h"

class StudentProcessor
{
public:
	StudentProcessor();
	~StudentProcessor() = default;

	bool LoadStudents( const std::string & inputFile, TCollStudents & rawCollStudents );
	void ProcessStudents( const TCollStudents & rawCollStudents );
	void PrintStudents( std::ostream & os ) const;

	TCollCollStudents	mCCStudents;
	
private:

	void PrintStudents( std::ostream & os, const TCollStudents & cStudents ) const;
	void PrintStudents( std::ostream & os, const TCollCollStudents & ccStudents ) const;

	void DeleteElements( TCollStudents * collPtr );

    std::map<char, TCollStudents> mymap;
    std::vector<Student> all_students;
};

inline StudentProcessor::StudentProcessor()
{
    all_students.reserve(1024);
};

#endif

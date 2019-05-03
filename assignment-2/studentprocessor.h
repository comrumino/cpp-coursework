#ifndef __STUDENT_PROCESSOR_H__
#define __STUDENT_PROCESSOR_H__

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "student.h"
#include "types.h"

class StudentProcessor {
  public:
    StudentProcessor();
    ~StudentProcessor() = default;

    bool LoadStudents(const std::string &inputFile, TCollStudents &rawCollStudents);
    void ProcessStudents(const TCollStudents &rawCollStudents);
    void PrintStudents(std::ostream &os) const;

    TCollCollStudents mCCStudents;

  private:
    void PrintStudents(std::ostream &os, const TCollStudents &cStudents) const;
    void PrintStudents(std::ostream &os, const TCollCollStudents &ccStudents) const;

    void DeleteElements(TCollStudents *collPtr);

    std::map<char, TCollStudents> smap;
    std::vector<Student> all_students;
};

inline StudentProcessor::StudentProcessor() { all_students.reserve(1024); };

#endif

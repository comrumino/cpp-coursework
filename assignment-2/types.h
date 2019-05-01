#ifndef __TYPES_H__
#define __TYPES_H__

#include <vector>
#include "student.h"

// collection of student object pointers
typedef std::vector<Student*> TCollStudents;

// collection of collection of student object pointers
typedef std::vector<TCollStudents*> TCollCollStudents;

#endif

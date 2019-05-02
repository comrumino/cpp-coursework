#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <typeinfo>
#include "studentprocessor.h"
#include "student.h"

using namespace std;

bool StudentProcessor::LoadStudents( const std::string & inputFile, TCollStudents & rawCollStudents )
{
    ifstream input(inputFile); 
    bool success = false;
    if (input) {
        std::string fcontent((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
        std::string finfo;
        std::string id;
        std::string fn;
        std::string ln;
        int fcf;
        int iid = -1;
        Student student;
        while (fcontent != "") {
            std::cout << "fuck dis 1" << std::endl;
            fcf = fcontent.find(";");
            if (fcf != -1) {
                finfo = fcontent.substr(0, fcf);
                fcontent = fcontent.substr(fcf + 1, std::string::npos);
            } else {
                finfo = fcontent;
                fcontent = "";
            }
            //
            fcf = finfo.find(",");
            if (fcf != -1) {
                fcf = finfo.find(",");
                id = finfo.substr(0, fcf);
                finfo = finfo.substr(fcf + 1, std::string::npos);
                id = id.substr(id.find_first_not_of(" "), id.find_last_not_of(" ") + 1);
            } else {
                id = "-1";
                std::cerr << "Student " << finfo << " did not have an ID" << std::endl;
            }
            //
            finfo = finfo.substr(finfo.find_first_not_of(" "), finfo.find_last_not_of(" ") + 1);  // trim
            if (finfo.find(" ") == -1 || finfo.find(",") != -1) {  // if after trimming, there is no whitespace skip input
                continue;
            }
            fcf = finfo.find_first_of(" ");
            fn = finfo.substr(0, fcf);
            finfo = finfo.substr(fcf + 1, std::string::npos);
            ln = finfo.substr(finfo.find_first_not_of(" "), finfo.find_last_not_of(" ") + 1);
            std::sscanf(id.c_str(), "%i", &iid);
            //
            all_students.push_back(Student(fn, ln, iid));
            rawCollStudents.push_back(&all_students.back()); // switch cast to scan
        }
        success = true;
    }
    input.close();
    return success;
}

void StudentProcessor::ProcessStudents( const TCollStudents & rawCollStudents )
{
    for (auto ms : rawCollStudents)
        mymap[ms->GetFirstName()[0]].push_back(ms);
    for (std::map<char, TCollStudents>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        mCCStudents.push_back(&(it->second));
}

void StudentProcessor::PrintStudents( std::ostream & os ) const
{
    PrintStudents(os, mCCStudents);
}

void StudentProcessor::PrintStudents( std::ostream & os, const TCollStudents & cStudents ) const
{
    for (auto student : cStudents) {
        os << "    " << student->GetFirstName() << " " << student->GetLastName() << " " << student->GetId() << endl;
    }
}

void StudentProcessor::PrintStudents( std::ostream & os, const TCollCollStudents & ccStudents ) const
{
    int i = 0;
    for (auto mCStudents : ccStudents) {
        os << "Collection " << i++ << ":" << std::endl;
        PrintStudents(os, *mCStudents);
    }
}

void StudentProcessor::DeleteElements( TCollStudents * collPtr )
{
    for (auto student : *collPtr) {
        auto mc = student->GetFirstName()[0];
        mymap[mc].erase(std::remove(mymap[mc].begin(), mymap[mc].end(), student), mymap[mc].end());
    }
}


// TCollCollStudents	mCCStudents

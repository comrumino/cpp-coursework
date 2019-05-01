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
            std::cout << "a" << std::endl;
            all_students.push_back(Student(fn, ln, iid));
            std::cout << "b" << std::endl;
            rawCollStudents.push_back(&all_students.back()); // switch cast to scan
            std::cout << "c" << std::endl;
            std::cout << "fuck dis 2" << std::endl;
        }
        success = true;
    }
    std::cout << "fuck dis 3" << std::endl;
    input.close();
    std::cout << "fuck dis 4" << std::endl;
    return success;
}

void StudentProcessor::ProcessStudents( const TCollStudents & rawCollStudents )
{
    for (auto ms : rawCollStudents) {
        std::cout << "FN " <<  ms->GetFirstName()[0] << std::endl;
        mymap[ms->GetFirstName()[0]].push_back(ms);
    }
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
        std::cout << "FUCK LOOP2" << std::endl;
        std::cout << "FUCK LOOP2 BACK" << student->GetFirstName() << std::endl;
        os << student->GetFirstName() << " " << student->GetLastName() << " " << student->GetId() << std::endl;
    }
}

void StudentProcessor::PrintStudents( std::ostream & os, const TCollCollStudents & ccStudents ) const
{
    for (auto mCStudents : ccStudents) {
        std::cout << "FUCK LOOP" << std::endl;
        std::cout << "FUCK LOOP BACK" << mCStudents->back() << std::endl;
        PrintStudents(os, *mCStudents);
    }
}

void DeleteElements( TCollStudents * collPtr )
{
}


// TCollCollStudents	mCCStudents

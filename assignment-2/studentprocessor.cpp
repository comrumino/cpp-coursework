#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
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
        while (fcontent != "") {
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
            std::cout << "id " << id << std::endl;
            std::cout << "fn " << fn << std::endl;
            std::cout << "ln " << ln << std::endl << std::endl;
        }
        success = true;
    }
    input.close();
    return success;
}

void StudentProcessor::ProcessStudents( const TCollStudents & rawCollStudents )
{

}

void StudentProcessor::PrintStudents( std::ostream & os ) const
{
}

void StudentProcessor::PrintStudents( std::ostream & os, const TCollStudents & cStudents ) const
{
}

void StudentProcessor::PrintStudents( std::ostream & os, const TCollCollStudents & ccStudents ) const
{
}

void DeleteElements( TCollStudents * collPtr )
{
}


// TCollCollStudents	mCCStudents

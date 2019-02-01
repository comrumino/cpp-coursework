/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 2.2
 *  Problem Statement:
 *   + Define a table of the names of months of the year and the number of days in each month.
 *   + Write out that table to a stringstream.
 *   + Do this twice; once using an array of char for the names and an array for the number of days and
 *     a second time using an array of structures, with each structure holding the name of a month and
 *     the number of days in it.
 */
#include <iostream>
#include <string>
#include <memory>

const int NUM_MONTHS = 12;
struct MonthDays
{
    std::string month;
    int days;
};

int main()
{
    std::unique_ptr<std::string[]> arr_months(new std::string[NUM_MONTHS]{"January", "February", "March",
                                                                        "April", "May", "June", "July",
                                                                        "August", "September", "October",
                                                                        "November", "December"});
    std::unique_ptr<int[]> arr_days(new int[NUM_MONTHS]{31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
    auto arr_monthdays = std::make_unique<MonthDays[]>(NUM_MONTHS);
    //std::unique_ptr<void*> arr_table(new void**[2]{months, mdays});
    for (long unsigned int i = 0; i < NUM_MONTHS; ++i) {
        MonthDays ith_md;
        ith_md.month = arr_months[i];
        ith_md.days = arr_days[i];
        std::cout << ith_md.month << " " << ith_md.days << std::endl;
        arr_monthdays[i] = ith_md;
    }
    return 0;
}

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
#include "jstronz-2-2.h"

const int NUM_MONTHS = 12;
const std::unique_ptr<std::string[]> arr_months(new std::string[NUM_MONTHS]{"January", "February", "March",
                                                                            "April", "May", "June", "July",
                                                                            "August", "September", "October",
                                                                            "November", "December"});
const std::unique_ptr<int[]> arr_days(new int[NUM_MONTHS]{31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
struct MonthDays
{
    std::string month;
    int days;
};

void write_table(std::ostream& os)
{
    for (long unsigned int i = 0; i < NUM_MONTHS; ++i) {
        os << arr_months[i] << " " << arr_days[i] << " ";
    }
}

void populate_monthdays(std::unique_ptr<MonthDays[]>& monthdays)
{
    for (long unsigned int i = 0; i < NUM_MONTHS; ++i) {
        MonthDays ith_md;
        ith_md.month = arr_months[i];
        ith_md.days = arr_days[i];
        monthdays[i] = ith_md;
    }
}

void write_array(std::ostream& os)
{
    auto arr_monthdays = std::make_unique<MonthDays[]>(NUM_MONTHS);
    populate_monthdays(arr_monthdays);
    // populate arr_monthdays with data
    for (long unsigned int i = 0; i < NUM_MONTHS; ++i) {
        auto ith_md = arr_monthdays[i];
        os << ith_md.month << " " << ith_md.days << " ";
    }
}

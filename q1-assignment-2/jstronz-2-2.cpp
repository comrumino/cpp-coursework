#include "jstronz-2-2.h"
#include <iostream>
#include <memory>
#include <string>

const int NUM_MONTHS = 12;
const std::unique_ptr<std::string[]> arr_months(new std::string[NUM_MONTHS]{
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November",
    "December"});
const std::unique_ptr<int[]> arr_days(new int[NUM_MONTHS]{31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
struct MonthDays {
    std::string month;
    int days;
};

void write_table(std::ostream &os) {
    for (long unsigned int i = 0; i < NUM_MONTHS; ++i) {
        os << arr_months[i] << " " << arr_days[i] << " ";
    }
}

void populate_monthdays(std::unique_ptr<MonthDays[]> &monthdays) {
    for (long unsigned int i = 0; i < NUM_MONTHS; ++i) {
        MonthDays ith_md;
        ith_md.month = arr_months[i];
        ith_md.days = arr_days[i];
        monthdays[i] = ith_md;
    }
}

void write_array(std::ostream &os) {
    auto arr_monthdays = std::make_unique<MonthDays[]>(NUM_MONTHS);
    populate_monthdays(arr_monthdays);
    // populate arr_monthdays with data
    for (long unsigned int i = 0; i < NUM_MONTHS; ++i) {
        auto ith_md = arr_monthdays[i];
        os << ith_md.month << " " << ith_md.days << " ";
    }
}

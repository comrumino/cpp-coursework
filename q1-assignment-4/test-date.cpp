#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include "TestHarness.h"
#include "jstronz-4-1.h"

TEST(DateTest, add_day)
{
    Date date;
    
    std::stringstream ymd;
    ymd << date.year << date.month << date.day;
    CHECK_EQUAL("000", ymd.str());
    ymd.str("");
    add_day(date);
    ymd << date.year << date.month << date.day;
    CHECK_EQUAL("001", ymd.str());
}

TEST(DateTest, add_month)
{
    Date date;

    std::stringstream ymd;
    ymd << date.year << date.month << date.day;
    CHECK_EQUAL("000", ymd.str());
    ymd.str("");
    add_month(date);
    ymd << date.year << date.month << date.day;
    CHECK_EQUAL("010", ymd.str());
}

TEST(DateTest, add_year)
{
    Date date;

    std::stringstream ymd;
    ymd << date.year << date.month << date.day;
    CHECK_EQUAL("000", ymd.str());
    ymd.str("");
    add_year(date);
    ymd << date.year << date.month << date.day;
    CHECK_EQUAL("100", ymd.str());
}

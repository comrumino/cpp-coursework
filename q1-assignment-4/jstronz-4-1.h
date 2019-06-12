#pragma once

struct Date
{
    int year = 0;
    int month = 0;
    int day = 0;
};

void add_day(Date& date);

void add_month(Date& date);

void add_year(Date& date);

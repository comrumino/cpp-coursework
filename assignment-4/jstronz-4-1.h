/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 4.1
 *  Problem Statement:
 *   Write functions to add one day, another function to add one month, and yet another function to add one year
 *   to a Date struct.
 *   | struct Date
 *   | {
 *   |     int year;
 *   |     int month;
 *   |     int day;
 *   | };
 *   Pass Dates by reference when appropriate (i.e., Date& or const Date&). For example, the following function
 *   returns by value a new Date instance with one day added to the passed in date.
 *   
 *   | Date addOneDay(const Date& date);
 */
#ifndef JSTRONZ_4_1_H
#define JSTRONZ_4_1_H
struct Date
{
    int year = 0;
    int month = 0;
    int day = 0;
};

void add_day(Date& date);

void add_month(Date& date);

void add_year(Date& date);
#endif

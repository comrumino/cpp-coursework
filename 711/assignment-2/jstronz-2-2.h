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
#include <sstream>
#ifndef JSTRONZ_2_2_H
#define JSTRONZ_2_2_H
void write_table(std::ostream& os);

void write_array(std::ostream& os);
#endif

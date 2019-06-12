#include "TestHarness.h"
#include "jstronz-2-2.h"
#include <sstream>

const std::string expected_monthdays("January 31 February 30 March 31 April 30 May 31 June 30 "
                                     "July 31 August 31 September 30 October 31 November 30 December 31 ");

TEST(MonthDaysTest, write_table) {
    std::stringstream os;
    write_table(os);
    CHECK_EQUAL(expected_monthdays, os.str());
}

TEST(MonthDaysTest, write_array) {
    std::stringstream os;
    write_array(os);
    CHECK_EQUAL(expected_monthdays, os.str());
}

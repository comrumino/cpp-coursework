#include "constraint_satisfaction.h"
#include <string>
#include <vector>
#include <iostream>


Expiration::Expiration(std::string date)
    :date(date)
{
}

const bool Expiration::is_valid_format() const {
    // is suffices to verify the following conditions:
    // + year is in yyyy format such that yyyy is 0 < uint
    // + month is mm format such that mm is 0 < uint < 12 + 1
    // + day is dd format such that dd is 0 < uint < 31 + 1
    // even if the day is invalid for a given month the restraints in
    // combination with a check if is_expired would make such a bypass
    // attempt ineffectual. In the game of at and mouse the aim is to
    // make things more difficult---like bruteforcing.
    size_t first = date.find_first_of("-");
    size_t last = date.find_last_of("-");
    std::cout << "string: " << date << std::endl;
    std::cout << "length: " << date.length() << std::endl;
    std::cout << "first: " << first << std::endl;
    std::cout << "last: " << last << std::endl;
    return true;
}

const std::string Expiration::get() const {
    return date;
}

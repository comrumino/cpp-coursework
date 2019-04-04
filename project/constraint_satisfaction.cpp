#include "constraint_satisfaction.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

const bool is_expired(std::string date) {
    // is suffices to verify the following conditions:
    // + year is in yyyy format such that yyyy is 0 < uint
    // + month is mm format such that mm is 0 < uint < 12 + 1
    // + day is dd format such that dd is 0 < uint < 31 + 1
    // even if the day is invalid for a given month the restraints in
    // combination with a check if is_expired would make such a bypass
    // attempt ineffectual. In the game of at and mouse the aim is to
    // make things more difficult---like bruteforcing.
    static const size_t _first = 4;
    static const size_t _last = 7;
    static const size_t _length = 10;
    unsigned int year = 0;
    unsigned int month = 0;
    unsigned int day = 0;
    size_t first = date.find_first_of("-");
    size_t last = date.find_last_of("-");
    // check that dash is in the same spot as the format cccc-cc-cc
    if (date.length() != _length || first != _first || last != _last) {
        return true;
    }
    // use sscanf to check dates are as expected
    std::sscanf(date.c_str(), "%u-%u-%u", &year, &month, &day);
    if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31) {
        return true;
    } else {
        return false;
    }
}

const bool is_product(std::string product_type) {
    if (product.nplive == product_type || product.npview == product_type)
        return true;
    else
        return false;
}

const bool is_license(std::string license_type) {
    if (license.evaluation == license_type)
        return true;
    else if (license.enterprise == license_type)
        return true;
    else if (license.consultant == license_type)
        return true;
    else if (license.auditor == license_type)
        return true;
    else if (license.developer == license_type)
        return true;
    else
        return false;
}

const bool is_users(std::string users) {
    unsigned int usrs = 0;
    std::sscanf(users.c_str(), "%u", &usrs);
    if (0 < usrs && usrs < 65536) {
        return true;
    } else {
        return false;
    }
}

const bool is_rulesets(std::string rulesets) {
    unsigned int rlsts = 0;
    std::sscanf(rulesets.c_str(), "%u", &rlsts);
    if (0 < rlsts && rlsts < 65536) {
        return true;
    } else {
        return false;
    }
}

const bool is_devices(std::string devices) {
    unsigned int dvcs = 0;
    std::sscanf(devices.c_str(), "%u", &dvcs);
    if (0 < dvcs && dvcs < 65536) {
        return true;
    } else {
        return false;
    }
}

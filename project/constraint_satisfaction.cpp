#include "constraint_satisfaction.h"
#include <string>


Expiration::Expiration(std::string date)
    :date(date)
{
}

const bool Expiration::is_valid_format() const {
    return true;
}

const std::string Expiration::get() const {
    return date;
}

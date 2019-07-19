#include "TestHarness.h"
#include "parse.h"
#include <string>
#include <sstream>
#include <iostream>

TEST(trim, trim) {
    const std::string trimmables("\"");
    std::string quoted_value("\"value\"");
    trim(quoted_value, trimmables);
    CHECK_EQUAL("value", quoted_value);
}
TEST(eat, eat_padded_1) {
    const std::string edible(" \t\n");
    std::istringstream padded_string("  string \t\n ");
    std::ostringstream actual;
    eat(padded_string, edible);
    actual << padded_string.rdbuf();
    CHECK_EQUAL("string \t\n ", actual.str());
}

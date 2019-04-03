#include "TestHarness.h"
#include "constraint_satisfaction.h"
#include <iostream>
#include <string>

TEST(ConstraintSatisfaction, product_license) {
    CHECK_EQUAL(product.nplive, "NP-Live");
    CHECK_EQUAL(product.npview, "NP-View");
    CHECK_EQUAL(license.evaluation, "Evaluation License");
    CHECK_EQUAL(license.enterprise, "Enterprise License");
    CHECK_EQUAL(license.consultant, "Consultant License");
    CHECK_EQUAL(license.auditor, "Auditor License");
    CHECK_EQUAL(license.developer, "Developer License");
}

TEST(ConstraintSatisfaction, expiration_verifaction) {
    Expiration exp_valid("2019-04-01");
    CHECK_EQUAL(exp_valid.is_valid_format(), true);
    std::vector<std::string> invalid_test_cases {"", "yyyy-mm-dd", "--",  // absurd inputs
                                                 "2019-00-01", "2019-01-00",  // lower bound tests
                                                 "2019-13-00", "2019-01-32"};  // upper bound tests
    for (auto invalid : invalid_test_cases) {
        Expiration exp_invalid(invalid);
        CHECK_EQUAL(exp_invalid.is_valid_format(), false);
    }
}

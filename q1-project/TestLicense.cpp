#include "TestHarness.h"
#include "constraint_satisfaction.h"
#include "license.h"
#include <iostream>
#include <string>

TEST(ConstraintSatisfaction, product_license) {
    // avoid a typo or two
    CHECK_EQUAL("NP-Live", product.nplive);
    CHECK_EQUAL("NP-View", product.npview);
    CHECK_EQUAL("Evaluation License", license.evaluation);
    CHECK_EQUAL("Enterprise License", license.enterprise);
    CHECK_EQUAL("Consultant License", license.consultant);
    CHECK_EQUAL("Auditor License", license.auditor);
    CHECK_EQUAL("Developer License", license.developer);
}

TEST(ConstraintSatisfaction, is_expired) {
    CHECK_EQUAL(false, is_expired("9119-04-01"));
    std::vector<std::string> expired_test_cases{"",           "yyyy-mm-dd", "--", // absurd inputs
                                                "2019-00-01", "2019-01-00",       // lower bound tests
                                                "2019-13-00", "2019-01-32"};      // upper bound tests
    for (auto invalid : expired_test_cases) {
        CHECK_EQUAL(true, is_expired(invalid));
    }
}

TEST(ConstraintSatisfaction, is_product) {
    CHECK_EQUAL(false, is_product(product.nplive + "-"));
    CHECK_EQUAL(false, is_product("-" + product.nplive));
    CHECK_EQUAL(false, is_product(""));
    std::vector<std::string> product_test_cases{product.nplive, product.npview};
    for (auto valid : product_test_cases) {
        CHECK_EQUAL(true, is_product(valid));
    }
}

TEST(ConstraintSatisfaction, is_license) {
    CHECK_EQUAL(false, is_license(license.evaluation + "-"));
    CHECK_EQUAL(false, is_license("-" + license.evaluation));
    CHECK_EQUAL(false, is_license(""));
    std::vector<std::string> license_test_cases{license.evaluation, license.enterprise, license.consultant,
                                                license.auditor,    license.auditor,    license.developer};
    for (auto valid : license_test_cases) {
        CHECK_EQUAL(true, is_license(valid));
    }
}

TEST(ConstraintSatisfaction, is_users_rulesets_devices) {
    std::vector<unsigned int> invalid_test_cases{0, 65536};
    std::vector<unsigned int> valid_test_cases{1, 2, 65535};
    // users
    for (auto invalid : invalid_test_cases) {
        CHECK_EQUAL(false, is_users(invalid));
    }
    for (auto valid : valid_test_cases) {
        CHECK_EQUAL(true, is_users(valid));
    }
    // rulesets
    for (auto invalid : invalid_test_cases) {
        CHECK_EQUAL(false, is_rulesets(invalid));
    }
    for (auto valid : valid_test_cases) {
        CHECK_EQUAL(true, is_rulesets(valid));
    }
    // devices
    for (auto invalid : invalid_test_cases) {
        CHECK_EQUAL(false, is_devices(invalid));
    }
    for (auto valid : valid_test_cases) {
        CHECK_EQUAL(true, is_devices(valid));
    }
}

TEST(License, verifySignature) {
    // std::ifstream privifs("testing/npview_signature_key.pem");
    // std::string privateKey((std::istreambuf_iterator<char>(privifs)), std::istreambuf_iterator<char>());
    //
    std::ifstream pubifs("testing/npview_signature_public_key.pem");
    std::string publicKey((std::istreambuf_iterator<char>(pubifs)), std::istreambuf_iterator<char>());

    std::ifstream licifs("testing/ExampleLicense.txt");
    std::string license((std::istreambuf_iterator<char>(licifs)), std::istreambuf_iterator<char>());

    std::ifstream sigifs("testing/ExampleLicense.sig.base64");
    std::string signature((std::istreambuf_iterator<char>(sigifs)), std::istreambuf_iterator<char>());

    std::cout << license << std::endl;
    bool authentic = verifySignature(publicKey, license, signature);
    if (authentic) {
        std::cout << "Authentic" << std::endl;
    } else {
        std::cout << "Not Authentic" << std::endl;
    }
}

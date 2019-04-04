#pragma once
#include <string>

static const struct Product
{
    const std::string nplive = "NP-Live";
    const std::string npview = "NP-View";
} product;

static const struct License
{
    const std::string evaluation = "Evaluation License";
    const std::string enterprise = "Enterprise License";
    const std::string consultant = "Consultant License";
    const std::string auditor = "Auditor License";
    const std::string developer = "Developer License";
} license;


const bool is_expired(std::string date);

const bool is_product(std::string product_type);

const bool is_license(std::string license_type);

const bool is_users(std::string users);

const bool is_rulesets(std::string rulesets);

const bool is_devices(std::string devices);

class ConstraintSatisfaction
{
public:
    ConstraintSatisfaction() = delete;
    ConstraintSatisfaction(const ConstraintSatisfaction& src) = delete;
    ConstraintSatisfaction& operator=(const ConstraintSatisfaction& rhs) = delete;
    ConstraintSatisfaction(std::string prdct, std::string lcns, std::string exp,
                           std::string usrs, std::string rlsts, std::string devs);
    virtual const bool is_valid() = 0;  // check the license is valid format and verify signature
    virtual const bool is_discretionary() = 0;  // check the license is within limits via datastore
}

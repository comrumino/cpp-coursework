#pragma once
#include <string>

static const struct Product {
    const std::string nplive = "NP-Live";
    const std::string npview = "NP-View";
} product;

static const struct License {
    const std::string evaluation = "Evaluation License";
    const std::string enterprise = "Enterprise License";
    const std::string consultant = "Consultant License";
    const std::string auditor = "Auditor License";
    const std::string developer = "Developer License";
} license;

const bool is_expired(std::string date);

const bool is_product(std::string product_type);

const bool is_license(std::string license_type);

const bool is_users(unsigned int users);

const bool is_rulesets(unsigned int rulesets);

const bool is_devices(unsigned int devices);

class ConstraintSatisfaction {
  public:
    ConstraintSatisfaction() = delete;
    ConstraintSatisfaction(const ConstraintSatisfaction &src) = delete;
    ConstraintSatisfaction &operator=(const ConstraintSatisfaction &rhs) = delete;
    ConstraintSatisfaction(std::string prdct, std::string lcns, std::string exp, std::string usrs = "0",
                           std::string rlsts = "0", std::string devs = "0", const bool signature = false);
    const bool is_valid();                     // check the license is valid format and signature is true/good
    virtual const bool is_discretionary() = 0; // check the license is within limits via datastore
  private:
    const std::string email;
    const std::string product;
    const std::string license;
    const std::string expiration;
    unsigned int users = 0;
    unsigned int rulesets = 0;
    unsigned int devices = 0;
    const bool signature = false;
};

class NPLiveConstraint : ConstraintSatisfaction {
  public:
    NPLiveConstraint() = delete;
    NPLiveConstraint(const ConstraintSatisfaction &src) = delete;
    NPLiveConstraint &operator=(const ConstraintSatisfaction &rhs) = delete;
    NPLiveConstraint(std::string prdct, std::string lcns, std::string exp, std::string usrs = "0",
                     std::string rlsts = "0", std::string devs = "0", const bool signature = false);
    const bool is_discretionary() override; // check the license is within limits via datastore
  private:
    const std::string email;
    const std::string product;
    const std::string license;
    const std::string expiration;
    unsigned int users = 0;
    unsigned int rulesets = 0;
    unsigned int devices = 0;
    const bool signature = false;
};

class NPViewConstraint : ConstraintSatisfaction {
  public:
    NPViewConstraint() = delete;
    NPViewConstraint(const ConstraintSatisfaction &src) = delete;
    NPViewConstraint &operator=(const ConstraintSatisfaction &rhs) = delete;
    NPViewConstraint(std::string prdct, std::string lcns, std::string exp, std::string usrs = "0",
                     std::string rlsts = "0", std::string devs = "0", const bool signature = false);
    const bool is_discretionary() override; // check the license is within limits via datastore
  private:
    const std::string email;
    const std::string product;
    const std::string license;
    const std::string expiration;
    unsigned int users = 0;
    unsigned int rulesets = 0;
    unsigned int devices = 0;
    const bool signature = false;
};

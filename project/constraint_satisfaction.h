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

class Expiration {
public:
    Expiration() = delete;  // disable default constructor
    Expiration(const Expiration& rhs) = delete;  // disable copy constructor
    Expiration& operator=(const Expiration& rhs) = delete;  // disable assignment constructor
    Expiration(std::string date);  // allow direct initialization
    ~Expiration() = default;  // string default destruction safe?
    const bool is_valid_format() const;
    const std::string get() const;
private:
    const std::string date;
};

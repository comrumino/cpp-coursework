#include <sstream>
#include <string>
#include "TestHarness.h"
#include "write.h"
TEST(Write, int)
{
    std::stringstream os;
    write(os, 1);
    CHECK_EQUAL("1", os.str());
    os.str("");
    write(os, -1);
    CHECK_EQUAL("-1", os.str());
}


TEST(Write, float)
{
    std::stringstream os;
    write(os, 1.01f);
    CHECK_EQUAL("1.01", os.str());
    os.str("");
    write(os, -1.101f);
    CHECK_EQUAL("-1.101", os.str());
}

TEST(Write, string)
{
    std::stringstream os;
    const std::string strng("this is a false statement");
    write(os, strng);
    CHECK_EQUAL(strng, os.str());
    os.str("");
    write(os, "");
    CHECK_EQUAL("", os.str());
}

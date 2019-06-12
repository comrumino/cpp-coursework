#include <algorithm>
#include "TestHarness.h"

TEST(lambdaTestProblem, lambdas)
{
    auto values = { 2, 4, 6, 8, 10, 12 };
    auto sum = 0;

    std::for_each(values.begin(), values.end(), [&values, &sum](auto val) -> void
    { 
        sum += val;
    });

    CHECK_EQUAL(42, sum);
}

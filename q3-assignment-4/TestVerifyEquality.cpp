#include "TestHarness.h"
#include "binary.h"
#include <iostream>
/*
 * Big/Little tests
 */
TEST(Word, verifyEqualityLittleEndian) {
    const unsigned char input[]{0xAB, 0xCD, 0};
    std::stringstream ss{reinterpret_cast<const char *>(input)};

    binary::Word actual{binary::Word::readLittleEndian(ss)};
    const binary::Word notReallyExpected{0xABCD};

    try {
        verifyEquality(notReallyExpected, actual, "notReallyExpected");
        CHECK(false);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        CHECK(true);
    }
}

TEST(Word, verifyEqualityBigEndian) {
    const unsigned char input[]{0xAB, 0xCD, 0};
    std::stringstream ss{reinterpret_cast<const char *>(input)};

    binary::Word actual{binary::Word::readBigEndian(ss)};
    const binary::Word notReallyExpected{0xCDAB};

    try {
        verifyEquality(notReallyExpected, actual, "notReallyExpected");
        CHECK(false);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        CHECK(true);
    }
}

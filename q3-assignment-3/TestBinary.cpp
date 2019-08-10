#include "TestHarness.h"
#include "binary.h"
#include "bitmap.h"
#include <sstream>

TEST(Byte, read) {
    std::stringstream ss{"feefiefoefoo"};
    auto b = binary::Byte::read(ss);
    CHECK_EQUAL('f', b);
    b = binary::Byte::read(ss);
    CHECK_EQUAL('e', b);
    b = binary::Byte::read(ss);
    CHECK_EQUAL('e', b);
    b = binary::Byte::read(ss);
    CHECK_EQUAL('f', b);
    b = binary::Byte::read(ss);
    CHECK_EQUAL('i', b);
    b = binary::Byte::read(ss);
    CHECK_EQUAL('e', b);
}
TEST(Word, readLittleEndian) {
    unsigned char carr[]{0x01, 0x02, 0x03, 0x04, 0x00};
    std::stringstream ss{reinterpret_cast<char *>(carr)};
    // check base case
    auto w = binary::Word::readLittleEndian(ss);
    CHECK_EQUAL(0x0201, w);
    binary::Word expected{0x0201};
    CHECK_EQUAL(expected, w);
    // check next step
    w = binary::Word::readLittleEndian(ss);
    CHECK_EQUAL(0x0403, w);
    binary::Word expected2{0x0403};
    CHECK_EQUAL(expected2, w);
}
TEST(Word, readBigEndian) {
    unsigned char carr[]{0x01, 0x02, 0x03, 0x04, 0x00};
    std::stringstream ss{reinterpret_cast<char *>(carr)};
    // check base case
    auto w = binary::Word::readBigEndian(ss);
    CHECK_EQUAL(0x0102, w);
    binary::Word expected{0x0102};
    CHECK_EQUAL(expected, w);
    // check next step
    w = binary::Word::readBigEndian(ss);
    CHECK_EQUAL(0x0304, w);
    binary::Word expected2{0x0304};
    CHECK_EQUAL(expected2, w);
}
TEST(DoubleWord, readLittleEndian) {
    unsigned char carr[]{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x00};
    std::stringstream ss{reinterpret_cast<char *>(carr)};
    // check base case
    auto dw = binary::DoubleWord::readLittleEndian(ss);
    CHECK_EQUAL(0x04030201, dw);
    binary::DoubleWord expected(0x04030201);
    CHECK_EQUAL(expected, dw);
    // check next step
    dw = binary::DoubleWord::readLittleEndian(ss);
    CHECK_EQUAL(0x08070605, dw);
    binary::DoubleWord expected2(0x08070605);
    CHECK_EQUAL(expected2, dw);
}
TEST(DoubleWord, readBigEndian) {
    unsigned char carr[]{0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x00};
    std::stringstream ss{reinterpret_cast<char *>(carr)};
    // check base case
    auto dw = binary::DoubleWord::readBigEndian(ss);
    CHECK_EQUAL(0x01020304, dw);
    binary::DoubleWord expected{0x01020304};
    CHECK_EQUAL(expected, dw);
    // check next step
    dw = binary::DoubleWord::readBigEndian(ss);
    CHECK_EQUAL(0x05060708, dw);
    binary::DoubleWord expected2(0x05060708);
    CHECK_EQUAL(expected2, dw);
}
TEST(Byte, writeByte) {
    binary::Byte barr[]{'1', 0xff, 0x00};
    std::stringstream ss;

    barr[0].write(ss);
    CHECK_EQUAL("1", ss.str());
    ss.str("");
    barr[1].write(ss);
    CHECK_EQUAL("\377", ss.str());
}
TEST(Word, writeLittleEndian) {
    binary::Word in{0x0102};
    binary::Word in2{0x0304};

    std::stringstream ss;
    in.writeLittleEndian(ss);
    in2.writeLittleEndian(ss);
    binary::Word out{binary::Word::readLittleEndian(ss)};
    binary::Word out2{binary::Word::readLittleEndian(ss)};
    CHECK_EQUAL(in, out);
    CHECK_EQUAL(in2, out2);
}
TEST(Word, writeBigEndian) {
    binary::Word in{0x0102};
    binary::Word in2{0x0304};

    std::stringstream ss;
    in.writeBigEndian(ss);
    in2.writeBigEndian(ss);
    binary::Word out{binary::Word::readBigEndian(ss)};
    binary::Word out2{binary::Word::readBigEndian(ss)};
    CHECK_EQUAL(in, out);
    CHECK_EQUAL(in2, out2);
}
TEST(DoubleWord, writeLittleEndian) {
    binary::DoubleWord in{0x01020304};
    binary::DoubleWord in2{0x05060708};

    std::stringstream ss;
    in.writeLittleEndian(ss);
    in2.writeLittleEndian(ss);
    binary::DoubleWord out{binary::DoubleWord::readLittleEndian(ss)};
    binary::DoubleWord out2{binary::DoubleWord::readLittleEndian(ss)};
    CHECK_EQUAL(in, out);
    CHECK_EQUAL(in2, out2);
}
TEST(DoubleWord, writeBigEndian) {
    binary::DoubleWord in{0x01020304};
    binary::DoubleWord in2{0x05060708};

    std::stringstream ss;
    in.writeBigEndian(ss);
    in2.writeBigEndian(ss);
    binary::DoubleWord out{binary::DoubleWord::readBigEndian(ss)};
    binary::DoubleWord out2{binary::DoubleWord::readBigEndian(ss)};
    CHECK_EQUAL(in, out);
    CHECK_EQUAL(in2, out2);
}
TEST(Byte, assign) {
    unsigned char carr[] = "feefiefoefoo";
    binary::Byte b;
    b = carr[0];
    CHECK_EQUAL(carr[0], b);
    binary::Byte b2{carr[1]};
    CHECK_EQUAL(carr[1], b2);
    unsigned char c{b};
    CHECK_EQUAL(carr[0], c);
    binary::Byte b3{b2};
    CHECK_EQUAL(b3, b2);
}
TEST(Word, assign) {
    CHECK_EQUAL(binary::Word{0x0102}, binary::Binary_t<uint16_t>{0x0102}) // verify alias
    binary::Word w{0x0102};
    auto w2 = binary::Word{0x0102};
    CHECK_EQUAL(w2, w);
    binary::Word w3{0x0304};
    w2 = binary::Word{0x0304};
    CHECK_EQUAL(w2, w3);
}
TEST(DoubleWord, assign) {
    CHECK_EQUAL(binary::DoubleWord{0x01020304}, binary::Binary_t<uint32_t>{0x01020304}) // verify alias
    binary::DoubleWord dw{0x01020304};
    auto dw2 = binary::DoubleWord{0x01020304};
    CHECK_EQUAL(dw2, dw);
    binary::DoubleWord dw3{0x05060708};
    dw2 = binary::DoubleWord{0x05060708};
    CHECK_EQUAL(dw3, dw2);
}

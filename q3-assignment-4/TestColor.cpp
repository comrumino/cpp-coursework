#include "TestHarness.h"
#include "binary.h"
#include "bitmap.h"
#include <iostream>
#include <sstream>
#include <vector>

TEST(Color, createColor) {
    int r = 0xAA;
    int g = 0xBB;
    int b = 0xCC;
    bitmap::Color color{r, g, b};

    CHECK_EQUAL(r, color.getRed());
    CHECK_EQUAL(g, color.getGreen());
    CHECK_EQUAL(b, color.getBlue());
    // extended test case
    unsigned int r2 = 0xCC;
    unsigned int g2 = 0xBB;
    unsigned int b2 = 0xAA;
    bitmap::Color color2{r2, g2, b2};

    CHECK_EQUAL(r2, color2.getRed());
    CHECK_EQUAL(g2, color2.getGreen());
    CHECK_EQUAL(b2, color2.getBlue());
    // extended test case 2
    double r3 = 0xBB;
    double g3 = 0xAA;
    double b3 = 0xCC;
    bitmap::Color color3{r3, g3, b3};

    CHECK_EQUAL(r3, color3.getRed());
    CHECK_EQUAL(g3, color3.getGreen());
    CHECK_EQUAL(b3, color3.getBlue());
}

TEST(Color, readColor) {
    unsigned char colorData[]{0x23, 0x24, 0x25, 0};
    std::istringstream colorStream{reinterpret_cast<char *>(colorData)};

    bitmap::Color color{bitmap::Color::read(colorStream)};

    CHECK_EQUAL(0x23, color.getBlue());
    CHECK_EQUAL(0x24, color.getGreen());
    CHECK_EQUAL(0x25, color.getRed());
    // extended test case
    unsigned char colorData2[]{0x01, 0x02, 0x03, 0};
    std::istringstream colorStream2{reinterpret_cast<char *>(colorData2)};

    bitmap::Color color2{bitmap::Color::read(colorStream2)};

    CHECK_EQUAL(0x01, color2.getBlue());
    CHECK_EQUAL(0x02, color2.getGreen());
    CHECK_EQUAL(0x03, color2.getRed());
    // extended test case 2
    unsigned char colorData3[]{0xf0, 0xff, 0x0f, 0};
    std::istringstream colorStream3{reinterpret_cast<char *>(colorData3)};

    bitmap::Color color3{bitmap::Color::read(colorStream3)};

    CHECK_EQUAL(0xf0, color3.getBlue());
    CHECK_EQUAL(0xff, color3.getGreen());
    CHECK_EQUAL(0x0f, color3.getRed());
}

TEST(Color, readScanLines) {
    unsigned char colorData[]{0xAA, 0xBB, 0xCC, 0x23, 0x24, 0x25, 0x11, 0x22, 0x33, 0xDD, 0xEE, 0xFF, 0};
    std::istringstream colorStream{reinterpret_cast<char *>(colorData)};

    typedef std::vector<bitmap::Color> ScanLine;
    typedef std::vector<ScanLine> ScanLineContainer;

    const int Width{2};
    const int Height{2};

    ScanLineContainer scanLines;

    for (auto row = 0; row < Height; ++row) {
        ScanLine scanLine;

        for (auto column = 0; column < Width; ++column) {
            scanLine.push_back(bitmap::Color::read(colorStream));
        }

        scanLines.push_back(scanLine);
    }

    const bitmap::Color expected{0x33, 0x22, 0x11};
    bitmap::Color actual{scanLines[1][0]};

    CHECK_EQUAL(expected, actual);
    // extended test case
    unsigned char colorData2[]{0xAA, 0xBB, 0xCC, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0xAA, 0xBB, 0xCC, 0x23, 0x24,
                               0x25, 0x26, 0x27, 0x28, 0xAA, 0xBB, 0xCC, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0};
    std::istringstream colorStream2{reinterpret_cast<char *>(colorData2)};

    typedef std::vector<bitmap::Color> ScanLine2;
    typedef std::vector<ScanLine> ScanLineContainer2;

    const int Width2{3};
    const int Height2{3};

    ScanLineContainer scanLines2;

    for (auto row = 0; row < Height2; ++row) {
        ScanLine scanLine2;

        for (auto column = 0; column < Width2; ++column) {
            scanLine2.push_back(bitmap::Color::read(colorStream2));
        }

        scanLines2.push_back(scanLine2);
    }
    CHECK_EQUAL(bitmap::Color(0x25, 0x24, 0x23), bitmap::Color(scanLines2[1][1]));
    CHECK_EQUAL(bitmap::Color(0x28, 0x27, 0x26), bitmap::Color(scanLines2[1][2]));
    CHECK_EQUAL(bitmap::Color(0x38, 0x37, 0x36), bitmap::Color(scanLines2[2][2]));
}

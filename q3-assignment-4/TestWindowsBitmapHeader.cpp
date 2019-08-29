#include "TestHarness.h"
#include "bitmap.h"
#include <fstream>

/*
 * Test non-padded bmp
 */
TEST(WindowsBitmapHeader, FileHeaderTest) {
    std::ifstream bmpStream{"q3-assignment-3/basic.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());
    bitmap::WindowsBitmapHeader bmpHeader;
    bmpHeader.readFileHeader(bmpStream);

    // The "q3-assignment-3/basic.bmp" image is 100x100 = 10000 pixels.
    // Each pixel is 3 bytes (1 red, 1 green, 1 blue), so the bmp image pixel data is 30000 bytes.
    // The header data is 54 bytes, so we expect 30054 as the total file size.
    CHECK_EQUAL(30054, bmpHeader.getFileSize());

    // We could also check the file size like so
    bmpStream.seekg(0, std::ifstream::end);
    CHECK_EQUAL(int(bmpStream.tellg()), bmpHeader.getFileSize());
}
TEST(WindowBitmapHeader, InfoHeaderTest) {
    std::ifstream bmpStream{"q3-assignment-3/basic.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader;
    bmpHeader.readFileHeader(bmpStream);
    bmpHeader.readInfoHeader(bmpStream);

    CHECK_EQUAL(100, bmpHeader.getBitmapHeight());
    CHECK_EQUAL(100, bmpHeader.getBitmapWidth());
}
/*
 * Test for 101x101 bmp
 */
TEST(WindowsBitmapHeader, FileHeaderTest_101) {
    std::ifstream bmpStream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader;
    bmpHeader.readFileHeader(bmpStream);

    bmpStream.seekg(0, std::ifstream::end);
    CHECK_EQUAL(int(bmpStream.tellg()), bmpHeader.getFileSize());
}
TEST(WindowBitmapHeader, InfoHeaderTest_101) {
    std::ifstream bmpStream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader;
    bmpHeader.readFileHeader(bmpStream);
    bmpHeader.readInfoHeader(bmpStream);

    CHECK_EQUAL(101, bmpHeader.getBitmapHeight());
    CHECK_EQUAL(101, bmpHeader.getBitmapWidth());
}
TEST(WindowsBitmapHeader, constructHeaderFromStream) {
    std::ifstream bmpStream{"q3-assignment-3/basic.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    // Construct the header object from a stream
    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};

    CHECK_EQUAL(30054, bmpHeader.getFileSize());
    CHECK_EQUAL(100, bmpHeader.getBitmapHeight());
    CHECK_EQUAL(100, bmpHeader.getBitmapWidth());
}
TEST(WindowsBitmapHeader, constructHeaderFromStream_101) {
    std::ifstream bmpStream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};

    CHECK_EQUAL(30758, bmpHeader.getFileSize());
    CHECK_EQUAL(101, bmpHeader.getBitmapHeight());
    CHECK_EQUAL(101, bmpHeader.getBitmapWidth());
}
/*
 * Test for 3x2 bmp
 */
TEST(WindowsBitmapHeader, ctorHeaderBasicColor) {
    std::ifstream bmpStream{"q3-assignment-3/basic_color.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};
    CHECK_EQUAL(3, bmpHeader.getBitmapWidth());
    CHECK_EQUAL(2, bmpHeader.getBitmapHeight());
    // 78 == (width + pad) * height * colorSize + headerSize
    // 78 == (3 + 1) * 2 * 3 + 54 == 78
    CHECK_EQUAL(78, bmpHeader.getFileSize());
}

#include "TestHarness.h"
#include "binary.h"
#include "bitmap.h"
#include "codec.h"
#include <fstream>

using namespace bitmap;
using namespace binary;
using namespace codec;
/*
 *given
 */
TEST(ec_createDecoder, WindowsBitmapDecoder) {
    std::ifstream bitmapStream{"q3-assignment-4/basic.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    WindowsBitmapDecoder decoderPrototype{};
    HBitmapDecoder decoder{decoderPrototype.clone(bitmapStream)};
    CHECK_EQUAL("image/x-ms-bmp", decoder->getMimeType());
}

TEST(ec_BitmapSizeTest, BitmapIterator) {
    std::ifstream bitmapStream{"q3-assignment-4/basic.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    WindowsBitmapDecoder decoderPrototype{};
    HBitmapDecoder decoder{decoderPrototype.clone(bitmapStream)};
    HBitmapIterator bitmapIter{decoder->createIterator()};

    CHECK_EQUAL(100, bitmapIter->getBitmapWidth());
    CHECK_EQUAL(100, bitmapIter->getBitmapHeight());
}

TEST(ec_BitmapScanLinesTest, BitmapIterator) {
    std::ifstream bitmapStream{"q3-assignment-4/basic.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    WindowsBitmapDecoder decoderPrototype{};
    HBitmapDecoder decoder{decoderPrototype.clone(bitmapStream)};
    HBitmapIterator bitmapIter{decoder->createIterator()};

    int numberOfScanLines{0};
    while (!bitmapIter->isEndOfImage()) {
        int numberOfPixelsInScanLine{0};
        while (!bitmapIter->isEndOfScanLine()) {
            ++numberOfPixelsInScanLine;
            bitmapIter->nextPixel();
        }
        CHECK_EQUAL(100, numberOfPixelsInScanLine);
        ++numberOfScanLines;

        bitmapIter->nextScanLine();
    }
    CHECK_EQUAL(100, numberOfScanLines);
}

TEST(ec_BitmapReadWrite, Bitmap) {
    // Read in the bitmap

    std::ifstream bitmapStream{"q3-assignment-4/basic.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    WindowsBitmapDecoder decoderPrototype{};
    HBitmapDecoder decoder{decoderPrototype.clone(bitmapStream)};
    HBitmapIterator bitmapIter{decoder->createIterator()};

    // Write out the bitmap to a different file with its write() method

    std::ofstream outputStream{"q3-assignment-4/output.bmp", std::ios::binary};
    CHECK(outputStream.is_open());

    WindowsBitmapEncoder encoderPrototype{};
    HBitmapEncoder encoder{encoderPrototype.clone(bitmapIter)};

    encoder->encodeToStream(outputStream);
    outputStream.close();

    // Read that one back in and check sizes

    std::ifstream bitmapStream2{"q3-assignment-4/output.bmp", std::ios::binary};
    CHECK(bitmapStream2.is_open());

    HBitmapDecoder decoder2{decoderPrototype.clone(bitmapStream2)};
    bitmapIter = decoder2->createIterator();

    int numberOfScanLines{0};
    while (!bitmapIter->isEndOfImage()) {
        int numberOfPixelsInScanLine{0};
        while (!bitmapIter->isEndOfScanLine()) {
            ++numberOfPixelsInScanLine;
            bitmapIter->nextPixel();
        }
        CHECK_EQUAL(100, numberOfPixelsInScanLine);
        ++numberOfScanLines;

        bitmapIter->nextScanLine();
    }
    CHECK_EQUAL(100, numberOfScanLines);
}

//// --- Repeat the tests with a bitmap that requires pad bytes (101x101)

TEST(ec_BitmapSizeTest_101, BitmapIterator) {
    std::ifstream bitmapStream{"q3-assignment-4/basic_101.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    WindowsBitmapDecoder decoderPrototype{};
    HBitmapDecoder decoder{decoderPrototype.clone(bitmapStream)};
    HBitmapIterator bitmapIter{decoder->createIterator()};

    CHECK_EQUAL(101, bitmapIter->getBitmapWidth());
    CHECK_EQUAL(101, bitmapIter->getBitmapHeight());
}

TEST(ec_BitmapScanLinesTest_101, BitmapIterator) {
    std::ifstream bitmapStream{"q3-assignment-4/basic_101.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    WindowsBitmapDecoder decoderPrototype{};
    HBitmapDecoder decoder{decoderPrototype.clone(bitmapStream)};
    HBitmapIterator bitmapIter{decoder->createIterator()};

    int numberOfScanLines{0};
    while (!bitmapIter->isEndOfImage()) {
        int numberOfPixelsInScanLine{0};
        while (!bitmapIter->isEndOfScanLine()) {
            ++numberOfPixelsInScanLine;
            bitmapIter->nextPixel();
        }
        CHECK_EQUAL(101, numberOfPixelsInScanLine);
        ++numberOfScanLines;

        bitmapIter->nextScanLine();
    }
    CHECK_EQUAL(101, numberOfScanLines);
}

TEST(ec_BitmapReadWrite_101, Bitmap) {
    // Read in the bitmap
    std::ifstream bitmapStream{"q3-assignment-4/basic_101.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    WindowsBitmapDecoder decoderPrototype{};
    HBitmapDecoder decoder{decoderPrototype.clone(bitmapStream)};
    HBitmapIterator bitmapIter{decoder->createIterator()};

    // Write out the bitmap to a different file with its write() method

    std::ofstream outputStream{"q3-assignment-4/output_101.bmp", std::ios::binary};
    CHECK(outputStream.is_open());

    WindowsBitmapEncoder encoderPrototype{};
    HBitmapEncoder encoder{encoderPrototype.clone(bitmapIter)};

    encoder->encodeToStream(outputStream);
    outputStream.close();

    // Read that one back in and check sizes

    std::ifstream bitmapStream2{"q3-assignment-4/output_101.bmp", std::ios::binary};
    CHECK(bitmapStream2.is_open());

    HBitmapDecoder decoder2{decoderPrototype.clone(bitmapStream2)};
    bitmapIter = decoder2->createIterator();

    int numberOfScanLines{0};
    while (!bitmapIter->isEndOfImage()) {
        int numberOfPixelsInScanLine{0};
        while (!bitmapIter->isEndOfScanLine()) {
            ++numberOfPixelsInScanLine;
            bitmapIter->nextPixel();
        }
        CHECK_EQUAL(101, numberOfPixelsInScanLine);
        ++numberOfScanLines;

        bitmapIter->nextScanLine();
    }
    CHECK_EQUAL(101, numberOfScanLines);
}

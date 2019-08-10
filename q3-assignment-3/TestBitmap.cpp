#include "TestHarness.h"
#include "binary.h"
#include "bitmap.h"
#include <fstream>
#include <vector>

TEST(BitmapSizeTest, Bitmap) {
    // check case basic color
    std::ifstream bmpStream{"q3-assignment-3/basic_color.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};
    bitmap::Bitmap bmp{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    CHECK_EQUAL(3, bmp.getWidth());
    CHECK_EQUAL(2, bmp.getHeight());
    // check case basic
    bmpStream = std::ifstream{"q3-assignment-3/basic.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bmpHeader = bitmap::WindowsBitmapHeader{bmpStream};
    bmp = bitmap::Bitmap{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    CHECK_EQUAL(100, bmp.getWidth());
    CHECK_EQUAL(100, bmp.getHeight());
    // check case 101
    bmpStream = std::ifstream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bmpHeader = bitmap::WindowsBitmapHeader{bmpStream};
    bmp = bitmap::Bitmap{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    CHECK_EQUAL(101, bmp.getWidth());
    CHECK_EQUAL(101, bmp.getHeight());
}
TEST(BitmapScanLinesTest, Bitmap) {
    // check case basic color
    std::ifstream bitmapStream{"q3-assignment-3/basic_color.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    bitmap::WindowsBitmapHeader bitmapHeader{bitmapStream};
    bitmap::Bitmap bitmap{bitmapHeader.getBitmapWidth(), bitmapHeader.getBitmapHeight(), bitmapStream};

    int numberOfScanLines{0};
    for (auto &scanLine : bitmap) {
        CHECK_EQUAL(3, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(2, numberOfScanLines);
    // check case basic
    bitmapStream = std::ifstream{"q3-assignment-3/basic.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    bitmapHeader = bitmap::WindowsBitmapHeader{bitmapStream};
    bitmap = bitmap::Bitmap{bitmapHeader.getBitmapWidth(), bitmapHeader.getBitmapHeight(), bitmapStream};

    numberOfScanLines = 0;
    for (auto &scanLine : bitmap) {
        CHECK_EQUAL(100, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(100, numberOfScanLines);
    // check case 101
    bitmapStream = std::ifstream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    bitmapHeader = bitmap::WindowsBitmapHeader{bitmapStream};
    bitmap = bitmap::Bitmap{bitmapHeader.getBitmapWidth(), bitmapHeader.getBitmapHeight(), bitmapStream};

    numberOfScanLines = 0;
    for (auto &scanLine : bitmap) {
        CHECK_EQUAL(101, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(101, numberOfScanLines);
}
TEST(BitmapReadWrite_color, Bitmap) {
    // read
    std::ifstream bmpStream{"q3-assignment-3/basic_color.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};
    bitmap::Bitmap bmp{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    // write
    std::ofstream outputStream{"q3-assignment-3/output.bmp", std::ios::binary};
    CHECK(outputStream.is_open());

    bmpHeader.write(outputStream);
    bmp.write(outputStream);
    outputStream.close();

    // read from previous write
    bmpStream = std::ifstream{"q3-assignment-3/output.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bmpHeader = bitmap::WindowsBitmapHeader{bmpStream};
    bitmap::Bitmap bmp2{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    int numberOfScanLines{0};
    for (auto &scanLine : bmp2) {
        CHECK_EQUAL(3, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(2, numberOfScanLines);

    // compare colors from both reads
    auto scanLine = *bmp.begin();
    auto scanLine2 = *bmp2.begin();
    std::vector<bitmap::Color> v;
    std::vector<bitmap::Color> v2;
    for (auto &color : scanLine) {
        v.push_back(color);
    }
    for (auto &color : scanLine2) {
        v2.push_back(color);
    }
    for (int i = 0; i < scanLine.size(); ++i) {
        // std::cout << "v1[" << i << "] = "  << v1.at(i) << std::endl;
        // std::cout << "v2[" << i << "] = "  << v2.at(i) << std::endl;
        CHECK(v.at(i) == v2.at(i));
    }
}
TEST(BitmapReadWrite, Bitmap) {
    // read
    std::ifstream bmpStream{"q3-assignment-3/basic.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};
    bitmap::Bitmap bmp{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    // write
    std::ofstream outputStream{"q3-assignment-3/output.bmp", std::ios::binary};
    CHECK(outputStream.is_open());

    bmpHeader.write(outputStream);
    bmp.write(outputStream);
    outputStream.close();

    // read from previous write
    bmpStream = std::ifstream{"q3-assignment-3/output.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bmpHeader = bitmap::WindowsBitmapHeader{bmpStream};
    bitmap::Bitmap bmp2{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    int numberOfScanLines{0};
    for (auto &scanLine : bmp2) {
        CHECK_EQUAL(100, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(100, numberOfScanLines);

    // compare colors from both reads
    auto scanLine = *bmp.begin();
    auto scanLine2 = *bmp2.begin();
    std::vector<bitmap::Color> v;
    std::vector<bitmap::Color> v2;
    for (auto &color : scanLine) {
        v.push_back(color);
    }
    for (auto &color : scanLine2) {
        v2.push_back(color);
    }
    for (int i = 0; i < scanLine.size(); ++i) {
        // std::cout << "v1[" << i << "] = "  << v1.at(i) << std::endl;
        // std::cout << "v2[" << i << "] = "  << v2.at(i) << std::endl;
        CHECK(v.at(i) == v2.at(i));
    }
}
TEST(BinaryOstreamIterator, Bitmap) {
    // read
    std::ifstream bmpStream{"q3-assignment-3/basic_color.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};
    bitmap::Bitmap bmp{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    // write
    std::ofstream outputStream{"q3-assignment-3/output_iter.bmp", std::ios::binary};
    CHECK(outputStream.is_open());

    bmpHeader.write(outputStream);
    for (auto &scanLine : bmp) {
        std::copy(scanLine.begin(), scanLine.end(), binary::binary_ostream_iterator<bitmap::Color>(outputStream));
        for (auto pad = 0; pad < bmp.getPaddingSize(); ++pad) {
            binary::Byte(0).write(outputStream);
        }
    }
    outputStream.close();

    // read from previous write
    std::ifstream bmpStream2{"q3-assignment-3/output_iter.bmp", std::ios::binary};
    CHECK(bmpStream2.is_open());

    bitmap::WindowsBitmapHeader bmpHeader2{bmpStream2};
    bitmap::Bitmap bmp2{bmpHeader2.getBitmapWidth(), bmpHeader2.getBitmapHeight(), bmpStream2};

    int numberOfScanLines{0};
    for (auto &scanLine : bmp2) {
        CHECK_EQUAL(3, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(2, numberOfScanLines);

    // compare colors from both reads
    auto scanLine = *bmp.begin();
    auto scanLine2 = *bmp2.begin();
    std::vector<bitmap::Color> v;
    std::vector<bitmap::Color> v2;
    for (auto &color : scanLine) {
        v.push_back(color);
    }
    for (auto &color : scanLine2) {
        v2.push_back(color);
    }
    for (int i = 0; i < scanLine.size(); ++i) {
        // std::cout << "v1[" << i << "] = "  << v1.at(i) << std::endl;
        // std::cout << "v2[" << i << "] = "  << v2.at(i) << std::endl;
        CHECK(v.at(i) == v2.at(i));
    }
}
TEST(BitmapSizeTest_101, Bitmap) {
    std::ifstream bitmapStream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    bitmap::WindowsBitmapHeader bitmapHeader{bitmapStream};
    bitmap::Bitmap bitmap{bitmapHeader.getBitmapWidth(), bitmapHeader.getBitmapHeight(), bitmapStream};

    CHECK_EQUAL(101, bitmap.getWidth());
    CHECK_EQUAL(101, bitmap.getHeight());
}

TEST(BitmapScanLinesTest_101, Bitmap) {
    std::ifstream bitmapStream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bitmapStream.is_open());

    bitmap::WindowsBitmapHeader bitmapHeader{bitmapStream};
    bitmap::Bitmap bitmap{bitmapHeader.getBitmapWidth(), bitmapHeader.getBitmapHeight(), bitmapStream};

    int numberOfScanLines{0};
    for (auto scanLine : bitmap) {
        CHECK_EQUAL(101, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(101, numberOfScanLines);
}

TEST(BitmapReadWrite_101, Bitmap) {
    // read
    std::ifstream bmpStream{"q3-assignment-3/basic_101.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bitmap::WindowsBitmapHeader bmpHeader{bmpStream};
    bitmap::Bitmap bmp{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    // write
    std::ofstream outputStream{"q3-assignment-3/output.bmp", std::ios::binary};
    CHECK(outputStream.is_open());

    bmpHeader.write(outputStream);
    bmp.write(outputStream);
    outputStream.close();

    // read from previous write
    bmpStream = std::ifstream{"q3-assignment-3/output.bmp", std::ios::binary};
    CHECK(bmpStream.is_open());

    bmpHeader = bitmap::WindowsBitmapHeader{bmpStream};
    bitmap::Bitmap bmp2{bmpHeader.getBitmapWidth(), bmpHeader.getBitmapHeight(), bmpStream};

    int numberOfScanLines{0};
    for (auto &scanLine : bmp2) {
        CHECK_EQUAL(101, scanLine.size());
        ++numberOfScanLines;
    }
    CHECK_EQUAL(101, numberOfScanLines);

    // compare colors from both reads
    auto scanLine = *bmp.begin();
    auto scanLine2 = *bmp2.begin();
    std::vector<bitmap::Color> v;
    std::vector<bitmap::Color> v2;
    for (auto &color : scanLine) {
        v.push_back(color);
    }
    for (auto &color : scanLine2) {
        v2.push_back(color);
    }
    for (int i = 0; i < scanLine.size(); ++i) {
        // std::cout << "v1[" << i << "] = "  << v1.at(i) << std::endl;
        // std::cout << "v2[" << i << "] = "  << v2.at(i) << std::endl;
        CHECK(v.at(i) == v2.at(i));
    }
}

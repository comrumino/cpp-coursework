#include "bitmap.h"
#include "binary.h"
using namespace binary;
using namespace std;

namespace bitmap {

Color Color::read(istream &is) {
    auto blue = Byte::read(is);
    auto green = Byte::read(is);
    auto red = Byte::read(is);
    return Color{red, green, blue}; // user order: ( red, green, blue )
}

void Color::write(ostream &os) const {
    blue.write(os);
    green.write(os);
    red.write(os);
}

ostream &operator<<(ostream &os, const Color &rhs) {
    rhs.write(os);
    return os;
}
Bitmap::Bitmap(int w, int h, istream &is) : width{w}, height{h}, paddingSize{0} {
    if (is.rdbuf()->in_avail() != 0) {
        auto align = DoubleWord::SIZEOF;
        auto scanLineSize = Color::SIZEOF * width;
        paddingSize = (align - (scanLineSize % align)) % align;

        for (auto h = 0; h < getHeight(); h++) {
            readScanLine(is);
        }
    }
}

void Bitmap::write(ostream &os) const {
    for (const auto &scanLine : scanLines) {
        writeScanLine(os, scanLine);
    }
}

void Bitmap::readScanLine(istream &is) {
    ScanLine scanLine;
    for (auto w = 0; w < getWidth(); w++) {
        scanLine.emplace_back(Color::read(is));
    }

    scanLines.emplace_back(std::move(scanLine));
    readPadding(is);
}

void Bitmap::writeScanLine(ostream &os, const ScanLine &scanLine) const {
    std::copy(scanLine.begin(), scanLine.end(), binary_ostream_iterator<Color>(os));
    writePadding(os);
}

void Bitmap::readPadding(istream &is) const {
    for (auto p = 0; p < getPaddingSize(); p++) {
        is.ignore();
    }
}

void Bitmap::writePadding(ostream &os) const {
    binary::Byte pad;
    for (auto p = 0; p < getPaddingSize(); p++) {
        pad.write(os);
    }
}

HBitmapIterator Bitmap::createIterator() const { return std::make_shared<BitmapIterator>(*this); }
ostream &operator<<(ostream &os, const Bitmap &rhs) {
    rhs.write(os);
    return os;
}
constexpr binary::DoubleWord WindowsBitmapHeader::fileHeaderBytes;
constexpr binary::Byte WindowsBitmapHeader::firstIdentifier;
constexpr binary::Byte WindowsBitmapHeader::secondIdentifier;
constexpr binary::DoubleWord WindowsBitmapHeader::reserved;
constexpr binary::DoubleWord WindowsBitmapHeader::infoHeaderBytes;
constexpr binary::DoubleWord rawImageOffset;
constexpr binary::Word WindowsBitmapHeader::colorPlanes;
constexpr binary::Word WindowsBitmapHeader::colorDepth;
constexpr binary::DoubleWord WindowsBitmapHeader::numberOfColors;
constexpr binary::DoubleWord WindowsBitmapHeader::numberOfImportantColors;

void WindowsBitmapHeader::read(istream &is) {
    readFileHeader(is);
    readInfoHeader(is);

    auto rawImagePos = static_cast<streampos>(rawImageOffset);

    if (rawImagePos != is.tellg()) // skip past "other" headers
    {
        is.seekg(rawImagePos);
    }

    verifyEquality(rawImagePos, is.tellg(), "actual raw image position referred to via rawImageOffset");
}

void WindowsBitmapHeader::readFileHeader(istream &is) {
    verifyEquality(static_cast<streampos>(0), is.tellg(), "firstIdentifier position");
    verifyEquality(firstIdentifier, Byte::read(is), "firstIdentifier value");

    verifyEquality(static_cast<streampos>(1), is.tellg(), "secondIdentifier position");
    verifyEquality(secondIdentifier, Byte::read(is), "secondIdentifier value");

    verifyEquality(static_cast<streampos>(2), is.tellg(), "fileSize position");
    fileSize = DoubleWord::read(is);

    verifyEquality(static_cast<streampos>(6), is.tellg(), "reserved position");
    verifyEquality(reserved, DoubleWord::read(is), "reserved value");

    verifyEquality(static_cast<streampos>(10), is.tellg(), "rawImageOffset position");
    verifyEquality(rawImageOffset, DoubleWord::read(is), "rawImageOffset value");

    verifyEquality(static_cast<streampos>(14), is.tellg(), "end file header");
}

void WindowsBitmapHeader::readInfoHeader(istream &is) {
    verifyEquality(static_cast<streampos>(14), is.tellg(), "infoHeaderBytes position");
    verifyEquality(infoHeaderBytes, DoubleWord::read(is), "infoHeaderBytes value");

    verifyEquality(static_cast<streampos>(18), is.tellg(), "width position");
    width = DoubleWord::read(is);

    verifyEquality(static_cast<streampos>(22), is.tellg(), "height position");
    height = DoubleWord::read(is);

    verifyEquality(static_cast<streampos>(26), is.tellg(), "colorPlanes position");
    verifyEquality(colorPlanes, Word::read(is), "colorPlanes value");

    verifyEquality(static_cast<streampos>(28), is.tellg(), "colorDepth position");
    static_cast<void>(Word::read(is));

    verifyEquality(static_cast<streampos>(30), is.tellg(), "compressionMethod position");
    compressionType = DoubleWord::read(is);

    verifyEquality(static_cast<streampos>(34), is.tellg(), "compressedImageSize position");
    compressedImageSize = DoubleWord::read(is);

    verifyEquality(static_cast<streampos>(38), is.tellg(), "horizontalPixelsPerMeter position");
    horizontalPixelsPerMeter = DoubleWord::read(is);

    verifyEquality(static_cast<streampos>(42), is.tellg(), "verticalPixelsPerMeter position");
    verticalPixelsPerMeter = DoubleWord::read(is);

    verifyEquality(static_cast<streampos>(46), is.tellg(), "numberOfColors position");
    static_cast<void>(DoubleWord::read(is));

    verifyEquality(static_cast<streampos>(50), is.tellg(), "numberOfImportantColors position");
    static_cast<void>(DoubleWord::read(is));

    verifyEquality(static_cast<streampos>(54), is.tellg(), "end info header");
}

void WindowsBitmapHeader::writeFileHeader(ostream &os) const {
    firstIdentifier.write(os);
    secondIdentifier.write(os);
    fileSize.write(os);
    reserved.write(os);
    rawImageOffset.write(os);
}

void WindowsBitmapHeader::writeInfoHeader(ostream &os) const {
    infoHeaderBytes.write(os);
    width.write(os);
    height.write(os);
    colorPlanes.write(os);
    colorDepth.write(os);
    compressionType.write(os);
    compressedImageSize.write(os);
    horizontalPixelsPerMeter.write(os);
    verticalPixelsPerMeter.write(os);
    numberOfColors.write(os);
    numberOfImportantColors.write(os);
}

void WindowsBitmapHeader::write(ostream &os) const {
    writeFileHeader(os);
    writeInfoHeader(os);
}

BitmapIterator::BitmapIterator(const Bitmap &bitmap)
    : width{bitmap.getWidth()}, height{bitmap.getHeight()}, numberOfPadBytes{bitmap.getPaddingSize()},
      startOfScanLines{bitmap.begin()}, currScanLine{bitmap.begin()}, endOfScanLines{bitmap.end()} {
    if (!BitmapIterator::isEndOfImage()) {
        currPixel = currScanLine->begin();
    }
}

BitmapIterator::~BitmapIterator() = default;
BitmapIterator::BitmapIterator(HBitmapIterator &bitmapIter) {
    this->width = bitmapIter->getBitmapWidth();
    this->height = bitmapIter->getBitmapHeight();
    this->numberOfPadBytes = bitmapIter->getBitmapNumberOfPadBytes();
    this->startOfScanLines = bitmapIter->getStartOfImage();
    this->endOfScanLines = bitmapIter->getEndOfImage();
    this->currScanLine = bitmapIter->getCurrentScanLine();
    this->currPixel = bitmapIter->getCurrentPixel();
}
Color BitmapIterator::getColor() const { return *currPixel; }

int BitmapIterator::getBitmapWidth() const { return width; }

int BitmapIterator::getBitmapHeight() const { return height; }

int BitmapIterator::getBitmapNumberOfPadBytes() const { return numberOfPadBytes; }

bool BitmapIterator::isEndOfImage() const { return currScanLine == endOfScanLines; }

bool BitmapIterator::isEndOfScanLine() const { return currPixel == currScanLine->end(); }

bool BitmapIterator::isStartOfScanLine() const { return currPixel == currScanLine->begin(); }
ScanLineIterator BitmapIterator::getCurrentScanLine() const { return currScanLine; }
ScanLineIterator BitmapIterator::getStartOfImage() const { return startOfScanLines; }
ScanLineIterator BitmapIterator::getEndOfImage() const { return endOfScanLines; }
PixelIterator BitmapIterator::getCurrentPixel() const { return currPixel; }

void BitmapIterator::nextScanLine() {
    if (isEndOfImage()) {
        throw std::runtime_error{"cannot retrieve next scan line, currently at end of image"};
    }
    ++currScanLine;
    currPixel = currScanLine->begin();
}

void BitmapIterator::nextPixel() {
    if (isEndOfScanLine()) {
        throw std::runtime_error{"cannot retrieve next pixel, current at end of scan line"};
    }
    ++currPixel;
}

} // namespace bitmap

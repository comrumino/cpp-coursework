#pragma once
#include "binary.h"
#include "ranged_number.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
using namespace binary;

namespace {
std::istringstream inullsstream("");
std::istream inullstream(inullsstream.rdbuf());
} // namespace
namespace bitmap {

class Color {
  public:
    static constexpr int SIZEOF = 3; // one byte per color: red, green, blue
    static Color read(std::istream &is) noexcept;
    static constexpr int INF{0};
    static constexpr int SUP{256};

    Color() = default;
    ~Color() = default;
    template <typename T> Color(const T &red, const T &green, const T &blue);
    Color(const Color &src) = default;
    Color(Color &&src) noexcept = default;

    Color &operator=(const Color &rhs) = default;
    bool operator==(const Color &rhs) const noexcept {
        return getRed() == rhs.getRed() && getGreen() == rhs.getGreen() && getBlue() == rhs.getBlue();
    }
    bool operator!=(const Color &rhs) const noexcept { return !(*this == rhs); }

    const binary::Byte getRed() const noexcept { return red.getValue(); }
    const binary::Byte getGreen() const noexcept { return green.getValue(); }
    const binary::Byte getBlue() const noexcept { return blue.getValue(); }
    void write(std::ostream &os) const;

  private:
    binary::Byte red;
    binary::Byte green;
    binary::Byte blue;
};
template <typename T>
Color::Color(const T &red, const T &green, const T &blue)
    : red{static_cast<binary::Byte>(red)}, green{static_cast<binary::Byte>(green)}, blue{static_cast<binary::Byte>(
                                                                                        blue)} {}

std::ostream &operator<<(std::ostream &os, const Color &rhs) noexcept;

class IBitmapIterator {
  public:
    virtual ~IBitmapIterator(){};

    virtual Color getColor() const noexcept = 0;

    virtual int getBitmapWidth() const noexcept = 0;

    virtual int getBitmapHeight() const noexcept = 0;

    virtual int getBitmapNumberOfPadBytes() const noexcept = 0;

    virtual bool isEndOfImage() const noexcept = 0;

    virtual bool isEndOfScanLine() const noexcept = 0;

    virtual bool isStartOfScanLine() const noexcept = 0;

    virtual void nextScanLine() = 0;

    virtual void nextPixel() = 0;
};

using HBitmapIterator = std::shared_ptr<IBitmapIterator>;

class Bitmap {
  public:
    using ScanLine = std::vector<Color>;
    using ScanLineCollection = std::vector<ScanLine>;
    using ScanLineIterator = ScanLineCollection::const_iterator;
    using Pixel = Color;
    using PixelIterator = ScanLine::const_iterator;
    using ReversePixelIterator = ScanLine::const_reverse_iterator;

    Bitmap() = default;
    ~Bitmap() = default;
    Bitmap(int width, int height, std::istream &is = inullstream);
    Bitmap(const Bitmap &src) = default;

    Bitmap &operator=(const Bitmap &rhs) = default;

    int getWidth() const noexcept { return width; }
    int getHeight() const noexcept { return height; }
    int getPaddingSize() const noexcept { return paddingSize; }

    ScanLineIterator begin() const noexcept { return scanLines.begin(); }
    ScanLineIterator end() const noexcept { return scanLines.end(); }
    HBitmapIterator createIterator() const noexcept;

    void write(std::ostream &os) const;

  private:
    int width{0};
    int height{0};
    ScanLineCollection scanLines;
    int paddingSize{0};

    void readScanLine(std::istream &is) noexcept;
    void writeScanLine(std::ostream &os, const ScanLine &scanLine) const;

    void readPadding(std::istream &is) const noexcept;
    void writePadding(std::ostream &os) const noexcept;
};

std::ostream &operator<<(std::ostream &os, const Bitmap &rhs);

class WindowsBitmapHeader {
  public:
    WindowsBitmapHeader() = default;
    ~WindowsBitmapHeader() = default;
    WindowsBitmapHeader(std::istream &is) { read(is); }
    WindowsBitmapHeader(binary::DoubleWord_t width, binary::DoubleWord_t height) : width{width}, height{height} {}

    WindowsBitmapHeader(const WindowsBitmapHeader &src) = default;
    WindowsBitmapHeader(WindowsBitmapHeader &&src) noexcept = default;

    WindowsBitmapHeader &operator=(const WindowsBitmapHeader &rhs) = default;
    WindowsBitmapHeader &operator=(WindowsBitmapHeader &&rhs) noexcept = default;

    void read(std::istream &is);
    void readFileHeader(std::istream &is);
    void readInfoHeader(std::istream &is);

    int getBitmapWidth() const noexcept { return width.getValue(); }
    int getBitmapHeight() const noexcept { return height.getValue(); }
    int getFileSize() const noexcept { return fileSize.getValue(); }

    void writeFileHeader(std::ostream &os) const;
    void writeInfoHeader(std::ostream &os) const;
    void write(std::ostream &os) const;

  private:
    // file header
    static constexpr binary::DoubleWord fileHeaderBytes{14};
    static constexpr binary::Byte firstIdentifier{'B'};
    static constexpr binary::Byte secondIdentifier{'M'};
    binary::DoubleWord fileSize{0};
    static constexpr binary::DoubleWord reserved{0};

    // info header, starts at pos 14
    static constexpr binary::DoubleWord infoHeaderBytes{40};
    binary::DoubleWord width{0};
    binary::DoubleWord height{0};
    binary::DoubleWord compressionType{0};
    binary::DoubleWord compressedImageSize{0};
    binary::DoubleWord horizontalPixelsPerMeter{0};
    binary::DoubleWord verticalPixelsPerMeter{0};

    static constexpr binary::Word colorPlanes{1};
    static constexpr binary::Word colorDepth{24};
    static constexpr binary::DoubleWord numberOfColors{0};
    static constexpr binary::DoubleWord numberOfImportantColors{0};
    static constexpr binary::DoubleWord rawImageOffset{54}; // fileHeaderBytes + infoHeaderBytes
};

class BitmapIterator : public IBitmapIterator {
  public:
    BitmapIterator(const Bitmap &bitmap);

    virtual ~BitmapIterator() = default;

    virtual Color getColor() const noexcept override;

    virtual int getBitmapWidth() const noexcept override;
    virtual int getBitmapHeight() const noexcept override;
    virtual int getBitmapNumberOfPadBytes() const noexcept override;

    virtual bool isEndOfImage() const noexcept override;
    virtual bool isEndOfScanLine() const noexcept override;
    virtual bool isStartOfScanLine() const noexcept override;

    virtual void nextScanLine() override;
    virtual void nextPixel() override;

  private:
    const int width, height, numberOfPadBytes;
    Bitmap::ScanLineIterator currScanLine;
    Bitmap::ScanLineIterator endOfScanLines;
    Bitmap::PixelIterator currPixel;
    Bitmap::ReversePixelIterator currReversePixel;
};

class BitmapIteratorDecorator : public IBitmapIterator {
  public:
    BitmapIteratorDecorator(HBitmapIterator iterator) : iterator{iterator} {}

    ~BitmapIteratorDecorator() = default;

    BitmapIteratorDecorator(const BitmapIteratorDecorator &src) = default;
    BitmapIteratorDecorator(BitmapIteratorDecorator &&src) = default;

    BitmapIteratorDecorator &operator=(const BitmapIteratorDecorator &rhs) = default;
    BitmapIteratorDecorator &operator=(BitmapIteratorDecorator &&rhs) = default;

    virtual Color getColor() const noexcept override { return iterator->getColor(); }

    virtual int getBitmapWidth() const noexcept override { return iterator->getBitmapWidth(); }

    virtual int getBitmapHeight() const noexcept override { return iterator->getBitmapHeight(); }

    virtual int getBitmapNumberOfPadBytes() const noexcept override { return iterator->getBitmapNumberOfPadBytes(); }

    virtual bool isEndOfImage() const noexcept override { return iterator->isEndOfImage(); }

    virtual bool isEndOfScanLine() const noexcept override { return iterator->isEndOfScanLine(); }

    virtual bool isStartOfScanLine() const noexcept override { return iterator->isEndOfScanLine(); }

    virtual void nextScanLine() override { iterator->nextScanLine(); }

    virtual void nextPixel() override { iterator->nextPixel(); }

  private:
    HBitmapIterator iterator;
};

class BrightnessDecorator : public BitmapIteratorDecorator {
  public:
    BrightnessDecorator(HBitmapIterator innerDecorator, const int adjustment)
        : BitmapIteratorDecorator{innerDecorator}, adjustment{adjustment} {}

    ~BrightnessDecorator() = default;

    BrightnessDecorator(const BrightnessDecorator &src) = default;

    BrightnessDecorator &operator=(const BrightnessDecorator &rhs) = default;

    virtual Color getColor() const noexcept override {
        auto color = BitmapIteratorDecorator::getColor();

        ranged_number<int, Color::INF, Color::SUP> red{color.getRed() + adjustment};
        ranged_number<int, Color::INF, Color::SUP> green{color.getGreen() + adjustment};
        ranged_number<int, Color::INF, Color::SUP> blue{color.getBlue() + adjustment};
        return Color{static_cast<binary::Byte_t>(red), static_cast<binary::Byte_t>(green),
                     static_cast<binary::Byte_t>(blue)};
    }

  private:
    int adjustment;
};

class ColorInversionDecorator : public BitmapIteratorDecorator {
  public:
    ColorInversionDecorator(HBitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {}
    ~ColorInversionDecorator() = default;

    ColorInversionDecorator(const ColorInversionDecorator &src) = default;
    ColorInversionDecorator(ColorInversionDecorator &&src) = default;
    ColorInversionDecorator &operator=(const ColorInversionDecorator &rhs) = default;
    ColorInversionDecorator &operator=(ColorInversionDecorator &&rhs) = default;

    virtual Color getColor() const noexcept override {
        auto color = BitmapIteratorDecorator::getColor();
        auto red = Color::SUP - color.getRed();
        auto green = Color::SUP - color.getGreen();
        auto blue = Color::SUP - color.getBlue();

        return Color{red, green, blue};
    }
};

class RedShiftDecorator : public BitmapIteratorDecorator {
  public:
    RedShiftDecorator(HBitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {}
    ~RedShiftDecorator() = default;

    RedShiftDecorator(const RedShiftDecorator &src) = default;
    RedShiftDecorator(RedShiftDecorator &&src) = default;

    RedShiftDecorator &operator=(const RedShiftDecorator &rhs) = default;
    RedShiftDecorator &operator=(RedShiftDecorator &&rhs) = default;

    virtual Color getColor() const noexcept override {
        auto color = BitmapIteratorDecorator::getColor();

        auto red = static_cast<double>(std::min(static_cast<int>(color.getRed() * 1.33), Color::SUP));
        auto green = color.getGreen() * 0.67;
        auto blue = color.getBlue() * 0.67;

        return Color{red, green, blue};
    }
};

class BlueShiftDecorator : public BitmapIteratorDecorator {
  public:
    BlueShiftDecorator(HBitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {}
    ~BlueShiftDecorator() = default;

    BlueShiftDecorator(const BlueShiftDecorator &src) = default;
    BlueShiftDecorator(BlueShiftDecorator &&src) = default;

    BlueShiftDecorator &operator=(const BlueShiftDecorator &rhs) = default;
    BlueShiftDecorator &operator=(BlueShiftDecorator &&rhs) = default;

    virtual Color getColor() const noexcept override {
        auto color = BitmapIteratorDecorator::getColor();

        auto red = color.getRed() * 0.67;
        auto green = color.getGreen() * 0.67;
        auto blue = static_cast<double>(std::min(static_cast<int>(color.getBlue() * 1.33), Color::SUP));

        return Color{red, green, blue};
    }
};

class DownLeftDecorator : public BitmapIteratorDecorator {
  public:
    DownLeftDecorator(HBitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {
        BitmapIteratorDecorator::nextScanLine();
    }
    ~DownLeftDecorator() = default;

    DownLeftDecorator(const DownLeftDecorator &src) = default;
    DownLeftDecorator(DownLeftDecorator &&src) = default;

    DownLeftDecorator &operator=(const DownLeftDecorator &rhs) = default;
    DownLeftDecorator &operator=(DownLeftDecorator &&rhs) = default;

    virtual void nextScanLine() override {
        BitmapIteratorDecorator::nextScanLine();
        BitmapIteratorDecorator::nextPixel();
    }
};

} // namespace bitmap

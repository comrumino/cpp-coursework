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
    static Color read(std::istream &is);
    static constexpr int INF{0};
    static constexpr int SUP{255};

    Color() = default;
    ~Color() = default;
    template <typename T> Color(const T &red, const T &green, const T &blue);
    Color(const Color &src) = default;
    Color(Color &&src) noexcept = default;

    Color &operator=(const Color &rhs) = default;
    bool operator==(const Color &rhs) const {
        return getRed() == rhs.getRed() && getGreen() == rhs.getGreen() && getBlue() == rhs.getBlue();
    }
    bool operator!=(const Color &rhs) const { return !(*this == rhs); }

    const binary::Byte getRed() const { return red.getValue(); }
    const binary::Byte getGreen() const { return green.getValue(); }
    const binary::Byte getBlue() const { return blue.getValue(); }
    void write(std::ostream &os) const;

  private:
    binary::Byte red;
    binary::Byte green;
    binary::Byte blue;
};
template <typename T>
Color::Color(const T &red, const T &green, const T &blue)
    : red{binary::Byte(red)}, green{binary::Byte(green)}, blue{binary::Byte(blue)} {}

std::ostream &operator<<(std::ostream &os, const Color &rhs);

using ScanLine = std::vector<Color>;
using ScanLineCollection = std::vector<ScanLine>;
using ScanLineIterator = ScanLineCollection::const_iterator;
using Pixel = Color;
using PixelIterator = ScanLine::const_iterator;
using RPixelIterator = ScanLine::const_reverse_iterator;

class IBitmapIterator {
  public:
    virtual ~IBitmapIterator(){};

    virtual Color getColor() const = 0;
    virtual ScanLineIterator getCurrentScanLine() const = 0;
    virtual ScanLineIterator getStartOfImage() const = 0;
    virtual ScanLineIterator getEndOfImage() const = 0;
    virtual PixelIterator getCurrentPixel() const = 0;

    virtual int getBitmapWidth() const = 0;

    virtual int getBitmapHeight() const = 0;

    virtual int getBitmapNumberOfPadBytes() const = 0;

    virtual bool isEndOfImage() const = 0;

    virtual bool isEndOfScanLine() const = 0;

    virtual bool isStartOfScanLine() const = 0;

    virtual void nextScanLine() = 0;

    virtual void nextPixel() = 0;
};

using HBitmapIterator = std::shared_ptr<IBitmapIterator>;

class Bitmap {
  public:
    Bitmap() = default;
    ~Bitmap() = default;
    Bitmap(int width, int height, std::istream &is = inullstream);
    Bitmap(const Bitmap &src) = default;

    Bitmap &operator=(const Bitmap &rhs) = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getPaddingSize() const { return paddingSize; }

    ScanLineIterator begin() const { return scanLines.begin(); }
    ScanLineIterator end() const { return scanLines.end(); }
    HBitmapIterator createIterator() const;

    void write(std::ostream &os) const;

  private:
    int width{0};
    int height{0};
    ScanLineCollection scanLines;
    int paddingSize{0};

    void readScanLine(std::istream &is);
    void writeScanLine(std::ostream &os, const ScanLine &scanLine) const;

    void readPadding(std::istream &is) const;
    void writePadding(std::ostream &os) const;
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

    int getBitmapWidth() const { return width.getValue(); }
    int getBitmapHeight() const { return height.getValue(); }
    int getFileSize() const { return fileSize.getValue(); }

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
    BitmapIterator(HBitmapIterator &bitmapIter);
    virtual ~BitmapIterator() override;

    int getBitmapWidth() const override;
    int getBitmapHeight() const override;
    int getBitmapNumberOfPadBytes() const override;
    bool isEndOfImage() const override;
    bool isEndOfScanLine() const override;
    bool isStartOfScanLine() const override;
    ScanLineIterator getCurrentScanLine() const override;
    ScanLineIterator getStartOfImage() const override;
    ScanLineIterator getEndOfImage() const override;
    PixelIterator getCurrentPixel() const override;

    virtual Color getColor() const override;
    virtual void nextScanLine() override;
    virtual void nextPixel() override;

  private:
    int width, height, numberOfPadBytes;
    ScanLineIterator currScanLine;
    ScanLineIterator startOfScanLines;
    ScanLineIterator endOfScanLines;
    PixelIterator currPixel;
};

using BitmapIteratorDecorator = BitmapIterator;

class BrightnessDecorator : public BitmapIteratorDecorator {
  public:
    BrightnessDecorator(BitmapIterator innerDecorator, const int adjustment)
        : BitmapIteratorDecorator{innerDecorator}, adjustment{adjustment} {}

    ~BrightnessDecorator() = default;
    BrightnessDecorator(const BrightnessDecorator &bitmapIter) = default;
    BrightnessDecorator(BrightnessDecorator &&src) noexcept = default;
    BrightnessDecorator &operator=(const BrightnessDecorator &rhs) = default;
    BrightnessDecorator &operator=(BrightnessDecorator &&rhs) noexcept = default;

    Color getColor() const final {
        auto color = BitmapIteratorDecorator::getColor();

        ranged_number<int, Color::INF, Color::SUP> red{color.getRed() + adjustment};
        ranged_number<int, Color::INF, Color::SUP> green{color.getGreen() + adjustment};
        ranged_number<int, Color::INF, Color::SUP> blue{color.getBlue() + adjustment};
        return Color{binary::Byte_t(red), binary::Byte_t(green), binary::Byte_t(blue)};
    }

  private:
    int adjustment;
};

class ColorInversionDecorator : public BitmapIteratorDecorator {
  public:
    ColorInversionDecorator(BitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {}
    ~ColorInversionDecorator() = default;

    ColorInversionDecorator(const ColorInversionDecorator &src) = default;
    ColorInversionDecorator(ColorInversionDecorator &&src) noexcept = default;
    ColorInversionDecorator &operator=(const ColorInversionDecorator &rhs) = default;
    ColorInversionDecorator &operator=(ColorInversionDecorator &&rhs) noexcept = default;

    Color getColor() const noexcept final {
        auto color = BitmapIteratorDecorator::getColor();
        auto red = Color::SUP - color.getRed();
        auto green = Color::SUP - color.getGreen();
        auto blue = Color::SUP - color.getBlue();

        return Color{red, green, blue};
    }
};

class RedShiftDecorator : public BitmapIteratorDecorator {
  public:
    RedShiftDecorator(BitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {}
    ~RedShiftDecorator() = default;

    RedShiftDecorator(const RedShiftDecorator &src) = default;
    RedShiftDecorator(RedShiftDecorator &&src) noexcept = default;

    RedShiftDecorator &operator=(const RedShiftDecorator &rhs) = default;
    RedShiftDecorator &operator=(RedShiftDecorator &&rhs) noexcept = default;

    Color getColor() const final {
        auto color = BitmapIteratorDecorator::getColor();

        auto red = double(std::min(int(color.getRed() * 1.33), Color::SUP));
        auto green = color.getGreen() * 0.67;
        auto blue = color.getBlue() * 0.67;

        return Color{red, green, blue};
    }
};

class BlueShiftDecorator : public BitmapIteratorDecorator {
  public:
    BlueShiftDecorator(BitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {}
    ~BlueShiftDecorator() = default;

    BlueShiftDecorator(const BlueShiftDecorator &src) = default;
    BlueShiftDecorator(BlueShiftDecorator &&src) = default;

    BlueShiftDecorator &operator=(const BlueShiftDecorator &rhs) = default;
    BlueShiftDecorator &operator=(BlueShiftDecorator &&rhs) = default;

    Color getColor() const final {
        auto color = BitmapIteratorDecorator::getColor();

        auto red = color.getRed() * 0.67;
        auto green = color.getGreen() * 0.67;
        auto blue = double(std::min(int(color.getBlue() * 1.33), Color::SUP));

        return Color{red, green, blue};
    }
};

class FlipDecorator : public BitmapIteratorDecorator {
  public:
    FlipDecorator(BitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {
        rCurrPixel = getCurrentScanLine()->rbegin();
    }
    ~FlipDecorator() = default;

    FlipDecorator(const FlipDecorator &src) = default;
    FlipDecorator(FlipDecorator &&src) = default;

    FlipDecorator &operator=(const FlipDecorator &rhs) = default;
    FlipDecorator &operator=(FlipDecorator &&rhs) = default;

    Color getColor() const { return *rCurrPixel; }
    void nextPixel() {
        BitmapIteratorDecorator::nextPixel();
        ++rCurrPixel;
    }
    void nextScanLine() {
        BitmapIteratorDecorator::nextScanLine();
        rCurrPixel = getCurrentScanLine()->rbegin();
    }
    PixelIterator getCurrentPixel() const { return rCurrPixel.base(); }

  private:
    RPixelIterator rCurrPixel;
};

class NopDecorator : public BitmapIteratorDecorator {
  public:
    NopDecorator(BitmapIterator innerDecorator) : BitmapIteratorDecorator{innerDecorator} {}
    ~NopDecorator() = default;

    NopDecorator(const NopDecorator &src) = default;
    NopDecorator(NopDecorator &&src) = default;

    NopDecorator &operator=(const NopDecorator &rhs) = default;
    NopDecorator &operator=(NopDecorator &&rhs) = default;
};
} // namespace bitmap

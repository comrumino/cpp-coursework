#pragma once
#include "binary.h"
#include <iostream>
#include <vector>

namespace bitmap {

class Color {
  public:
    static constexpr int SIZEOF = 3; // one byte per color: red, green, blue
    static Color read(std::istream &is) noexcept;

    Color() = default;
    ~Color() = default;
    template <typename T> Color(const T &red, const T &green, const T &blue);
    Color(const Color &src) = default;
    Color(Color &&src) = default;

    Color &operator=(const Color &rhs) = default;
    Color &operator=(Color &&rhs) = default;
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

class Bitmap {
  public:
    using ScanLine = std::vector<Color>;
    using ScanLineCollection = std::vector<ScanLine>;
    using ScanLineIterator = ScanLineCollection::const_iterator;

    Bitmap() = default;
    ~Bitmap() = default;
    Bitmap(int width, int height, std::istream &is);
    Bitmap(const Bitmap &src) = default;
    Bitmap(Bitmap &&src) = default;

    Bitmap &operator=(const Bitmap &rhs) = default;
    Bitmap &operator=(Bitmap &&rhs) = default;

    int getWidth() const noexcept { return width; }
    int getHeight() const noexcept { return height; }
    int getPaddingSize() const noexcept { return myPaddingSize; }
    ScanLineIterator begin() const noexcept { return myScanLines.begin(); }
    ScanLineIterator end() const noexcept { return myScanLines.end(); }
    void write(std::ostream &os) const;

  private:
    int width{0};
    int height{0};
    ScanLineCollection myScanLines;
    int myPaddingSize{0};

    void readScanLine(std::istream &is) noexcept;
    void writeScanLine(std::ostream &os, const ScanLine &scanLine) const;

    void readPadding(std::istream &is) const noexcept;
    void writePadding(std::ostream &os) const noexcept;
};

std::ostream &operator<<(std::ostream &os, const Bitmap &rhs);

template <typename T>
Color::Color(const T &red, const T &green, const T &blue)
    : red{static_cast<binary::Byte>(red)},
      green{static_cast<binary::Byte>(green)},
      blue{static_cast<binary::Byte>(blue)} {}

std::ostream &operator<<(std::ostream &os, const Color &rhs) noexcept;

class WindowsBitmapHeader {
  public:
    WindowsBitmapHeader() = default;
    ~WindowsBitmapHeader() = default;
    WindowsBitmapHeader(std::istream &is) { read(is); }
    WindowsBitmapHeader(const WindowsBitmapHeader &src) = default;
    WindowsBitmapHeader(WindowsBitmapHeader &&src) = default;

    WindowsBitmapHeader &operator=(const WindowsBitmapHeader &rhs) = default;
    WindowsBitmapHeader &operator=(WindowsBitmapHeader &&rhs) = default;

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
    static constexpr binary::Byte firstIdentifier{'B'};
    static constexpr binary::Byte secondIdentifier{'M'};
    binary::DoubleWord fileSize{0};
    static constexpr binary::DoubleWord reserved{0};
    binary::DoubleWord rawImageOffset{0};

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
};
} // namespace bitmap

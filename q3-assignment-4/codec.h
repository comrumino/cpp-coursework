#pragma once
#include "bitmap.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <set>
#include <string>
#include <string_view>

namespace codec {

class IBitmapDecoder;
using HBitmapDecoder = std::shared_ptr<IBitmapDecoder>;
class IBitmapEncoder;
using HBitmapEncoder = std::shared_ptr<IBitmapEncoder>;
static constexpr int HEADER_CHUNK_SIZE = 100; // first n bytes to check if stream is supported

struct MimeType {
    static constexpr std::string_view WINDOWS_BITMAP = "image/x-ms-bmp";
};

class CodecLibrary {
  public:
    CodecLibrary();

    CodecLibrary(const CodecLibrary &src) = default;
    CodecLibrary(CodecLibrary &&src) = default;

    CodecLibrary &operator=(const CodecLibrary &rhs) = default;
    CodecLibrary &operator=(CodecLibrary &&rhs) = default;

    void registerEncoder(const HBitmapEncoder &encoder) noexcept;
    void registerDecoder(const HBitmapDecoder &decoder) noexcept;

    HBitmapEncoder createEncoder(const std::string &mimeType, const bitmap::HBitmapIterator &iter);
    HBitmapDecoder createDecoder(std::istream &inStream);
    HBitmapDecoder createDecoder(const std::string &mimeType, std::istream &inStream);

  private:
    HBitmapEncoder encoder;
    HBitmapDecoder decoder;
    std::set<std::string_view> supportedMimeTypes;
};

class IBitmapDecoder {
  public:
    virtual ~IBitmapDecoder() {}

    virtual HBitmapDecoder clone(std::istream &inStream) = 0;

    virtual bitmap::HBitmapIterator createIterator() const = 0;

    virtual const std::string &getMimeType() const noexcept = 0;

    virtual bool isSupported(const std::string &firstChunkOfBitmap) const noexcept = 0;
};

class IBitmapEncoder {
  public:
    virtual ~IBitmapEncoder() {}

    virtual HBitmapEncoder clone(bitmap::HBitmapIterator it) noexcept = 0;

    virtual void encodeToStream(std::ostream &outStream) const = 0;
};

class WindowsBitmapDecoder : public IBitmapDecoder {
  public:
    WindowsBitmapDecoder();

    virtual ~WindowsBitmapDecoder() = default;

    WindowsBitmapDecoder(const WindowsBitmapDecoder &src) = delete;
    WindowsBitmapDecoder(WindowsBitmapDecoder &&src) = delete;

    WindowsBitmapDecoder &operator=(const WindowsBitmapDecoder &rhs) = delete;
    WindowsBitmapDecoder &operator=(WindowsBitmapDecoder &&rhs) = delete;

    virtual HBitmapDecoder clone(std::istream &inStream) override;

    virtual bitmap::HBitmapIterator createIterator() const override;

    virtual const std::string &getMimeType() const noexcept override;

    virtual bool isSupported(const std::string &firstChunkOfBitmap) const noexcept override;

  private:
    std::stringstream stream;
    const std::string mimeType;
    std::unique_ptr<bitmap::Bitmap> bitmap;
};
class WindowsBitmapEncoder : public IBitmapEncoder {
  public:
    WindowsBitmapEncoder() = default;
    virtual ~WindowsBitmapEncoder() = default;

    WindowsBitmapEncoder(const WindowsBitmapEncoder &src) = delete;
    WindowsBitmapEncoder(WindowsBitmapEncoder &&src) = delete;

    WindowsBitmapEncoder &operator=(const WindowsBitmapEncoder &rhs) = delete;
    WindowsBitmapEncoder &operator=(WindowsBitmapEncoder &&rhs) = delete;

    virtual HBitmapEncoder clone(bitmap::HBitmapIterator it) noexcept;

    virtual void encodeToStream(std::ostream &outStream) const;

  private:
    void encodeHeader(std::ostream &outStream) const;
    void encodePayload(std::ostream &outStream) const;

    bitmap::HBitmapIterator it;
};

} // namespace codec

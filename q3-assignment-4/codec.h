#pragma once
#include "bitmap.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <sstream>
#include <string>
#include <string_view>

namespace codec {

class IBitmapDecoder;
using HBitmapDecoder = std::shared_ptr<IBitmapDecoder>;
class IBitmapEncoder;
using HBitmapEncoder = std::shared_ptr<IBitmapEncoder>;
static constexpr int HEADER_CHUNK_SIZE = 100; // first n bytes to check if stream is supported
using mime_map = std::unordered_map<std::string_view, std::string_view>;

struct MimeType {
    static constexpr std::string_view WINDOWS_BITMAP = "image/x-ms-bmp";
};

static const mime_map SUPPORTED = {{MimeType::WINDOWS_BITMAP, MimeType::WINDOWS_BITMAP}, };

class CodecLibrary {
  public:
    CodecLibrary(const mime_map &supportedMimeTypes = SUPPORTED);

    CodecLibrary(const CodecLibrary &src) = default;
    CodecLibrary(CodecLibrary &&src) = default;

    CodecLibrary &operator=(const CodecLibrary &rhs) = default;
    CodecLibrary &operator=(CodecLibrary &&rhs) = default;
    bool isSupported( std::istream &inStream) const;

    void registerEncoder(const HBitmapEncoder &encoder);
    void registerDecoder(const HBitmapDecoder &decoder);

    HBitmapEncoder createEncoder(const std::string &mimeType, const bitmap::HBitmapIterator &iter);
    HBitmapDecoder createDecoder(std::istream &inStream);
    HBitmapDecoder createDecoder(const std::string &mimeType, std::istream &inStream);

  private:
    HBitmapEncoder encoder;
    HBitmapDecoder decoder;
    std::unordered_map<std::string_view, std::string_view> supportedMimeTypes;
};

class IBitmapDecoder {
  public:
    virtual ~IBitmapDecoder() {}

    virtual HBitmapDecoder clone(std::istream &inStream) = 0;

    virtual bitmap::HBitmapIterator createIterator() const = 0;

    virtual const std::string &getMimeType() const = 0;

    virtual bool isSupported(const std::string &firstChunkOfBitmap) const = 0;
};

class IBitmapEncoder {
  public:
    virtual ~IBitmapEncoder() {}

    virtual HBitmapEncoder clone(bitmap::HBitmapIterator it) = 0;

    virtual void encodeToStream(std::ostream &outStream) const = 0;
};

class WindowsBitmapDecoder : public IBitmapDecoder {
  public:
    WindowsBitmapDecoder();
    ~WindowsBitmapDecoder() final = default;

    WindowsBitmapDecoder(const WindowsBitmapDecoder &src) = delete;
    WindowsBitmapDecoder(WindowsBitmapDecoder &&src) = delete;

    WindowsBitmapDecoder &operator=(const WindowsBitmapDecoder &rhs) = delete;
    WindowsBitmapDecoder &operator=(WindowsBitmapDecoder &&rhs) = delete;

    HBitmapDecoder clone(std::istream &inStream) final;

    bitmap::HBitmapIterator createIterator() const final;

    const std::string &getMimeType() const final;

    bool isSupported(const std::string &firstChunkOfBitmap) const final;

  private:
    std::stringstream stream;
    const std::string mimeType;
    std::unique_ptr<bitmap::Bitmap> bitmap;
};
class WindowsBitmapEncoder : public IBitmapEncoder {
  public:
    WindowsBitmapEncoder() = default;
    ~WindowsBitmapEncoder() final = default;

    WindowsBitmapEncoder(const WindowsBitmapEncoder &src) = delete;
    WindowsBitmapEncoder(WindowsBitmapEncoder &&src) = delete;

    WindowsBitmapEncoder &operator=(const WindowsBitmapEncoder &rhs) = delete;
    WindowsBitmapEncoder &operator=(WindowsBitmapEncoder &&rhs) = delete;

    HBitmapEncoder clone(bitmap::HBitmapIterator it) final;

    void encodeToStream(std::ostream &outStream) const final;

  private:
    void encodeHeader(std::ostream &outStream) const;
    void encodePayload(std::ostream &outStream) const;

    bitmap::HBitmapIterator it;
};

} // namespace codec

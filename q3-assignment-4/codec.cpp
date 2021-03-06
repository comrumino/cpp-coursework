#include "codec.h"
#include "bitmap.h"
#include <string>

#include <iostream>
#include <memory>
#include <sstream>

namespace codec {

CodecLibrary::CodecLibrary(const mime_map &supportedMimeTypes) : supportedMimeTypes{supportedMimeTypes} {}

void CodecLibrary::registerEncoder(const HBitmapEncoder &encoder_) { encoder = encoder_; }

void CodecLibrary::registerDecoder(const HBitmapDecoder &decoder_) { decoder = decoder_; }

HBitmapEncoder CodecLibrary::createEncoder(const std::string &mimeType, const bitmap::HBitmapIterator &iter) {
    if (supportedMimeTypes.find(mimeType) == supportedMimeTypes.end()) {
        throw std::runtime_error{"Invalid mimeType"};
    } else {
        return encoder->clone(iter);
    }
}

bool CodecLibrary::isSupported(std::istream &inStream) const {
    // inStream.exceptions(std::ios::failbit | std::ios::badbit);
    std::string s;
    char c;
    for (int i = 0; i < HEADER_CHUNK_SIZE; i++) {
        inStream.seekg(i);
        c = inStream.peek();
        if (c == EOF) {
            break;
        } else {
            s += c;
        }
    }
    inStream.seekg(0);
    return decoder->isSupported(s);
}

HBitmapDecoder CodecLibrary::createDecoder(std::istream &inStream) {
    if (!isSupported(inStream)) {
        throw std::runtime_error{"Malformed or unsupported istream"};
    } else {
        return decoder->clone(inStream);
    }
}

HBitmapDecoder CodecLibrary::createDecoder(const std::string &mimeType, std::istream &inStream) {
    if (supportedMimeTypes.find(mimeType) == supportedMimeTypes.end()) {
        throw std::runtime_error{"Invalid mimeType"};
    } else {
        return decoder->clone(inStream);
    }
}

WindowsBitmapDecoder::WindowsBitmapDecoder() : mimeType{MimeType::WINDOWS_BITMAP} {}

HBitmapDecoder WindowsBitmapDecoder::clone(std::istream &inStream) {
    auto result = std::make_shared<WindowsBitmapDecoder>();
    result->stream << inStream.rdbuf();

    if (!result->stream.str().empty()) {
        if (!isSupported(result->stream.str().substr(0, HEADER_CHUNK_SIZE))) {
            throw std::runtime_error{"unsupported format"};
        }

        bitmap::WindowsBitmapHeader header{result->stream};
        result->bitmap = std::make_unique<bitmap::Bitmap>(
            bitmap::Bitmap{header.getBitmapWidth(), header.getBitmapHeight(), result->stream});
    }

    return result;
}

bitmap::HBitmapIterator WindowsBitmapDecoder::createIterator() const {
    if (bitmap == nullptr) {
        throw std::runtime_error{"Invalid bitmap"};
    }

    auto it = bitmap::BitmapIterator{*bitmap};
    return std::make_shared<bitmap::BitmapIterator>(it);
}

const std::string &WindowsBitmapDecoder::getMimeType() const { return mimeType; }

bool WindowsBitmapDecoder::isSupported(const std::string &firstChunkOfBitmap) const {
    return firstChunkOfBitmap[0] == 'B' && firstChunkOfBitmap[1] == 'M';
}

HBitmapEncoder WindowsBitmapEncoder::clone(bitmap::HBitmapIterator it) {
    auto result = std::make_shared<WindowsBitmapEncoder>();
    result->it = it;
    return result;
}

void WindowsBitmapEncoder::encodeToStream(std::ostream &outStream) const {
    if (it == nullptr) {
        throw std::runtime_error{"Invalid iterator"};
    } else {
        encodeHeader(outStream);
        encodePayload(outStream);
    }
}

void WindowsBitmapEncoder::encodeHeader(std::ostream &outStream) const {
    bitmap::WindowsBitmapHeader header{static_cast<DoubleWord_t>(it->getBitmapWidth()),
                                       static_cast<DoubleWord_t>(it->getBitmapHeight())};
    header.write(outStream);
}

void WindowsBitmapEncoder::encodePayload(std::ostream &outStream) const {
    for (auto i = it; !i->isEndOfImage(); i->nextScanLine()) {
        for (; !i->isEndOfScanLine(); i->nextPixel()) {
            outStream << i->getColor();
        }

        Byte padByte{0};
        for (int pad = 0u; pad < i->getBitmapNumberOfPadBytes(); ++pad) {
            outStream << padByte;
        }
    }
}

} // namespace codec

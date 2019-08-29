#pragma once
#include "endian.h"
#include <cstdint>
#include <iostream>

namespace binary {

template <typename T> class Binary_t {
  public:
    static constexpr int SIZEOF{sizeof(T)};
    static Binary_t read(std::istream &is, const endian &&endianness = endian::native);
    static Binary_t readLittleEndian(std::istream &is);
    static Binary_t readBigEndian(std::istream &is);

    Binary_t() = default;
    ~Binary_t() = default;
    constexpr Binary_t(T value) : bvalue{value} {} // non-explicit
    Binary_t(const Binary_t &src) = default;
    Binary_t(Binary_t &&src) noexcept = default;
    Binary_t &operator=(const Binary_t &rhs) = default;
    Binary_t &operator=(Binary_t &&rhs) noexcept = default;
    Binary_t &operator=(const T &value);

    operator T() const noexcept { return bvalue; }
    bool operator==(const Binary_t &rhs) const noexcept { return bvalue == rhs.bvalue; }
    bool operator!=(const Binary_t &rhs) const noexcept { return !(bvalue == rhs.bvalue); }
    bool operator==(const T &rhs) const noexcept { return bvalue == rhs; }
    template <typename T2> bool operator!=(const T2 &rhs) const noexcept { return !(bvalue == rhs); }

    const T getValue() const noexcept { return bvalue; };
    void write(std::ostream &os, const endian &&endianess = endian::native) const;
    void writeLittleEndian(std::ostream &os) const;
    void writeBigEndian(std::ostream &os) const;

  private:
    T bvalue{0};
};

using Byte_t = uint8_t;
using Word_t = uint16_t;
using DoubleWord_t = uint32_t;
using Byte = Binary_t<Byte_t>;
using Word = Binary_t<Word_t>;
using DoubleWord = Binary_t<DoubleWord_t>;
static constexpr int OCTET = 8; // 8 bits in an octet
static constexpr Byte_t BIT_MASK = static_cast<Byte_t>((1 << (OCTET + 1)) - 1);

template <typename T> Binary_t<T> &Binary_t<T>::operator=(const T &value) {
    bvalue = static_cast<T>(value);
    return *this;
}

template <typename T> Binary_t<T> Binary_t<T>::read(std::istream &is, const endian &&endianess) {
    if (!is) {
        throw std::runtime_error{"Invalid istream"};
    } else if (endianess == endian::little) {
        return readLittleEndian(is);
    } else if (endianess == endian::big) {
        return readBigEndian(is);
    } else {
        throw std::invalid_argument{"Not implemented endian provided as argument"};
    }
}

template <typename T> Binary_t<T> Binary_t<T>::readLittleEndian(std::istream &is) {
    char c = 'a';
    T result = 0;
    for (int idx = 0, shift = 0; idx < Binary_t<T>::SIZEOF; ++idx) {
        is.get(c);
        shift = idx * OCTET;
        result |= static_cast<Byte_t>(c) << shift;
    }
    return Binary_t<T>{result};
}

template <typename T> Binary_t<T> Binary_t<T>::readBigEndian(std::istream &is) {
    char c = 'a';
    T result = 0;
    for (int idx = 0, shift = 0; idx < Binary_t<T>::SIZEOF; ++idx) {
        is.get(c);
        shift = (Binary_t<T>::SIZEOF - 1 - idx) * OCTET;
        result |= static_cast<Byte_t>(c) << shift;
    }
    return Binary_t<T>{result};
}

template <typename T> void Binary_t<T>::write(std::ostream &os, const endian &&endianess) const {
    if (!os) {
        throw std::runtime_error{"Invalid ostream"};
    } else if (endianess == endian::little) {
        writeLittleEndian(os);
    } else if (endianess == endian::big) {
        writeBigEndian(os);
    } else {
        throw std::invalid_argument{"Not implemented endian provided as argument"};
    }
}

template <typename T> void Binary_t<T>::writeLittleEndian(std::ostream &os) const {
    for (int idx = 0, shift = 0; idx < Binary_t<T>::SIZEOF; ++idx) {
        shift = idx * OCTET;
        Byte_t value = (bvalue & BIT_MASK << shift) >> shift;
        os << value;
    }
}

template <typename T> void Binary_t<T>::writeBigEndian(std::ostream &os) const {
    for (int idx = 0, shift = 0; idx < Binary_t<T>::SIZEOF; ++idx) {
        shift = (Binary_t<T>::SIZEOF - 1 - idx) * OCTET;
        Byte_t value = (bvalue & BIT_MASK << shift) >> shift;
        os << value;
    }
}

template <typename T> std::ostream &operator<<(std::ostream &os, const Binary_t<T> &rhs) {
    rhs.write(os);
    return os;
}

template <typename T, typename T2> void verifyEquality(T &&expected, T2 &&actual, const char *msg) {
    if (expected != actual)
        throw std::runtime_error{msg};
}

template <class T, class CharT = char, class Traits = std::char_traits<CharT>>
class binary_ostream_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void> {
  public:
    typedef std::basic_ostream<CharT, Traits> ostream_type;
    typedef Traits traits_type;
    typedef CharT char_type;

    binary_ostream_iterator(ostream_type &stream) : bstream(stream) {}

    binary_ostream_iterator &operator=(T const &value) {
        value.write(bstream);
        if (!bstream) {
            throw std::runtime_error{"Invalid stream"};
        }
        return *this;
    }
    binary_ostream_iterator &operator*() { return *this; }
    binary_ostream_iterator &operator++() { return *this; }
    binary_ostream_iterator &operator++(int) { return *this; }

  protected:
    ostream_type &bstream;
};

} // namespace binary

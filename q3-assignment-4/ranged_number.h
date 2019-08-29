#pragma once
#include <algorithm>

template <typename T, T greatestLowerBound, T leastUpperBound> class ranged_number {
  public:
    ranged_number() = default;
    ranged_number(const T &value);
    ~ranged_number() = default;
    ranged_number(const ranged_number &src) = default;
    ranged_number(ranged_number &&src) = default;
    ranged_number &operator=(const ranged_number &rhs) = default;
    ranged_number &operator=(ranged_number &&rhs) = default;
    const T &getValue() const noexcept;
    operator T();

    const ranged_number &operator++() noexcept;
    const ranged_number operator++(int) noexcept;
    const ranged_number &operator--() noexcept;
    const ranged_number operator--(int) noexcept;
    const ranged_number &operator+=(const ranged_number &rhs) noexcept;
    const ranged_number &operator+=(ranged_number &&rhs) noexcept;
    const ranged_number &operator-=(const ranged_number &rhs) noexcept;
    const ranged_number &operator-=(ranged_number &&rhs) noexcept;

  private:
    T value;
};

template <typename T, T leastLowerBound, T leastUpperBound>
ranged_number<T, leastLowerBound, leastUpperBound>::ranged_number(const T &value)
    : value{std::clamp(value, leastLowerBound, leastUpperBound)} {}

template <typename T, T leastLowerBound, T leastUpperBound>
const T &ranged_number<T, leastLowerBound, leastUpperBound>::getValue() const noexcept {
    return value;
}

template <typename T, T leastLowerBound, T leastUpperBound>
ranged_number<T, leastLowerBound, leastUpperBound>::operator T() {
    return value;
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> &ranged_number<T, leastLowerBound, leastUpperBound>::
operator++() noexcept {
    value = std::clamp<T>(value + 1, leastLowerBound, leastUpperBound);
    return *this;
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> ranged_number<T, leastLowerBound, leastUpperBound>::
operator++(int) noexcept {
    auto beforeIncrement = *this;
    operator++();
    return std::move(beforeIncrement);
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> &ranged_number<T, leastLowerBound, leastUpperBound>::
operator--() noexcept {
    value = std::clamp<T>(value - 1, leastLowerBound, leastUpperBound);
    return *this;
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> ranged_number<T, leastLowerBound, leastUpperBound>::
operator--(int) noexcept {
    auto beforeDecrement = *this;
    operator--();
    return std::move(beforeDecrement);
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> &ranged_number<T, leastLowerBound, leastUpperBound>::
operator+=(const ranged_number &rhs) noexcept {
    value = std::clamp<T>(value + rhs.getValue(), leastLowerBound, leastUpperBound);
    return *this;
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> &ranged_number<T, leastLowerBound, leastUpperBound>::
operator+=(ranged_number &&rhs) noexcept {
    value = std::clamp<T>(value + rhs.getValue(), leastLowerBound, leastUpperBound);
    return *this;
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> &ranged_number<T, leastLowerBound, leastUpperBound>::
operator-=(const ranged_number &rhs) noexcept {
    value = std::clamp<T>(value - rhs.getValue(), leastLowerBound, leastUpperBound);
    return *this;
}

template <typename T, T leastLowerBound, T leastUpperBound>
const ranged_number<T, leastLowerBound, leastUpperBound> &ranged_number<T, leastLowerBound, leastUpperBound>::
operator-=(ranged_number &&rhs) noexcept {
    value = std::clamp<T>(value - rhs.getValue(), leastLowerBound, leastUpperBound);
    return *this;
}

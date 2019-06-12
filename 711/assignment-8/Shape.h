#pragma once

#include <ostream>

class Shape
{
public:
    Shape() = default;  

    Shape(const Shape& src) = delete;
    Shape& operator=(const Shape& rhs) = delete;

    virtual ~Shape() = default;  // Passes through to derived class destructor

    virtual void draw(std::ostream& os) const = 0;  // pure virtual => abstract-base => only derived class can construct

    virtual void stream(std::ostream& os) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
    shape.stream(os);
    return os;
}

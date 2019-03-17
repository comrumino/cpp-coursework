#pragma once

#include <ostream>

class Shape
{
public:
    // only a derived class ca
    // 
    Shape() = default;  

    Shape(const Shape& src) = delete;
    Shape& operator=(const Shape& rhs) = delete;

    virtual ~Shape() = default;  // Passes through to derived class destructor

    virtual void draw(std::ostream& os) const = 0;  // pure virtual function

    virtual void stream(std::ostream& os) const = 0;  // pure virtual function
};

inline std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
    shape.stream(os);
    return os;
}

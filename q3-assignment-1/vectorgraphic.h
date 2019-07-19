#pragma once
#include <vector>
#include "point.h"
using Points = std::vector<Point>;

class VectorGraphic {
    public:
        VectorGraphic();
        ~VectorGraphic();

        void addPoint(const Point& p);    
        void removePoint(const Point& p);
        void erasePoint(int index);

        void openShape();
        void closeShape();

        bool isOpen() const;
        bool isClosed() const;

        int getWidth() const;
        int getHeight() const;

        int getPointCount() const;
        Point getPoint(int index) const;

    private:
        Points myPath;

        // ...
};

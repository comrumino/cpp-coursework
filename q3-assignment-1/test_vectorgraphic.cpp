#include "TestHarness.h"
#include "point.h"
#include "vectorgraphic.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

TEST(VectorGraphic, count) {
    VectorGraphic vector_graphic;
    CHECK_EQUAL(0, vector_graphic.getPointCount());
}


TEST(VectorGraphic, add_point) {
    Points points{Point(0, 0), Point(0, 1), Point(1, 0)};
    VectorGraphic vector_graphic;
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
        CHECK_EQUAL(i + 1, vector_graphic.getPointCount());
    }
}

TEST(VectorGraphic, get_point) {
    Point point(1, 2);
    VectorGraphic vector_graphic;
    bool caught = false;
    try {
        vector_graphic.getPoint(0);   
    } catch (...) {
        caught = true;
    }
    CHECK_EQUAL(true, caught);
    vector_graphic.addPoint(point);
    CHECK_EQUAL(point, vector_graphic.getPoint(0));
}

TEST(VectorGraphic, remove_point) {
    Points points{Point(0, 0), Point(0, 1), Point(1, 0)};
    VectorGraphic vector_graphic;
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
    }
    for (int i = 0; i < points.size(); ++i) {
        CHECK_EQUAL(points[i], vector_graphic.getPoint(i));
    }
    CHECK_EQUAL(points.size(), vector_graphic.getPointCount());
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.removePoint(points[i]);
        if (i == points.size() - 1) {
            CHECK_EQUAL(0, vector_graphic.getPointCount());
        } else {
            CHECK_EQUAL(points[i+1], vector_graphic.getPoint(0));
        }
    }
    // re-populate
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
    }
    // remove point (0, 1) then (0, 0)
    for (int i = points.size() - 1; i >= 0; --i) {
        vector_graphic.removePoint(points[i]);
        if (i == 0) {
            CHECK_EQUAL(0, vector_graphic.getPointCount());
        } else {
            CHECK_EQUAL(points[i-1], vector_graphic.getPoint(-1));
        }
    }
}

TEST(VectorGraphic, erase_point ) {
    Points points{Point(0, 0), Point(0, 1), Point(1, 0)};
    VectorGraphic vector_graphic;
    bool caught = false;
    try {
        vector_graphic.erasePoint(0);   
    } catch (...) {
        caught = true;
    }
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
    }
    CHECK_EQUAL(points.size(), vector_graphic.getPointCount());
    for (int i = points.size() - 1; i >= 0; --i) {
        vector_graphic.erasePoint(i);
        if (i == 0) {
            CHECK_EQUAL(0, vector_graphic.getPointCount());
        } else {
            CHECK_EQUAL(points[i-1], vector_graphic.getPoint(-1));
        }
    }
}


TEST(VectorGraphic, open_close ) {
    VectorGraphic vector_graphic;
    CHECK_EQUAL(false, vector_graphic.isOpen());
    CHECK_EQUAL(true, vector_graphic.isClosed());
    vector_graphic.openShape();
    CHECK_EQUAL(true, vector_graphic.isOpen());
    CHECK_EQUAL(false, vector_graphic.isClosed());
    vector_graphic.closeShape();
    CHECK_EQUAL(false, vector_graphic.isOpen());
    CHECK_EQUAL(true, vector_graphic.isClosed());
}

TEST(VectorGraphic, get_width_height) {
    VectorGraphic vector_graphic;
    // powers of 2 and powers 3 are relatively prime, so this is good enough
    Points points{Point(0, 0), Point(2, 3), Point(4, 9)};
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
        std::cout << vector_graphic.getPoint(i) << std::endl;
        CHECK_EQUAL(!i ? i : std::pow(2, i), vector_graphic.getWidth());
        CHECK_EQUAL(!i ? i : std::pow(3, i), vector_graphic.getHeight());
    }
    for (int i = points.size() - 1; i >= 0; --i) {
        std::cout << vector_graphic.getPoint(i) << std::endl;
        CHECK_EQUAL(!i ? i : std::pow(2, i), vector_graphic.getWidth());
        CHECK_EQUAL(!i ? i : std::pow(3, i), vector_graphic.getHeight());
        vector_graphic.erasePoint(i);
    }
}

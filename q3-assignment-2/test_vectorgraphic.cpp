#include "TestHarness.h"
#include "point.h"
#include "vectorgraphic.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

TEST(VectorGraphic, count) {
    geom::VectorGraphic vector_graphic;
    CHECK_EQUAL(0, vector_graphic.getPointCount());
}
TEST(VectorGraphic, add_point) {
    geom::Points points{geom::Point(0, 0), geom::Point(0, 1), geom::Point(1, 0)};
    geom::VectorGraphic vector_graphic;
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
        CHECK_EQUAL(i + 1, vector_graphic.getPointCount());
    }
}
TEST(VectorGraphic, get_point) {
    geom::Point point(1, 2);
    geom::VectorGraphic vector_graphic;
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
    geom::Points points{geom::Point(0, 0), geom::Point(0, 1), geom::Point(1, 0)};
    geom::Point outside_point(1, 1);
    geom::VectorGraphic vector_graphic;
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
    }
    for (int i = 0; i < points.size(); ++i) {
        CHECK_EQUAL(points[i], vector_graphic.getPoint(i));
    }
    CHECK_EQUAL(points.size(), vector_graphic.getPointCount());
    // attempt to remove point not in vector_graphic
    bool caught = false;
    try {
        vector_graphic.removePoint(outside_point);
    } catch (...) {
        caught = true;
    }
    CHECK_EQUAL(false, caught);
    // remove points in vector graphic
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.removePoint(points[i]);
        if (i == points.size() - 1) {
            CHECK_EQUAL(0, vector_graphic.getPointCount());
        } else {
            CHECK_EQUAL(points[i + 1], vector_graphic.getPoint(0));
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
            CHECK_EQUAL(points[i - 1], vector_graphic.getPoint(vector_graphic.getPointCount() - 1));
        }
    }
}

TEST(VectorGraphic, erase_point) {
    geom::Points points{geom::Point(0, 0), geom::Point(0, 1), geom::Point(1, 0)};
    geom::VectorGraphic vector_graphic;
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
            CHECK_EQUAL(points[i - 1], vector_graphic.getPoint(vector_graphic.getPointCount() - 1));
        }
    }
}
TEST(VectorGraphic, open_close) {
    geom::VectorGraphic vector_graphic;
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
    geom::VectorGraphic vector_graphic;
    // powers of 2 and powers 3 are relatively prime, so this is good enough
    geom::Points points{geom::Point(0, 0), geom::Point(2, 3), geom::Point(4, 9)};
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
        CHECK_EQUAL(!i ? i : std::pow(2, i), vector_graphic.getWidth());
        CHECK_EQUAL(!i ? i : std::pow(3, i), vector_graphic.getHeight());
    }
    std::stringstream ss;
    ss << vector_graphic;
    std::string exp = "<VectorGraphic closed=\"true\">\n"
                      "<Point x=\"0\" y=\"0\"/>\n"
                      "<Point x=\"2\" y=\"3\"/>\n"
                      "<Point x=\"4\" y=\"9\"/>\n"
                      "</VectorGraphic>";
    CHECK_EQUAL(ss.str(), exp);
    for (int i = points.size() - 1; i >= 0; --i) {
        CHECK_EQUAL(!i ? i : std::pow(2, i), vector_graphic.getWidth());
        CHECK_EQUAL(!i ? i : std::pow(3, i), vector_graphic.getHeight());
        vector_graphic.erasePoint(i);
    }
}
TEST(VectorGraphic, get_width_height_negatives) {
    // check negatives are okay
    geom::VectorGraphic vector_graphic;
    geom::Points points{geom::Point(-1, -1), geom::Point(1, 1)};
    for (int i = 0; i < points.size(); ++i) {
        vector_graphic.addPoint(points[i]);
    }
    CHECK_EQUAL(2, vector_graphic.getPointCount());
    CHECK_EQUAL(2, vector_graphic.getWidth());
    CHECK_EQUAL(2, vector_graphic.getHeight());
}
TEST(VectorGraphic, stream_operator) {
    geom::VectorGraphic vector_graphic;
    std::stringstream ss;
    vector_graphic.addPoint(geom::Point());
    vector_graphic.closeShape();
    ss << vector_graphic.get_human_readable();
    std::string exp = "VectorGraphic is closed and has points:\n"
                      "  (0, 0)\n";
    CHECK_EQUAL(ss.str(), exp);
    ss.str("");
    vector_graphic.openShape();
    ss << vector_graphic.get_human_readable();
    exp = "VectorGraphic is not closed and has points:\n"
          "  (0, 0)\n";
    CHECK_EQUAL(ss.str(), exp);
    ss.str("");
    vector_graphic.erasePoint(0);
    ss << vector_graphic.get_human_readable();
    exp = "VectorGraphic is not closed and does not have points.\n";
    CHECK_EQUAL(ss.str(), exp);
}
/*
// provided unit tests
TEST(ctor, VectorGraphic) {
 geom::VectorGraphic vg;
 CHECK_EQUAL(0, vg.getPointCount());
 CHECK_EQUAL(true, vg.isClosed());
 CHECK_EQUAL(false, vg.isOpen());
}

TEST(insertPoint, VectorGraphic)
{
 geom::VectorGraphic vg;
    vg.addPoint(geom::Point{1, 1});
 CHECK_EQUAL(1, vg.getPointCount());

    vg.addPoint(geom::Point{2, 2});
 CHECK_EQUAL(2, vg.getPointCount());
}

TEST(removePoint, VectorGraphic)
{
 geom::VectorGraphic vg;
    vg.addPoint(geom::Point{1, 1});
    vg.addPoint(geom::Point{2, 2});
    vg.removePoint(geom::Point{1, 1});

 CHECK_EQUAL(1, vg.getPointCount());
 CHECK_EQUAL(geom::Point(2, 2), vg.getPoint(0));
}

TEST(erasePoint, VectorGraphic)
{
 geom::VectorGraphic vg;
    vg.addPoint(geom::Point{1, 1});
    vg.addPoint(geom::Point{2, 2});
    vg.addPoint(geom::Point{3, 3});
 vg.erasePoint(1);

 CHECK_EQUAL(2, vg.getPointCount());
 CHECK_EQUAL(geom::Point(1, 1), vg.getPoint(0));
 CHECK_EQUAL(geom::Point(3, 3), vg.getPoint(1));
}

TEST(erasePointOutOfRange, VectorGraphic)
{
 geom::VectorGraphic vg;
    vg.addPoint(geom::Point{1, 1});
    vg.addPoint(geom::Point{2, 2});
    vg.addPoint(geom::Point{3, 3});

    try
    {
     vg.erasePoint(5);
    }
    catch (std::out_of_range&)
    {
        CHECK_EQUAL(3, vg.getPointCount());
        return;
    }
 CHECK(false); // should have caught exception
}

TEST(equality, VectorGraphic)
{
 geom::VectorGraphic vg1;
    vg1.addPoint(geom::Point{1, 1});
    vg1.addPoint(geom::Point{2, 2});
    vg1.addPoint(geom::Point{3, 3});

 geom::VectorGraphic vg2;
    vg2.addPoint(geom::Point{1, 1});
    vg2.addPoint(geom::Point{2, 2});
    vg2.addPoint(geom::Point{3, 3});

 CHECK(vg1 == vg2);
}

TEST(inequality, VectorGraphic)
{
 geom::VectorGraphic vg1;
    vg1.addPoint(geom::Point{1, 1});
    vg1.addPoint(geom::Point{1, 2});
    vg1.addPoint(geom::Point{1, 3});

 geom::VectorGraphic vg2;
    vg2.addPoint(geom::Point{2, 1});
    vg2.addPoint(geom::Point{2, 2});
    vg2.addPoint(geom::Point{2, 3});

 CHECK(vg1 != vg2);

    geom::VectorGraphic vg3;
    vg3.addPoint(geom::Point{1, 1});
    vg3.addPoint(geom::Point{1, 2});
    vg3.addPoint(geom::Point{1, 3});
    vg3.openShape();

    CHECK(vg3 != vg1);
}
TEST(closeShape, VectorGraphic) {
 geom::VectorGraphic vg;
 vg.closeShape();
 CHECK_EQUAL(true, vg.isClosed());
 CHECK_EQUAL(false, vg.isOpen());
}
TEST(openShape, VectorGraphic) {
 geom::VectorGraphic vg;
 vg.openShape();
 CHECK_EQUAL(false, vg.isClosed());
 CHECK_EQUAL(true, vg.isOpen());
}
TEST(widthHeight, VectorGraphic) {
    geom::VectorGraphic vectorGraphic;
    vectorGraphic.addPoint(geom::Point{0, 2});
    vectorGraphic.addPoint(geom::Point{4, 3});
    vectorGraphic.addPoint(geom::Point{5, 8});
    vectorGraphic.addPoint(geom::Point{2, 1});
    CHECK_EQUAL(5, vectorGraphic.getWidth());
    CHECK_EQUAL(7, vectorGraphic.getHeight());

    vectorGraphic.erasePoint(2);
    CHECK_EQUAL(4, vectorGraphic.getWidth());
    CHECK_EQUAL(2, vectorGraphic.getHeight());
}
*/

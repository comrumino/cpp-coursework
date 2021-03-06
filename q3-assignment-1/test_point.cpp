#include "TestHarness.h"
#include "point.h"
#include <iostream>
#include <sstream>
#include <string>

TEST(Point, stream_operator) { // verify trivial class, streams as expected
    Point pt(0, 1);
    std::stringstream ss;
    ss << pt;
    CHECK_EQUAL("<Point x=\"0\" y=\"1\"/>", ss.str());
}

TEST(Point, direct_ctor) {
    Point pt(1, 0);
    std::stringstream ss;
    ss << pt;
    CHECK_EQUAL("<Point x=\"1\" y=\"0\"/>", ss.str());
}

TEST(Point, default_ctor) {
    Point pt; // reminder, Point pt() is a vexing parse
    std::stringstream ss;
    ss << pt;
    CHECK_EQUAL("<Point x=\"0\" y=\"0\"/>", ss.str());
}

TEST(Point, copy_ctor) {
    Point pt(1, 1);
    Point pt2 = pt;
    std::stringstream ss;
    ss << pt2;
    CHECK_EQUAL("<Point x=\"1\" y=\"1\"/>", ss.str());
}

TEST(Point, move_ctor) {
    Point pt(2, 0);
    Point pt2 = std::move(pt);
    std::stringstream ss;
    ss << pt2;
    CHECK_EQUAL("<Point x=\"2\" y=\"0\"/>", ss.str());
}

TEST(Point, equality) {
    Point pt0(0, 0);
    Point pt1(0, 1);
    Point pt2(1, 0);
    // Both directions to show reflexive
    CHECK_EQUAL(0, pt0 == pt1);
    CHECK_EQUAL(0, pt1 == pt0);
    CHECK_EQUAL(0, pt0 == pt2);
    CHECK_EQUAL(0, pt2 == pt0);
    CHECK_EQUAL(0, pt1 == pt2);
    CHECK_EQUAL(0, pt2 == pt1);
    CHECK_EQUAL(1, pt0 == pt0);
    CHECK_EQUAL(1, pt1 == pt1);
}

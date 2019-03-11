/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 7.1 Probe
 *  Problem Statement:
 *   + Define a probe that can be inserted into a class as a test coverage device. The probe keeps track of the
 *     number of instances of the class that currently exist and how many have been created since the program was
 *     started. The probe is to respond with appropriate tracking information when the class instance containing
 *     the probe is queried. It will be necessary to figure out the best way to present the query. Demonstrate your
 *     probe on a class with multiple instances. Note: the data and function members of the probe cannot be static.
 *     The probe itself must be declared static in the probed class.
 *   + Overload the ostream operator to support printing of information of the class Probe.
 *   + Use the delete keyword to delete the copy constructor and assignment operator for the probe. (see Section 13.1.6 in Lippman)
 */
#include "TestHarness.h"
#include "probe.h"
#include <iostream>
#include <sstream>

TEST(Probe, ctor_dtor) {
    Overhead ovrhd0 = Overhead();
    std::stringstream res_probe;
    auto dlambda = [&]() {
        Overhead ovrhd1 = Overhead();
        Overhead ovrhd2 = Overhead();
        Overhead ovrhd3 = Overhead();
        res_probe << ovrhd0.probe;
        CHECK_EQUAL("target_cls: overhead\nctor_calls: 4\ndtor_calls: 0\ninst_count: 4\n", res_probe.str());
    };
    dlambda();
    res_probe.str("");
    res_probe << ovrhd0.probe;
    CHECK_EQUAL("target_cls: overhead\nctor_calls: 4\ndtor_calls: 3\ninst_count: 1\n", res_probe.str());
}

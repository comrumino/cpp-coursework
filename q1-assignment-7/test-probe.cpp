#include "TestHarness.h"
#include "probe.h"
#include <iostream>
#include <sstream>

TEST(Probe, ctor) {  // verify inc_ctor works for the trivial case since dtor depends on ctor to be tested properly
    Probe prb("ctor");
    prb.inc_ctor();
    CHECK_EQUAL(1, prb.get_ctor_calls());
}

TEST(Probe, dtor) {
    // verify inc_dtor works for the trivial case
    Probe prb("dtor");
    prb.inc_ctor();
    prb.inc_dtor();
    CHECK_EQUAL(1, prb.get_dtor_calls());
    // verify exception is thrown if improper use occurs
    try {
        prb.inc_dtor();
        CHECK_FAIL("An error should have been thrown since `dtor_calls > ctor_calls`.");
    } catch(int err_code) {
        CHECK_EQUAL(1, err_code);
    }
}

TEST(Probe, inst) {  // verify inst count is the difference between ctor_calls and dtor_calls
    Probe prb("inst");
    prb.inc_ctor();
    prb.inc_ctor();
    prb.inc_dtor();
    CHECK_EQUAL(1, prb.get_inst_count());
}

TEST(Probe, static_probe) {  // verify that static probe works as expected, check ostreams of Overhead and nop_probe
    Probe nop_probe("nop");
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
    res_probe.str("");
    res_probe << nop_probe;
    CHECK_EQUAL("target_cls: nop\nctor_calls: 0\ndtor_calls: 0\ninst_count: 0\n", res_probe.str());
}

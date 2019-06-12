#include "TestHarness.h"
#include "char-queue-deque.h"
#include <iostream>
#include <sstream>

TEST(CharDeque, construct_sizes) {
    std::stringstream cqss;
    CharDeque cq;
    cqss << cq;
    CHECK_EQUAL("\nsize: 0\nmax_size: 18446744073709551615\nqueue: \n\n", cqss.str());
    cqss.str("");
    CharDeque cq0(0);
    cqss << cq0;
    CHECK_EQUAL("\nsize: 0\nmax_size: 18446744073709551615\nqueue: \n\n", cqss.str());
    cqss.str("");
    CharDeque cq1(1);
    cqss << cq1;
    CHECK_EQUAL("\nsize: 1\nmax_size: 18446744073709551615\nqueue: \n\n", cqss.str());
    cqss.str("");
    CharDeque cq2(2);
    cqss << cq2;
    CHECK_EQUAL("\nsize: 2\nmax_size: 18446744073709551615\nqueue: \n\n", cqss.str());
}

TEST(CharDeque, enqueue) {
    std::stringstream cqss;
    CharDeque cq0(0);
    cq0.enqueue('a');
    cq0.enqueue('b');
    cq0.enqueue('c');
    cqss << cq0;
    CHECK_EQUAL("\nsize: 3\nmax_size: 18446744073709551615\nqueue: abc\n\n", cqss.str());
}

TEST(CharDeque, dequeue) {
    std::stringstream cqss;
    CharDeque cq0(0);
    cq0.dequeue();
    cq0.enqueue('i');
    cq0.enqueue('f');
    cq0.enqueue('q');
    cq0.enqueue('r');
    cq0.dequeue();
    cq0.dequeue();
    cq0.enqueue('g');
    cq0.enqueue('a');
    cq0.enqueue('c');
    cq0.dequeue();
    cq0.dequeue();
    cq0.dequeue();
    cqss << cq0;
    CHECK_EQUAL("\nsize: 2\nmax_size: 18446744073709551615\nqueue: ac\n\n", cqss.str());
}

TEST(CharDeque, isEmpty) {
    CharDeque cq0(0);
    CHECK_EQUAL(true, cq0.isEmpty());
    cq0.enqueue('i');
    CHECK_EQUAL(false, cq0.isEmpty());
    cq0.dequeue();
    CHECK_EQUAL(true, cq0.isEmpty());
}

TEST(CharDeque, swap) {
    std::stringstream orig_cqss;
    std::stringstream orig_cq2ss;
    std::stringstream cqss;
    std::stringstream cq2ss;
    CharDeque cq(0);
    cq.enqueue('i');
    cq.enqueue('f');
    cq.enqueue('q');
    cq.enqueue('r');
    cq.dequeue();
    cq.dequeue();
    cq.enqueue('g');
    cq.enqueue('a');
    cq.enqueue('c');
    cq.dequeue();
    cq.dequeue();
    cq.dequeue();
    CharDeque cq2(0);
    cq2.enqueue('c');
    cq2.enqueue('a');
    orig_cqss << cq;
    orig_cq2ss << cq2;
    cq.swap(cq2);
    cqss << cq;
    cq2ss << cq2;
    CHECK_EQUAL(orig_cq2ss.str(), cqss.str());
    CHECK_EQUAL(orig_cqss.str(), cq2ss.str());
}

TEST(CharDeque, capacity) {
    CharDeque cq0(0);
    CHECK_EQUAL(0, cq0.capacity());
    cq0.enqueue('a');
    cq0.enqueue('b');
    cq0.enqueue('c');
    CHECK_EQUAL(3, cq0.capacity());
    cq0.enqueue('g');
    cq0.enqueue('a');
    CHECK_EQUAL(5, cq0.capacity());
}

TEST(CharDeque, copy_assignment) {
    std::stringstream cqss;
    std::stringstream cq2ss;
    std::stringstream cq3ss;
    CharDeque cq(0);
    cq.enqueue('i');
    cq.enqueue('f');
    cq.enqueue('q');
    cq.enqueue('r');
    cq.dequeue();
    cq.dequeue();
    cq.enqueue('g');
    cq.enqueue('a');
    cq.enqueue('c');
    cq.dequeue();
    // create cq2 via copy and cq3 via assignment
    CharDeque cq2(cq);
    CharDeque cq3(0);
    cq3 = cq;
    // preserve state of cq
    cqss << cq;
    cq.dequeue();
    cq.dequeue();
    // create conditions to verify deep-copy against cq
    for (int i = 0; i < 7; ++i) {
        cq.enqueue('f');
    }
    // copy test cq2 and cq
    cq2ss << cq2;
    CHECK_EQUAL(cqss.str(), cq2ss.str());
    // assignment test cq3 and cq
    cq3ss << cq3;
    CHECK_EQUAL(cqss.str(), cq3ss.str());
}

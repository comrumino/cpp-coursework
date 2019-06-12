#include <iostream>
#include <sstream>
#include "TestHarness.h"
#include "char-queue.h"

TEST(CharQueue, construct_sizes) {
    std::stringstream cqss;
    CharQueue cq;
    cqss << cq;
    CHECK_EQUAL("\nsize: 1\nbegin: 0\ncount: 0\nqueue: \n\n", cqss.str());
    cqss.str("");
    CharQueue cq0(0);
    cqss << cq0;
    CHECK_EQUAL("\nsize: 1\nbegin: 0\ncount: 0\nqueue: \n\n", cqss.str());
    cqss.str("");
    CharQueue cq1(1);
    cqss << cq1;
    CHECK_EQUAL("\nsize: 1\nbegin: 0\ncount: 0\nqueue: \n\n", cqss.str());
    cqss.str("");
    CharQueue cq2(2);
    cqss << cq2;
    CHECK_EQUAL("\nsize: 2\nbegin: 0\ncount: 0\nqueue: \n\n", cqss.str());
}

TEST(CharQueue, enqueue) {
    std::stringstream cqss;
    CharQueue cq0(0);
    cq0.enqueue('\0');
    cq0.enqueue('a');
    cq0.enqueue('b');
    cq0.enqueue('c');
    cqss << cq0;
    CHECK_EQUAL("\nsize: 4\nbegin: 0\ncount: 3\nqueue: abc\n\n", cqss.str());
}

TEST(CharQueue, dequeue) {
    std::stringstream cqss;
    CharQueue cq0(0);
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
    CHECK_EQUAL("\nsize: 7\nbegin: 5\ncount: 2\nqueue: ac\n\n", cqss.str());
}

TEST(CharQueue, isEmpty) {
    CharQueue cq0(0);
    CHECK_EQUAL(true, cq0.isEmpty());
    cq0.enqueue('i');
    CHECK_EQUAL(false, cq0.isEmpty());
    cq0.dequeue();
    CHECK_EQUAL(true, cq0.isEmpty());
}

TEST(CharQueue, swap) {
    std::stringstream orig_cqss;
    std::stringstream orig_cq2ss;
    std::stringstream cqss;
    std::stringstream cq2ss;
    CharQueue cq(0);
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
    CharQueue cq2(0);
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

TEST(CharQueue, capacity) {
    CharQueue cq0(0);
    CHECK_EQUAL(1, cq0.capacity());
    cq0.enqueue('a');
    cq0.enqueue('b');
    cq0.enqueue('c');
    CHECK_EQUAL(4, cq0.capacity());
    cq0.enqueue('g');
    cq0.enqueue('a');
    CHECK_EQUAL(7, cq0.capacity());
}

TEST(CharQueue, copy_assignment) {
    std::stringstream cqss;
    std::stringstream cq2ss;
    std::stringstream cq3ss;
    CharQueue cq(0);
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
    CharQueue cq2(cq);
    CharQueue cq3(0);
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

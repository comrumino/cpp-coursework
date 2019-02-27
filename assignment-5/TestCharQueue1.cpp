#include <iostream>
#include "TestHarness.h"
#include "CharQueue1.h"

TEST(CharQueue, construct_sizes) {
    // the fuck
    // CharQueue cq();
    // std::cout << cq;
    CharQueue cq0(0);
    cq0.dequeue();
    cq0.enqueue('i');
    cq0.enqueue('f');
    cq0.dequeue();
    cq0.dequeue();
    cq0.enqueue('g');
    cq0.enqueue('a');
    cq0.enqueue('c');
    cq0.dequeue();
    cq0.dequeue();
    //cq0.dequeue();
    std::cout << cq0;
    CHECK_EQUAL("ifgac", cq0.queue.get());
    CHECK_EQUAL(6, strlen(cq0.queue.get()));

}

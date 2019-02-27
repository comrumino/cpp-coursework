#include <memory>
#include <iostream>
#include "CharQueue1.h"

CharQueue::CharQueue(size_t size)
    :begin{0}, count{0}, size{size ? size : 1}, queue{std::make_unique<char[]>(size + 1)}
{
}

CharQueue::CharQueue(const CharQueue& src) 
    :begin{src.begin}, count{src.count}, size{src.size}, queue{std::make_unique<char[]>(size + 1)}
{
    auto q = queue.get();
    auto sq = src.queue.get();
    while (*q++ = *sq++) {
        if (*q == '\0') {
            break;
        }
    }
}

void CharQueue::enqueue(char ch) {
    // check if count is capacity, and resize after enqueue
    queue[begin + count++ % size] = ch;
    if (count == size) {
        size_t newsize = size + (size >> 3) + (size < 9 ? 3 : 6);
        auto _queue = std::make_unique<char[]>(newsize);
        auto q = queue.get();
        q += begin;
        auto tq = _queue.get();
        while (*tq++ = *q++) {
            if (*q == '\0') {
                break;
            }
        }
        if (count + begin < size) {
            q = queue.get();
            for (int i = 0; i < begin + count - size; ++i) {
                *tq++ = *q++;
            }
        }
        queue = std::move(_queue);
        begin = 0;
        size = newsize;
    }
}

char CharQueue::dequeue() {

    // check if check empty
    //
    if (!isEmpty()) {
        --count;
        return queue[begin++];
    } else {
        std::cout << "Cannot dequeue empty queue!" << std::endl;
        return NULL; 
    }

}

bool CharQueue::isEmpty() const {
    return count == 0;
}

void CharQueue::swap(CharQueue& src) {  // exchange contents
    // check sizes

}

size_t CharQueue::capacity() const {
   return 0; 
}

CharQueue& CharQueue::operator=(CharQueue src) {
    size = src.size;
    begin = src.begin;
    count = src.count;
    queue = std::make_unique<char[]>(size); // initialize
    auto p = queue.get();  // get pointer
    auto q = src.queue.get();
    while (*p++ = *q++) {
        if (*q == '\0') {
            break;
        }
    }
    return *this;

}

std::ostream& operator<<(std::ostream& os, const CharQueue& cq) {
    os << std::endl;
    os << "size: " << cq.size << std::endl;
    os << "begin: " << cq.begin << std::endl;
    os << "count: " << cq.count << std::endl;
    os << "queue: ";
    auto p = cq.queue.get();
    while (*p != '\0') {
        std::cout << *p++;
    }
    std::cout << std::endl << std::endl ;
    return os;  // return ostream to allow chaining
}

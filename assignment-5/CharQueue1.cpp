/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 5.1
 *  Problem Statement:
 *   + CharQueue1 with a std::unique_ptr<char[]> array as the private data member.
 *     Use std::make_unique to grow the array used for the queue as needed.
 *     Add other private member variables as needed to track size and position.
 *     Overload the copy constructor and assignment operator to and implement a deep copy.
 */
#include <memory>
#include <iostream>
#include "CharQueue1.h"

CharQueue::CharQueue()
    :begin(0), count(0), size(1), queue(std::make_unique<char[]>(size + 1))
{
}

CharQueue::CharQueue(size_t size)
    :begin(0), count(0), size(size ? size : 1), queue(std::make_unique<char[]>(size + 1))
{
}

CharQueue::CharQueue(const CharQueue& src) 
    :begin(src.begin), count(src.count), size(src.size), queue(std::make_unique<char[]>(src.size + 1))
{
    auto q = queue.get();
    auto sq = src.queue.get();
    while (*q++ = *sq++) {
        if (*sq == '\0') {
            break;
        }
    }
}

void CharQueue::enqueue(char ch) {
    if (ch == '\0') {  // CharQueue assumes that enqueued characters are not null, so do nothing
        return;
    }
    queue[(begin + count) % size] = ch;
    count++;
    if (count == size) {
        size_t newsize = size + (size >> 3) + (size < 9 ? 3 : 6);
        auto _queue = std::make_unique<char[]>(newsize + 1);
        auto q = queue.get();
        q += begin;
        auto tq = _queue.get();
        for (int i = 0; i < count; ++i) {
            if (*q == '\0') {
                q = queue.get();
            }
            *tq++ = *q++;
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
        char ch = queue[begin++];
        begin = begin % size;
        return ch;
    } else {
        return '\0'; 
    }

}

bool CharQueue::isEmpty() const {
    return count == 0;
}

void CharQueue::swap(CharQueue& src) {  // exchange contents
    CharQueue _src(src);
    src.size = size;
    src.begin = begin;
    src.count = count;
    src.queue = std::move(queue);
    size = _src.size;
    begin = _src.begin;
    count = _src.count;
    queue = std::move(_src.queue);
}

size_t CharQueue::capacity() const {
   return size; 
}

CharQueue& CharQueue::operator=(CharQueue src) {
    size = src.size;
    begin = src.begin;
    count = src.count;
    queue = std::make_unique<char[]>(size + 1);
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
    p += cq.begin;
    for (int i = 0; i < cq.count; ++i) {
        if (*p == '\0') {
            p = cq.queue.get();
        }
        os << *p++;
    }
    os << std::endl << std::endl ;
    return os;  // return ostream to allow chaining
}

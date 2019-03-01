/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 5.2
 *  Problem Statement:
 *   + CharQueue2 with a std::deque<char> data member.
 *     Use the compiler generated copy constructor and assignment
 *     operator as a bitwise copy of the deque will perform a deep copy.
 */
#include <deque>
#include <memory>
#include <iostream>
#include "CharQueue2.h"

CharQueue::CharQueue()
    :queue()
{
}

CharQueue::CharQueue(size_t size)
    :queue()
{
    // allow for predetermined queue size as long as it does not 
    if (size > queue.max_size()) {
        queue.resize(queue.max_size());
    } else {
        queue.resize(size);
    }
}

CharQueue::CharQueue(const CharQueue& src) 
    :queue()
{
    queue = src.queue;  // std::deque makes this a deep-copy
}

void CharQueue::enqueue(char ch) {
    queue.push_back(ch);
}

char CharQueue::dequeue() {
    if (!queue.empty()) {
        char front = queue.front();
        queue.pop_front();
        return front;
    } else {  // when the queue is empty return null char
        return '\0';
    }
}

bool CharQueue::isEmpty() const {
    return queue.empty();
}

void CharQueue::swap(CharQueue& src) {  // exchange contents
    CharQueue _src(src);
    src.queue = queue;
    queue = _src.queue;
}

size_t CharQueue::capacity() const {
   return queue.size();
}

CharQueue& CharQueue::operator=(CharQueue src) {
    queue = src.queue;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const CharQueue& cq) {
    os << std::endl;
    os << "size: " << cq.queue.size() << std::endl;
    os << "max_size: " << cq.queue.max_size() << std::endl;
    os << "queue: ";
    for (auto p = cq.queue.cbegin(); p != cq.queue.cend(); ++p) {
        if (*p != '\0') {  // ignore null characters for insertion operator since they are invisible
            os << *p;
        }
    }
    os << std::endl << std::endl;
    return os;  // return ostream to allow chaining
}

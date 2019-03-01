/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 5.2
 *  Problem Statement:
 *   + CharQueue2 with a std::deque<char> data member.
 *     Use the compiler generated copy constructor and assignment
 *     operator as a bitwise copy of the deque will perform a deep copy.
 */
#pragma once
#include <deque>

class CharQueue {
private:
    std::deque<char> queue;

public:
    CharQueue();
    CharQueue(size_t size);
    CharQueue(const CharQueue& src);  // copy constructor

    void enqueue(char ch);
    char dequeue();

    bool isEmpty() const;
    void swap(CharQueue& src);

    size_t capacity() const;

    CharQueue& operator=(CharQueue src);
    // global function is friend of class, so can access private
    friend std::ostream& operator<<(std::ostream& os, const CharQueue& cq);
};

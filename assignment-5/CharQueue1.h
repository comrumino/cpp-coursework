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
#pragma once
#include <memory>

class CharQueue {
private:
    unsigned int begin;
    unsigned int count;
    size_t size;
    std::unique_ptr<char[]> queue;

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

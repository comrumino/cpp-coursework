#pragma once
#include <deque>
#include <memory>

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

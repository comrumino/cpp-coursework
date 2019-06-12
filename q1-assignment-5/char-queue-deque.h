#pragma once
#include <deque>
#include <iostream>

class CharDeque {
  private:
    std::deque<char> queue;

  public:
    CharDeque();
    CharDeque(size_t size);
    // CharDeque(const CharDeque& src);  // use default constructor, per prompt

    void enqueue(char ch);
    char dequeue();

    bool isEmpty() const;
    void swap(CharDeque &src);

    size_t capacity() const;

    // CharDeque& operator=(CharDeque src);  // use default assignment operator, per prompt
    // global function is friend of class, so can access private
    friend std::ostream &operator<<(std::ostream &os, const CharDeque &cq);
};

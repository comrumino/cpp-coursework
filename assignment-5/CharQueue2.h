#pragma once

class CharQueue {
private:
    // std::unique_ptr<char[]> 
    auto queue = std::make_unique<char[]>(0);

public:
    CharQueue();
    CharQueue(size_t size);
    CharQueue(const CharQueue& src); // copy constructor

    void enqueue(char ch);
    char dequeue();

    bool isEmpty() const;
    void swap(CharQueue& src);

    size_t capacity() const;

    CharQueue& operator=(CharQueue src);
};

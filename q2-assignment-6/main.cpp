#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#define RUN_MAIN 1

class BaseException {
  public:
    BaseException() {}
    virtual ~BaseException() {}

    virtual const char *message() const noexcept = 0;
};

class QueueEmptyException : public BaseException {
  public:
    QueueEmptyException() = default;
    const char *message() const noexcept override;
};

const char *QueueEmptyException::message() const noexcept { return "Queue Empty"; }

template <typename qContainer> class Queue {
  public:
    typedef typename qContainer::value_type Elmt;
    void push(const Elmt &e);
    Elmt pop();
    int size() const;
    std::string describe() const;

    Queue &operator=(const Queue<qContainer> &other);
    template <typename qContainer2> Queue &operator=(const Queue<qContainer2> &other);

  private:
    template <typename qContainer2> friend class Queue;
    qContainer mContainer;
};

template <typename qContainer> Queue<qContainer> &Queue<qContainer>::operator=(const Queue<qContainer> &other) {
    qContainer tmp;
    std::copy(other.mContainer.begin(), other.mContainer.end(), std::back_inserter(tmp));
    mContainer.swap(tmp);
    return *this;
}

template <typename qContainer>
template <typename qContainer2>
Queue<qContainer> &Queue<qContainer>::operator=(const Queue<qContainer2> &other) {
    qContainer tmp;
    std::copy(other.mContainer.begin(), other.mContainer.end(), std::back_inserter(tmp));
    mContainer.swap(tmp);
    return *this;
}

template <typename qContainer> std::string Queue<qContainer>::describe() const {
    std::stringstream desc;
    desc << "inside Queue base";
    return desc.str();
}

template <> std::string Queue<std::deque<int>>::describe() const {
    std::stringstream desc;
    desc << "inside Queue<deque<int>>";
    return desc.str();
}

template <typename qContainer> void Queue<qContainer>::push(const Elmt &e) { mContainer.push_back(e); }

template <typename qContainer> int Queue<qContainer>::size() const { return mContainer.size(); }

template <typename qContainer> typename Queue<qContainer>::Elmt Queue<qContainer>::pop() {
#if RUN_MAIN
    std::cout << describe() << std::endl;
#endif
    Elmt rv;
    if (!mContainer.empty()) {
        rv = mContainer.front();
        mContainer.pop_front();
    } else {
        throw QueueEmptyException();
    }
    return rv;
}

#if RUN_MAIN
// Please don't modify
int main(int argc, char **argv) {
    Queue<std::deque<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    q.push(6);
    q.push(7);

    Queue<std::deque<char>> q2;
    q2.push('c');
    std::cout << q2.pop() << std::endl;

    std::cout << q.pop() << std::endl;
    q = q2;
}
#else
#include "TestHarness.h"

TEST(Queue, DequeueInt) {
    Queue<std::deque<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    CHECK_EQUAL(1, q.pop());
    CHECK_EQUAL(2, q.size());
    CHECK_EQUAL("inside Queue<deque<int>>", q.describe());
}

TEST(Queue, DequeueChar) {
    Queue<std::deque<char>> q2;
    q2.push('c');
    CHECK_EQUAL('c', q2.pop());
    CHECK_EQUAL(0, q2.size());
    CHECK_EQUAL("inside Queue base", q2.describe());
}

TEST(Queue, ListString) {
    Queue<std::list<std::string>> qListStr;
    qListStr.push("hello world");
    CHECK_EQUAL("hello world", qListStr.pop());
    CHECK_EQUAL(0, qListStr.size());
    CHECK_EQUAL("inside Queue base", qListStr.describe());
    std::string exc_msg = "";
    try {
        qListStr.pop();
    } catch (QueueEmptyException exc) {
        CHECK_EQUAL("Queue Empty", exc.message());
    }
}

TEST(Queue, DequeueMixed) {
    Queue<std::deque<int>> qDequeInt;
    qDequeInt.push(1);
    CHECK_EQUAL(1, qDequeInt.pop());
    CHECK_EQUAL(0, qDequeInt.size());
    Queue<std::deque<char>> qDequeChar;
    qDequeChar.push('a');
    qDequeInt = qDequeChar;
    CHECK_EQUAL('a', qDequeChar.pop());
    CHECK_EQUAL(0, qDequeChar.size());
    CHECK_EQUAL('a', qDequeInt.pop());
    CHECK_EQUAL(0, qDequeChar.size());
}
#endif

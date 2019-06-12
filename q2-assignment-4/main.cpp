#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;

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

class QueueCopyException : public BaseException {
  public:
    QueueCopyException() = default;
    const char *message() const noexcept override;
};

const char *QueueCopyException::message() const noexcept { return "Invalid Queue Copy"; }

class QueueGrowException : public BaseException {
  public:
    QueueGrowException() = default;
    const char *message() const noexcept override;
};

const char *QueueGrowException::message() const noexcept { return "Invalid Queue Grow"; }

class QueueBase {
  public:
    QueueBase(unsigned int capacity);
    QueueBase(const QueueBase &other);

    int Size() const;
    bool IsEmpty() const;
    bool IsFull() const;
    int Capacity() const;

    void Swap(QueueBase &other);

  protected:
    static const int m_Empty = -1;
    int m_Capacity;
    int m_Head = m_Empty;
    int m_Tail = m_Empty;
};

inline QueueBase::QueueBase(unsigned int capacity) : m_Capacity(capacity) {}

inline QueueBase::QueueBase(const QueueBase &other)
    : m_Capacity(other.m_Capacity), m_Head(other.m_Head), m_Tail(other.m_Tail) {}

inline int QueueBase::Size() const {
    if (IsEmpty()) // m_Head == -1 && m_Tail == -1
        return 0;
    else if (IsFull()) // m_Head % m_Capacity == m_Tail % m_Capacity
        return m_Capacity;
    else if (m_Head > m_Tail)
        return m_Head - m_Tail;
    else
        return (m_Capacity + 1) - (m_Tail - m_Head); // Less the negative space (distance between head and tail)
}

inline bool QueueBase::IsEmpty() const { return m_Tail == m_Empty && m_Head == m_Empty; }

inline bool QueueBase::IsFull() const { return !IsEmpty() && (m_Tail % m_Capacity) == (m_Head % m_Capacity); }

inline int QueueBase::Capacity() const { return m_Capacity; }

inline void QueueBase::Swap(QueueBase &other) { std::swap(*this, other); }

template <typename T> class Queue : public QueueBase {
  public:
    Queue(unsigned int size);
    Queue(const Queue &other);
    ~Queue();

    void Push(const T &e);

    T Pop();

    Queue &operator=(const Queue<T> &other);

    template <typename T2> Queue &operator=(const Queue<T2> &other);

    void Swap(Queue<T> &other);

  private:
    template <typename T2> friend class Queue;

    void Grow(int n_Capacity = -1);
    template <typename T2> void Copy(const Queue<T2> &other);

    T *m_Array;
};

template <typename T> Queue<T>::Queue(unsigned int capacity) : QueueBase(capacity), m_Array(new T[m_Capacity]) {}

template <typename T> Queue<T>::~Queue() {
    if (m_Array != nullptr)
        delete[] m_Array;
}

template <typename T> Queue<T>::Queue(const Queue<T> &other) : QueueBase(other), m_Array(new T[m_Capacity]) {
    Copy(other);
}

template <typename T> Queue<T> &Queue<T>::operator=(const Queue<T> &other) {
    // Always realloc even if current capacity is greater than the rhs capacity for predictable swap
    if (m_Array != nullptr)
        delete[] m_Array;
    m_Capacity = other.m_Capacity;
    m_Array = new T[m_Capacity];
    Copy(other);
    return *this;
}

template <typename T> template <typename T2> Queue<T> &Queue<T>::operator=(const Queue<T2> &other) {
    // Always realloc even if current capacity is greater than the rhs capacity for predictable swap
    if (m_Array != nullptr)
        delete[] m_Array;
    m_Capacity = other.m_Capacity;
    m_Array = new T[m_Capacity];
    Copy(other);
    return *this;
}

template <typename T> void Queue<T>::Swap(Queue<T> &other) { std::swap(*this, other); }

template <typename T> void Queue<T>::Push(const T &e) {
    if (IsEmpty()) {
        m_Tail = 0;
        m_Head = 0;
    } else if (IsFull()) {
        Grow();
    }
    m_Head %= m_Capacity;
    m_Array[m_Head] = e;
    ++m_Head;
}

template <typename T> T Queue<T>::Pop() {
    if (IsEmpty()) {
        throw QueueEmptyException();
    } else {
        T returnValue = T();
        m_Tail %= m_Capacity; // consistency with m_Head behavior
        returnValue = m_Array[m_Tail];
        ++m_Tail;
        if (m_Tail == m_Head) {
            m_Tail = m_Empty;
            m_Head = m_Empty;
        }

        return returnValue;
    }
}

template <typename T> void Queue<T>::Grow(int n_Capacity) { // increase capacity
    if (n_Capacity == -1) {
        n_Capacity = m_Capacity + (m_Capacity >> 3) + (m_Capacity < 9 ? 3 : 6);
    } else if (n_Capacity > m_Capacity) {
        n_Capacity = n_Capacity;
    } else {
        throw QueueGrowException();
    }
    Queue<T> nQueue(n_Capacity);
    nQueue.Copy(*this);
    if (m_Array != nullptr)
        delete[] m_Array;
    m_Capacity = nQueue.Capacity();
    m_Array = new T[m_Capacity];
    Copy(nQueue);
}

template <typename T> template <typename T2> void Queue<T>::Copy(const Queue<T2> &other) {
    if (m_Capacity >= other.m_Capacity) {
        m_Head = 0;
        m_Tail = 0;
        if (other.m_Head > other.m_Tail) { // elements are contiguous
            for (int i = other.m_Tail; i < other.m_Head; ++i) {
                m_Array[m_Head] = other.m_Array[i];
                ++m_Head;
            }
        } else { // elements are not contiguous so do from start to head and tail to end
            for (int i = other.m_Tail; i < other.m_Capacity; ++i) { // from tail to end
                m_Array[m_Head] = other.m_Array[i];
                ++m_Head;
            }
            for (int i = 0; i < other.m_Head; ++i) { // from start up to head
                m_Array[m_Head] = other.m_Array[i];
                ++m_Head;
            }
        }
    } else {
        throw QueueCopyException();
    }
}

// Please do not modify anything below this line.
void TestSize() {
    Queue<int> q(10);
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    q.Push(5);
    q.Push(6);
    q.Push(7);

    if (q.Size() == 7) {
        cout << "pass";
    }
}

void TestPop() {
    Queue<int> q(10);
    q.Push(1);
    q.Push(2);

    if (q.Pop() == 1 && q.Pop() == 2) {
        cout << "pass";
    }
}

void TestDirectInitCtor() {
    Queue<int> q1(10);
    q1.Push(1);
    q1.Push(2);
    q1.Push(3);
    Queue<int> q2(q1);
    q1.Pop();
    q1.Pop();

    if (q1.Size() == 1 && q2.Size() == 3) {
        cout << "pass";
    }
}

void TestQueueEmpty() {
    Queue<int> q(2); // head = tail = -1
    q.Push(1);       // head = tail = 0
    q.Pop();         // head = tail = -1 (queue is empty)

    try {
        q.Pop(); // this must throw an exception
    } catch (const BaseException &e) {
        if (strncmp(e.message(), "Queue Empty", 11) == 0) {
            cout << "pass";
        }
    }
}

void TestAssignmentCtor() {
    Queue<int> q1(10);
    q1.Push(1);
    q1.Push(2);
    q1.Push(3);
    Queue<int> q2(10);
    q2 = q1;
    q1.Pop();
    q1.Pop();

    if (q1.Size() == 1 && q2.Size() == 3) {
        cout << "pass";
    }
}

void TestIntFloatAssignmentCtor() {
    Queue<int> q1(10);
    q1.Push(1);
    q1.Push(2);
    q1.Push(3);
    Queue<float> q2(10);
    q2 = q1;
    q1.Pop();
    q1.Pop();

    if (q1.Size() == 1 && q2.Size() == 3) {
        cout << "pass";
    }
}

#include "TestHarness.h"

TEST(Queue, Size) {
    Queue<int> q(10);
    q.Push(1);
    q.Push(2);
    q.Push(3);
    q.Push(4);
    q.Push(5);
    q.Push(6);
    q.Push(7);
    CHECK_EQUAL(7, q.Size());
}

TEST(Queue, Pop) {
    bool passed = true;
    Queue<int> q(3);
    q.Push(1);
    q.Push(2);
    q.Push(3);
    CHECK_EQUAL(1, q.Pop());
    q.Push(4);
    CHECK_EQUAL(2, q.Pop());
    q.Push(5);
    CHECK_EQUAL(3, q.Pop());
    q.Push(6);
    CHECK_EQUAL(4, q.Pop());
    CHECK_EQUAL(5, q.Pop());
    CHECK_EQUAL(6, q.Pop());
    CHECK_EQUAL(0, q.Size());
}

TEST(Queue, DirectInitCtor) {
    Queue<int> q1(10);
    q1.Push(1);
    q1.Push(2);
    q1.Push(3);
    Queue<int> q2(q1);
    q1.Pop();
    q1.Pop();

    CHECK_EQUAL(1, q1.Size());
    CHECK_EQUAL(3, q2.Size());
}

TEST(Queue, Empty) {
    bool passed = false;
    Queue<int> q(2); // head = tail = -1
    CHECK_EQUAL(true, q.IsEmpty());
    CHECK_EQUAL(false, q.IsFull());
    q.Push(1); // head = tail = 0
    q.Pop();   // head = tail = -1 (queue is empty)

    try {
        q.Pop(); // this must throw an exception
    } catch (const BaseException &e) {
        if (strncmp(e.message(), "Queue Empty", 11) == 0) {
            passed = true;
        }
    }
    CHECK_EQUAL(true, passed);
}

TEST(Queue, AssignmentCtor) {
    bool passed = false;
    Queue<int> q1(10);
    q1.Push(1);
    q1.Push(2);
    q1.Push(3);
    Queue<int> q2(10);
    q2 = q1;
    q1.Pop();
    q1.Pop();
    CHECK_EQUAL(1, q1.Size());
    CHECK_EQUAL(3, q2.Size());
}

TEST(Queue, IntFloatAssignmentCtor) {
    Queue<int> q1(10);
    q1.Push(1);
    q1.Push(2);
    q1.Push(3);
    Queue<float> q2(10);
    q2 = q1;
    q1.Pop();
    q1.Pop();

    CHECK_EQUAL(1, q1.Size());
    CHECK_EQUAL(3, q2.Size());
}

TEST(Queue, Swap) {
    Queue<int> q1(2);
    q1.Push(1);
    q1.Push(2);
    Queue<int> q2(4);
    q2.Push(1);
    q2.Push(2);
    q2.Push(3);
    CHECK_EQUAL(2, q1.Size());
    CHECK_EQUAL(true, q1.IsFull());
    CHECK_EQUAL(3, q2.Size());
    CHECK_EQUAL(false, q2.IsFull());
    CHECK_EQUAL(2, q1.Capacity());
    CHECK_EQUAL(4, q2.Capacity());
    q1.Swap(q2);
    CHECK_EQUAL(3, q1.Size());
    CHECK_EQUAL(false, q1.IsFull());
    CHECK_EQUAL(2, q2.Size());
    CHECK_EQUAL(true, q2.IsFull());
    CHECK_EQUAL(4, q1.Capacity());
    CHECK_EQUAL(2, q2.Capacity());
}

TEST(Queue, DynamicTail) {
    Queue<int> q1(3);
    Queue<int> q2(3);
    for (int i = 0; i < 3; ++i)
        q1.Push(i);
    for (int i = 0; i < 3; ++i) { // Verify copy for full capacity for boundary conditions
        q2 = q1;
        q1.Swap(q2);
        CHECK_EQUAL(i, q1.Pop());
        q1.Push(i);
        CHECK_EQUAL(3, q1.Size());
    }
}

TEST(Queue, Dynamic) {
    Queue<int> q1(3);
    q1.Push(1);
    q1.Push(2);
    q1.Push(3);
    CHECK_EQUAL(3, q1.Size());
    CHECK_EQUAL(3, q1.Capacity());
    q1.Push(4);
    CHECK_EQUAL(4, q1.Size());
    CHECK_EQUAL(6, q1.Capacity());
    q1.Push(5);
    q1.Push(6);
    q1.Push(7);
    CHECK_EQUAL(7, q1.Size());
    CHECK_EQUAL(9, q1.Capacity());
    q1.Push(8);
    q1.Push(9);
    q1.Push(10);
    CHECK_EQUAL(10, q1.Size());
    CHECK_EQUAL(16, q1.Capacity());
}

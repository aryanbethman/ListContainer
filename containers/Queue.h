#pragma once

#include "RestrictedSequentialList.h"
#include "LinkedList.h"

// Queue is an adapter class, using a LinkedList for storage.
template <typename T>
class Queue : public RestrictedSequentialList<T> {
private:
    LinkedList<T> storage;

public:
    // --- AbstractList Interface ---
    // push adds to the back of the queue
    void push(T item) override;
    // pop removes from the front of the queue
    T pop() override;
    int size() override;
    void clear() override;
    const char* name() override;

    // --- SequentialList Interface (hidden) ---
    void insert_at(int pos, T item) override;
    void erase_at(int pos) override;
    T at(int pos) override;

    // --- Queue Specific Method ---
    T front();
};

#include "Queue.cpp"

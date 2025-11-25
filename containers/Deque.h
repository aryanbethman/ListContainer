#pragma once

#include "RestrictedSequentialList.h"
#include "LinkedList.h"

// Deque is an adapter class, using a LinkedList for storage.
template <typename T>
class Deque : public RestrictedSequentialList<T> {
private:
    LinkedList<T> storage;

public:
    // --- AbstractList Interface ---
    // Default push adds to the back
    void push(T item) override;
    // Default pop removes from the back
    T pop() override;
    int size() override;
    void clear() override;
    const char* name() override;

    // --- SequentialList Interface (hidden) ---
    void insert_at(int pos, T item) override;
    void erase_at(int pos) override;
    T at(int pos) override;

    // --- Deque Specific Methods ---
    void push_front(T item);
    T pop_front();
    T front();
    T back();
};

#include "Deque.cpp"

#pragma once

#include "RestrictedSequentialList.h"
#include "VectorList.h"

// Note: Stack is an adapter class. It contains a VectorList and uses it for storage.
template <typename T>
class Stack : public RestrictedSequentialList<T> {
private:
    VectorList<T> storage;

public:
    // --- AbstractList Interface ---
    void push(T item) override;
    T pop() override;
    int size() override;
    void clear() override;
    const char* name() override;

    // --- SequentialList Interface (hidden by not being implemented directly) ---
    // We will throw errors if these are called, as they violate Stack principles.
    void insert_at(int pos, T item) override;
    void erase_at(int pos) override;
    T at(int pos) override;

    // --- Stack Specific Method ---
    T top();
};

#include "Stack.cpp"

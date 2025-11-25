#pragma once

#include "Heap.h"

// PriorityQueue is implemented by inheriting from Heap.
// It restricts access to heap-specific methods like heapify and at.
template <typename T>
class PriorityQueue : public Heap<T> {
public:
    const char* name() override;

    // --- Forbidden Methods ---
    void heapify() = delete; // Or throw an exception
    T at(int pos) = delete;
};

#include "PriorityQueue.cpp"

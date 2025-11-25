#pragma once

#include "PriorityBased.h"
#include "VectorList.h"

// Heap implementation using a VectorList for storage.
template <typename T>
class Heap : public PriorityBased<T> {
protected: // Protected so PriorityQueue can inherit the implementation
    VectorList<T> storage;

    // Heap algorithm helpers
    void sift_up(int index);
    void sift_down(int index);

    // Get parent/child indices
    int parent(int index) { return (index - 1) / 2; }
    int left_child(int index) { return 2 * index + 1; }
    int right_child(int index) { return 2 * index + 2; }

public:
    // --- AbstractList Interface ---
    void push(T item) override;
    T pop() override;
    int size() override;
    void clear() override;
    const char* name() override;

    // --- PriorityBased Interface ---
    T top() override;

    // --- Heap Specific Methods ---
    // Rearranges the collection into a valid heap structure
    void heapify();
    // Returns item at a specific index in the heap's underlying array
    T at(int pos);
};

#include "Heap.cpp"

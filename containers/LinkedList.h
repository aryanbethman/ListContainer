#pragma once

#include "SequentialList.h"
#include "ListNode.h"

template <typename T>
class LinkedList : public SequentialList<T> {
private:
    ListNode<T> sentinel;
    int _size;

    // Helper to get node at a specific position
    ListNode<T>* node_at(int pos);

public:
    // Constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // --- AbstractList Interface ---
    void push(T item) override;
    T pop() override;
    int size() override;
    void clear() override;
    const char* name() override;

    // --- SequentialList Interface ---
    void insert_at(int pos, T item) override;
    void erase_at(int pos) override;
    T at(int pos) override;
};

#include "LinkedList.cpp"

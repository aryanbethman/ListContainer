#pragma once

#include "SequentialList.h"
#include "../common/list_err.h"

template <typename T>
class VectorList : public SequentialList<T> {
private:
    T* _data;         // Pointer to the dynamically allocated array
    int _size;        // Current number of elements in the list
    int _capacity;    // Current allocated size of the array

    // Private helper to handle resizing the dynamic array
    void resize(int new_capacity);

public:
    // Constructor
    VectorList();

    // Destructor
    ~VectorList();

    // --- AbstractList Interface Implementation ---
    void push(T item) override;
    T pop() override;
    int size() override;
    void clear() override;
    const char* name() override;

    // --- SequentialList Interface Implementation ---
    void insert_at(int pos, T item) override;
    void erase_at(int pos) override;
    T at(int pos) override;

    // Helper for efficient swapping
    void swap(int pos1, int pos2);

    // Helper to set a value at a specific position
    void set_at(int pos, T item);
};

#include "VectorList.cpp"
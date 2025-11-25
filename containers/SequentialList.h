#pragma once

#include "AbstractList.h"

template <typename T>
class SequentialList : public AbstractList<T> {
public:
    virtual ~SequentialList() {};

    // Inserts an item at a specific integer pos
    virtual void insert_at(int pos, T item) = 0;

    // Removes the item at a specific integer pos
    virtual void erase_at(int pos) = 0;

    // Returns the item at a specific integer pos without removing it
    virtual T at(int pos) = 0;
};

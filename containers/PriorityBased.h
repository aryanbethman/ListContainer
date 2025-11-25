#pragma once

#include "AbstractList.h"

template <typename T>
class PriorityBased : public AbstractList<T> {
public:
    virtual ~PriorityBased() {};

    // Returns the highest-priority item without removing it
    virtual T top() = 0;
};

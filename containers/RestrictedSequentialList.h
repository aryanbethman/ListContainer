#pragma once

#include "SequentialList.h"

// This class doesn't add new methods, it just serves as a grouping
// in the hierarchy for Stack, Queue, and Deque.
template <typename T>
class RestrictedSequentialList : public SequentialList<T> {
public:
    virtual ~RestrictedSequentialList() {};
};

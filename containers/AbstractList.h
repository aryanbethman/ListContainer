#pragma once

// Generic type T for the items in the list
template <typename T>
class AbstractList {
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~AbstractList() {};

    // Adds a single item to the container
    virtual void push(T item) = 0;

    // Removes and returns a single item from the container
    virtual T pop() = 0;

    // Returns the total number of items currently in the container
    virtual int size() = 0;

    // Removes all items from the container
    virtual void clear() = 0;

    // Returns the name of the container type (e.g., "Stack", "Queue")
    virtual const char* name() = 0;
};

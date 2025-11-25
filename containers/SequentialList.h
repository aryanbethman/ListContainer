#pragma once

#include "AbstractList.h"
#include <functional>

// Forward declaration (VectorList is defined later)
template <typename T> class VectorList;

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

    // ========================================================================
    // FUNCTIONAL PROGRAMMING OPERATIONS
    // ========================================================================

    /**
     * Map - Apply a transformation function to each element, producing a new list.
     * 
     * WHAT: Transform every element in the list using the provided function.
     * 
     * @param transform A function that takes an element of type T and returns type U
     * @return A new SequentialList containing the transformed elements
     * 
     * Example:
     *   VectorList<int> nums = {1, 2, 3};
     *   VectorList<int> squared = nums.map<int>([](int x) { return x * x; });
     *   // Result: {1, 4, 9}
     */
    template <typename U>
    VectorList<U> map(std::function<U(T)> transform);

    /**
     * Filter - Select only elements that match a predicate.
     * 
     * WHAT: Keep only the elements for which the predicate returns true.
     * 
     * @param predicate A function that takes an element and returns bool
     * @return A new SequentialList containing only matching elements
     * 
     * Example:
     *   VectorList<int> nums = {1, 2, 3, 4, 5};
     *   VectorList<int> evens = nums.filter([](int x) { return x % 2 == 0; });
     *   // Result: {2, 4}
     */
    VectorList<T> filter(std::function<bool(T)> predicate);

    /**
     * Reduce - Combine all elements into a single value using an accumulator function.
     * 
     * WHAT: Aggregate the list into a single value by repeatedly applying the combine function.
     * 
     * @param initial The starting value for the accumulator
     * @param combine A function that takes (accumulator, element) and returns new accumulator
     * @return The final accumulated value
     * 
     * Example:
     *   VectorList<int> nums = {1, 2, 3, 4, 5};
     *   int sum = nums.reduce<int>(0, [](int acc, int x) { return acc + x; });
     *   // Result: 15
     */
    template <typename U>
    U reduce(U initial, std::function<U(U, T)> combine);

    /**
     * ForEach - Perform a side-effect action on each element.
     * 
     * WHAT: Execute the action function for each element (typically for I/O or external state).
     * 
     * @param action A function that takes an element and performs some action
     * 
     * Example:
     *   VectorList<int> nums = {1, 2, 3};
     *   nums.forEach([](int x) { std::cout << x << std::endl; });
     */
    void forEach(std::function<void(T)> action);
};

// Include the template implementation
#include "SequentialList.cpp"

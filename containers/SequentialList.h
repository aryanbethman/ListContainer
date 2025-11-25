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

    // ========================================================================
    // ADVANCED AGGREGATION OPERATIONS
    // ========================================================================

    /**
     * Min - Find the minimum element.
     * 
     * WHAT: Return the smallest element in the list
     * 
     * @return Minimum element
     * @throws list_err if list is empty
     * 
     * Example:
     *   VectorList<int> nums = {5, 2, 8, 1, 9};
     *   int min = nums.min();  // Returns 1
     */
    T min();

    /**
     * Max - Find the maximum element.
     * 
     * WHAT: Return the largest element in the list
     * 
     * @return Maximum element
     * @throws list_err if list is empty
     */
    T max();

    /**
     * Sum - Calculate sum of all elements.
     * 
     * WHAT: Add all elements together
     * 
     * @return Sum of all elements
     * 
     * Note: Requires T to support operator+
     */
    T sum();

    /**
     * Average - Calculate arithmetic mean.
     * 
     * WHAT: Compute average value of all elements
     * 
     * @return Average as double
     * @throws list_err if list is empty
     * 
     * Example:
     *   VectorList<int> nums = {1, 2, 3, 4, 5};
     *   double avg = nums.average();  // Returns 3.0
     */
    double average();

    /**
     * Median - Find the middle value.
     * 
     * WHAT: Return the median (middle value when sorted)
     * 
     * @return Median value
     * @throws list_err if list is empty
     * 
     * Note: Creates a sorted copy, does not modify original
     */
    double median();

    /**
     * Count inversions - Count pairs (i,j) where i < j but list[i] > list[j].
     * 
     * WHAT: Measure how far the list is from being sorted
     * 
     * @return Number of inversions
     * 
     * Example:
     *   VectorList<int> nums = {3, 1, 2};
     *   int inv = nums.countInversions();  // Returns 2
     *   // Inversions: (3,1) and (3,2)
     */
    int countInversions();

    /**
     * Any - Check if any element satisfies predicate.
     * 
     * WHAT: Return true if at least one element matches
     * 
     * @param predicate Function to test elements
     * @return true if any element matches
     */
    bool any(std::function<bool(T)> predicate);

    /**
     * All - Check if all elements satisfy predicate.
     * 
     * WHAT: Return true if every element matches
     * 
     * @param predicate Function to test elements
     * @return true if all elements match
     */
    bool all(std::function<bool(T)> predicate);

    /**
     * None - Check if no elements satisfy predicate.
     * 
     * WHAT: Return true if no elements match
     * 
     * @param predicate Function to test elements
     * @return true if no elements match
     */
    bool none(std::function<bool(T)> predicate);

    /**
     * Find - Get first element matching predicate.
     * 
     * WHAT: Return the first element that matches, or throw if none found
     * 
     * @param predicate Function to test elements
     * @return First matching element
     * @throws list_err if no match found
     */
    T find(std::function<bool(T)> predicate);

    /**
     * Contains - Check if element exists in list.
     * 
     * WHAT: Return true if the value is in the list
     * 
     * @param value Value to search for
     * @return true if value is found
     */
    bool contains(T value);
};

// Include the template implementation
#include "SequentialList.cpp"

#pragma once

#include <functional>
#include "../containers/SequentialList.h"
#include "../containers/VectorList.h"

/**
 * Search Algorithms Module
 * 
 * Provides various search operations for list containers.
 */

namespace algorithms {

/**
 * Linear Search: Find first occurrence of an element
 * 
 * @param list The list to search
 * @param value The value to find
 * @return Index of first occurrence, or -1 if not found
 */
template<typename T>
int linearSearch(SequentialList<T>& list, const T& value) {
    for (int i = 0; i < list.size(); i++) {
        if (list.at(i) == value) {
            return i;
        }
    }
    return -1;
}

/**
 * Linear Search with Predicate: Find first element satisfying a condition
 * 
 * @param list The list to search
 * @param predicate Function that returns true for the target element
 * @return Index of first match, or -1 if not found
 */
template<typename T>
int linearSearchIf(SequentialList<T>& list, std::function<bool(T)> predicate) {
    for (int i = 0; i < list.size(); i++) {
        if (predicate(list.at(i))) {
            return i;
        }
    }
    return -1;
}

/**
 * Binary Search: Find element in sorted list
 * 
 * @param list The SORTED list to search
 * @param value The value to find
 * @param compare Comparison function
 * @return Index of the element, or -1 if not found
 */
template<typename T>
int binarySearch(SequentialList<T>& list, const T& value, 
                 std::function<bool(T,T)> compare = [](T a, T b) { return a < b; }) {
    int left = 0;
    int right = list.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        T midValue = list.at(mid);
        
        if (midValue == value) {
            return mid;
        }
        
        if (compare(midValue, value)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

/**
 * Find All: Find all occurrences of a value
 * 
 * @param list The list to search
 * @param value The value to find
 * @return VectorList of indices where value was found
 */
template<typename T>
VectorList<int> findAll(SequentialList<T>& list, const T& value) {
    VectorList<int> indices;
    for (int i = 0; i < list.size(); i++) {
        if (list.at(i) == value) {
            indices.push(i);
        }
    }
    return indices;
}

/**
 * Find All If: Find all elements satisfying a predicate
 * 
 * @param list The list to search
 * @param predicate Function to test elements
 * @return VectorList of indices where predicate returned true
 */
template<typename T>
VectorList<int> findAllIf(SequentialList<T>& list, std::function<bool(T)> predicate) {
    VectorList<int> indices;
    for (int i = 0; i < list.size(); i++) {
        if (predicate(list.at(i))) {
            indices.push(i);
        }
    }
    return indices;
}

/**
 * Contains: Check if a value exists in the list
 * 
 * @param list The list to search
 * @param value The value to find
 * @return true if value is found, false otherwise
 */
template<typename T>
bool contains(SequentialList<T>& list, const T& value) {
    return linearSearch(list, value) != -1;
}

/**
 * Count Occurrences: Count how many times a value appears
 * 
 * @param list The list to search
 * @param value The value to count
 * @return Number of occurrences
 */
template<typename T>
int countOccurrences(SequentialList<T>& list, const T& value) {
    int count = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list.at(i) == value) {
            count++;
        }
    }
    return count;
}

} // namespace algorithms

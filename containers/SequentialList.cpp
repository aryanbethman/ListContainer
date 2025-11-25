/*
 * Implementation of Functional Operations for SequentialList
 * 
 * These are template implementations, so they must be in the header
 * or included by it. This file is included at the end of SequentialList.h
 */

#include "VectorList.h"
#include "../common/list_err.h"

// ============================================================================
// MAP - Transform each element
// ============================================================================
template <typename T>
template <typename U>
VectorList<U> SequentialList<T>::map(std::function<U(T)> transform) {
    VectorList<U> result;
    
    // Apply transformation to each element
    for (int i = 0; i < this->size(); i++) {
        U transformed = transform(this->at(i));
        result.push(transformed);
    }
    
    return result;
}

// ============================================================================
// FILTER - Select matching elements
// ============================================================================
template <typename T>
VectorList<T> SequentialList<T>::filter(std::function<bool(T)> predicate) {
    VectorList<T> result;
    
    // Include only elements that match the predicate
    for (int i = 0; i < this->size(); i++) {
        T element = this->at(i);
        if (predicate(element)) {
            result.push(element);
        }
    }
    
    return result;
}

// ============================================================================
// REDUCE - Aggregate to single value
// ============================================================================
template <typename T>
template <typename U>
U SequentialList<T>::reduce(U initial, std::function<U(U, T)> combine) {
    U accumulator = initial;
    
    // Apply combine function to each element
    for (int i = 0; i < this->size(); i++) {
        accumulator = combine(accumulator, this->at(i));
    }
    
    return accumulator;
}

// ============================================================================
// FOREACH - Perform side effects
// ============================================================================
template <typename T>
void SequentialList<T>::forEach(std::function<void(T)> action) {
    // Execute action for each element
    for (int i = 0; i < this->size(); i++) {
        action(this->at(i));
    }
}

// ============================================================================
// ADVANCED AGGREGATION OPERATIONS
// ============================================================================

// ============================================================================
// MIN - Find minimum element
// ============================================================================
template <typename T>
T SequentialList<T>::min() {
    if (this->size() == 0) {
        throw list_err("Cannot find min of empty list");
    }
    
    T minimum = this->at(0);
    for (int i = 1; i < this->size(); i++) {
        if (this->at(i) < minimum) {
            minimum = this->at(i);
        }
    }
    return minimum;
}

// ============================================================================
// MAX - Find maximum element
// ============================================================================
template <typename T>
T SequentialList<T>::max() {
    if (this->size() == 0) {
        throw list_err("Cannot find max of empty list");
    }
    
    T maximum = this->at(0);
    for (int i = 1; i < this->size(); i++) {
        if (this->at(i) > maximum) {
            maximum = this->at(i);
        }
    }
    return maximum;
}

// ============================================================================
// SUM - Calculate sum of all elements
// ============================================================================
template <typename T>
T SequentialList<T>::sum() {
    if (this->size() == 0) {
        return T();  // Return default-constructed T (e.g., 0 for int)
    }
    
    T total = this->at(0);
    for (int i = 1; i < this->size(); i++) {
        total = total + this->at(i);
    }
    return total;
}

// ============================================================================
// AVERAGE - Calculate arithmetic mean
// ============================================================================
template <typename T>
double SequentialList<T>::average() {
    if (this->size() == 0) {
        throw list_err("Cannot calculate average of empty list");
    }
    
    // Use reduce to sum, then divide
    T total = this->sum();
    return static_cast<double>(total) / this->size();
}

// ============================================================================
// MEDIAN - Find middle value
// ============================================================================
template <typename T>
double SequentialList<T>::median() {
    if (this->size() == 0) {
        throw list_err("Cannot calculate median of empty list");
    }
    
    // Create a sorted copy
    VectorList<T> sorted;
    for (int i = 0; i < this->size(); i++) {
        sorted.push(this->at(i));
    }
    
    // Simple bubble sort (good enough for demonstration)
    for (int i = 0; i < sorted.size() - 1; i++) {
        for (int j = 0; j < sorted.size() - i - 1; j++) {
            if (sorted.at(j) > sorted.at(j + 1)) {
                T temp = sorted.at(j);
                sorted.erase_at(j);
                sorted.insert_at(j, sorted.at(j));
                sorted.erase_at(j + 1);
                sorted.insert_at(j + 1, temp);
            }
        }
    }
    
    int mid = sorted.size() / 2;
    if (sorted.size() % 2 == 0) {
        // Even number of elements: average of two middle values
        return (static_cast<double>(sorted.at(mid - 1)) + 
                static_cast<double>(sorted.at(mid))) / 2.0;
    } else {
        // Odd number of elements: middle value
        return static_cast<double>(sorted.at(mid));
    }
}

// ============================================================================
// COUNT INVERSIONS - Measure sortedness
// ============================================================================
template <typename T>
int SequentialList<T>::countInversions() {
    int count = 0;
    
    // Count pairs (i,j) where i < j but list[i] > list[j]
    for (int i = 0; i < this->size() - 1; i++) {
        for (int j = i + 1; j < this->size(); j++) {
            if (this->at(i) > this->at(j)) {
                count++;
            }
        }
    }
    
    return count;
}

// ============================================================================
// ANY - Check if any element matches
// ============================================================================
template <typename T>
bool SequentialList<T>::any(std::function<bool(T)> predicate) {
    for (int i = 0; i < this->size(); i++) {
        if (predicate(this->at(i))) {
            return true;
        }
    }
    return false;
}

// ============================================================================
// ALL - Check if all elements match
// ============================================================================
template <typename T>
bool SequentialList<T>::all(std::function<bool(T)> predicate) {
    for (int i = 0; i < this->size(); i++) {
        if (!predicate(this->at(i))) {
            return false;
        }
    }
    return true;
}

// ============================================================================
// NONE - Check if no elements match
// ============================================================================
template <typename T>
bool SequentialList<T>::none(std::function<bool(T)> predicate) {
    return !any(predicate);
}

// ============================================================================
// FIND - Get first matching element
// ============================================================================
template <typename T>
T SequentialList<T>::find(std::function<bool(T)> predicate) {
    for (int i = 0; i < this->size(); i++) {
        if (predicate(this->at(i))) {
            return this->at(i);
        }
    }
    throw list_err("No element found matching predicate");
}

// ============================================================================
// CONTAINS - Check if value exists
// ============================================================================
template <typename T>
bool SequentialList<T>::contains(T value) {
    for (int i = 0; i < this->size(); i++) {
        if (this->at(i) == value) {
            return true;
        }
    }
    return false;
}

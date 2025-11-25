/*
 * Implementation of Functional Operations for SequentialList
 * 
 * These are template implementations, so they must be in the header
 * or included by it. This file is included at the end of SequentialList.h
 */

#include "VectorList.h"

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

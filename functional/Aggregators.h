#pragma once

#include <functional>
#include <stdexcept>
#include "../containers/AbstractList.h"
#include "../containers/SequentialList.h"
#include "FunctionalOps.h"

/**
 * Aggregation Operations Module
 * 
 * Provides common aggregation functions for numeric and comparable types.
 * These are built on top of the functional operations (reduce, forEach, etc.)
 */

namespace functional {

/**
 * SUM: Calculate sum of all elements
 * Requires T to support operator+
 */
template<typename T>
T sum(AbstractList<T>& source) {
    if (source.size() == 0) {
        return T(); // Return default-constructed value for empty list
    }
    return reduce<T>(source, [](T a, T b) { return a + b; }, T());
}

/**
 * AVERAGE: Calculate average of all elements
 * Requires T to support operator+ and operator/
 */
template<typename T>
double average(AbstractList<T>& source) {
    if (source.size() == 0) {
        throw std::runtime_error("Cannot calculate average of empty list");
    }
    T total = sum<T>(source);
    return static_cast<double>(total) / source.size();
}

/**
 * MINIMUM: Find minimum element
 * Requires T to support operator<
 */
template<typename T>
T minimum(AbstractList<T>& source) {
    if (source.size() == 0) {
        throw std::runtime_error("Cannot find minimum of empty list");
    }
    
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        T min = seqList.at(0);
        for (int i = 1; i < source.size(); i++) {
            T current = seqList.at(i);
            if (current < min) {
                min = current;
            }
        }
        return min;
    }
    
    throw std::runtime_error("Minimum operation requires SequentialList");
}

/**
 * MAXIMUM: Find maximum element
 * Requires T to support operator>
 */
template<typename T>
T maximum(AbstractList<T>& source) {
    if (source.size() == 0) {
        throw std::runtime_error("Cannot find maximum of empty list");
    }
    
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        T max = seqList.at(0);
        for (int i = 1; i < source.size(); i++) {
            T current = seqList.at(i);
            if (current > max) {
                max = current;
            }
        }
        return max;
    }
    
    throw std::runtime_error("Maximum operation requires SequentialList");
}

/**
 * PRODUCT: Calculate product of all elements
 * Requires T to support operator*
 */
template<typename T>
T product(AbstractList<T>& source) {
    if (source.size() == 0) {
        return T(1); // Multiplicative identity
    }
    return reduce<T>(source, [](T a, T b) { return a * b; }, T(1));
}

/**
 * COUNT_IF: Count elements satisfying a condition
 */
template<typename T>
int countIf(AbstractList<T>& source, std::function<bool(T)> predicate) {
    int count = 0;
    forEach<T>(source, [&count, &predicate](T item) {
        if (predicate(item)) {
            count++;
        }
    });
    return count;
}

/**
 * FIND_IF: Find first element satisfying a predicate
 * Returns index of first match, or -1 if not found
 */
template<typename T>
int findIf(SequentialList<T>& source, std::function<bool(T)> predicate) {
    for (int i = 0; i < source.size(); i++) {
        if (predicate(source.at(i))) {
            return i;
        }
    }
    return -1;
}

} // namespace functional

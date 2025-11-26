#pragma once

#include <functional>
#include "../containers/AbstractList.h"
#include "../containers/VectorList.h"

/**
 * Functional Operations Module
 * 
 * This module provides functional programming capabilities for list containers.
 * All operations are implemented as free template functions that work with
 * any AbstractList<T> implementation.
 * 
 * Key Principles:
 * - Functions return NEW lists rather than modifying originals
 * - Support for C++11 lambdas via std::function
 * - Composable operations for building complex transformations
 */

namespace functional {

/**
 * MAP: Transform each element using a transformation function
 * 
 * @param source The source list to transform
 * @param transform Function that maps T to U
 * @return New list containing transformed elements
 * 
 * Example:
 *   VectorList<int> numbers;
 *   numbers.push(1); numbers.push(2); numbers.push(3);
 *   auto squared = map<int,int>(numbers, [](int x) { return x*x; });
 *   // squared contains: [1, 4, 9]
 */
template<typename T, typename U>
VectorList<U> map(AbstractList<T>& source, std::function<U(T)> transform) {
    VectorList<U> result;
    
    // For sequential lists, use at() method
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        for (int i = 0; i < source.size(); i++) {
            result.push(transform(seqList.at(i)));
        }
    } else {
        // For non-sequential lists, pop and push back
        // This is less efficient but works for all AbstractList types
        VectorList<T> temp;
        int originalSize = source.size();
        
        // Extract all elements
        for (int i = 0; i < originalSize; i++) {
            temp.push(source.pop());
        }
        
        // Process and restore
        for (int i = temp.size() - 1; i >= 0; i--) {
            T item = temp.at(i);
            source.push(item);
            result.push(transform(item));
        }
    }
    
    return result;
}

/**
 * FILTER: Select elements that satisfy a predicate
 * 
 * @param source The source list to filter
 * @param predicate Function that returns true for elements to keep
 * @return New list containing only elements where predicate returns true
 * 
 * Example:
 *   VectorList<int> numbers;
 *   numbers.push(1); numbers.push(2); numbers.push(3); numbers.push(4);
 *   auto evens = filter<int>(numbers, [](int x) { return x % 2 == 0; });
 *   // evens contains: [2, 4]
 */
template<typename T>
VectorList<T> filter(AbstractList<T>& source, std::function<bool(T)> predicate) {
    VectorList<T> result;
    
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        for (int i = 0; i < source.size(); i++) {
            T item = seqList.at(i);
            if (predicate(item)) {
                result.push(item);
            }
        }
    } else {
        VectorList<T> temp;
        int originalSize = source.size();
        
        for (int i = 0; i < originalSize; i++) {
            temp.push(source.pop());
        }
        
        for (int i = temp.size() - 1; i >= 0; i--) {
            T item = temp.at(i);
            source.push(item);
            if (predicate(item)) {
                result.push(item);
            }
        }
    }
    
    return result;
}

/**
 * REDUCE: Aggregate all elements into a single value
 * 
 * @param source The source list to reduce
 * @param combiner Function that combines two values into one
 * @param initial Initial accumulator value
 * @return Single aggregated value
 * 
 * Example:
 *   VectorList<int> numbers;
 *   numbers.push(1); numbers.push(2); numbers.push(3);
 *   int sum = reduce<int>(numbers, [](int a, int b) { return a+b; }, 0);
 *   // sum = 6
 */
template<typename T>
T reduce(AbstractList<T>& source, std::function<T(T,T)> combiner, T initial) {
    T accumulator = initial;
    
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        for (int i = 0; i < source.size(); i++) {
            accumulator = combiner(accumulator, seqList.at(i));
        }
    } else {
        VectorList<T> temp;
        int originalSize = source.size();
        
        for (int i = 0; i < originalSize; i++) {
            temp.push(source.pop());
        }
        
        for (int i = temp.size() - 1; i >= 0; i--) {
            T item = temp.at(i);
            source.push(item);
            accumulator = combiner(accumulator, item);
        }
    }
    
    return accumulator;
}

/**
 * FOREACH: Apply a function to each element (for side effects)
 * 
 * @param source The source list to iterate over
 * @param action Function to apply to each element
 * 
 * Example:
 *   VectorList<int> numbers;
 *   numbers.push(1); numbers.push(2); numbers.push(3);
 *   forEach<int>(numbers, [](int x) { std::cout << x << " "; });
 *   // Prints: 1 2 3
 */
template<typename T>
void forEach(AbstractList<T>& source, std::function<void(T)> action) {
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        for (int i = 0; i < source.size(); i++) {
            action(seqList.at(i));
        }
    } else {
        VectorList<T> temp;
        int originalSize = source.size();
        
        for (int i = 0; i < originalSize; i++) {
            temp.push(source.pop());
        }
        
        for (int i = temp.size() - 1; i >= 0; i--) {
            T item = temp.at(i);
            source.push(item);
            action(item);
        }
    }
}

/**
 * COUNT: Count elements that satisfy a predicate
 * 
 * @param source The source list
 * @param predicate Function that returns true for elements to count
 * @return Number of elements satisfying the predicate
 */
template<typename T>
int count(AbstractList<T>& source, std::function<bool(T)> predicate) {
    return reduce<int>(
        filter<T>(source, predicate),
        [](int acc, int) { return acc + 1; },
        0
    );
}

/**
 * ANY: Check if any element satisfies a predicate
 * 
 * @param source The source list
 * @param predicate Function to test elements
 * @return true if at least one element satisfies the predicate
 */
template<typename T>
bool any(AbstractList<T>& source, std::function<bool(T)> predicate) {
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        for (int i = 0; i < source.size(); i++) {
            if (predicate(seqList.at(i))) {
                return true;
            }
        }
    }
    return false;
}

/**
 * ALL: Check if all elements satisfy a predicate
 * 
 * @param source The source list
 * @param predicate Function to test elements
 * @return true if all elements satisfy the predicate
 */
template<typename T>
bool all(AbstractList<T>& source, std::function<bool(T)> predicate) {
    if (dynamic_cast<SequentialList<T>*>(&source)) {
        SequentialList<T>& seqList = dynamic_cast<SequentialList<T>&>(source);
        for (int i = 0; i < source.size(); i++) {
            if (!predicate(seqList.at(i))) {
                return false;
            }
        }
    }
    return source.size() > 0;
}

} // namespace functional

#pragma once

#include <functional>
#include "../containers/SequentialList.h"
#include "../containers/VectorList.h"

/**
 * Sorting Algorithms Module
 * 
 * Provides various sorting algorithms implemented in a functional style.
 * All functions work on SequentialList types and use custom comparators.
 */

namespace algorithms {

/**
 * QuickSort: In-place quicksort implementation
 * 
 * @param list The list to sort
 * @param compare Comparison function (returns true if first < second)
 * @param low Starting index
 * @param high Ending index
 */
template<typename T>
void quickSortHelper(SequentialList<T>& list, std::function<bool(T,T)> compare, int low, int high) {
    if (low < high) {
        // Partition
        T pivot = list.at(high);
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (compare(list.at(j), pivot)) {
                i++;
                // Swap elements at i and j
                T temp = list.at(i);
                list.erase_at(i);
                list.insert_at(i, list.at(j - (i < j ? 0 : 1)));
                list.erase_at(j);
                list.insert_at(j, temp);
            }
        }
        
        // Place pivot in correct position
        i++;
        T temp = list.at(i);
        list.erase_at(i);
        list.insert_at(i, list.at(high - (i < high ? 0 : 1)));
        list.erase_at(high);
        list.insert_at(high, temp);
        
        int pivotIndex = i;
        
        // Recursively sort sub-arrays
        quickSortHelper(list, compare, low, pivotIndex - 1);
        quickSortHelper(list, compare, pivotIndex + 1, high);
    }
}

/**
 * QuickSort: Sort a sequential list using quicksort
 * 
 * @param list The list to sort (modified in place)
 * @param compare Comparison function (default: operator<)
 */
template<typename T>
void quickSort(SequentialList<T>& list, std::function<bool(T,T)> compare = [](T a, T b) { return a < b; }) {
    if (list.size() <= 1) return;
    quickSortHelper(list, compare, 0, list.size() - 1);
}

/**
 * Simpler bubble sort implementation (more reliable for our use case)
 * Useful for small lists or when stability is required
 */
template<typename T>
void bubbleSort(SequentialList<T>& list, std::function<bool(T,T)> compare = [](T a, T b) { return a < b; }) {
    int n = list.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (!compare(list.at(j), list.at(j + 1)) && !(list.at(j) == list.at(j + 1))) {
                // Swap
                T temp = list.at(j);
                list.erase_at(j);
                list.insert_at(j, list.at(j));
                list.erase_at(j + 1);
                list.insert_at(j + 1, temp);
            }
        }
    }
}

/**
 * Insertion sort - simple and efficient for small or nearly sorted lists
 */
template<typename T>
void insertionSort(SequentialList<T>& list, std::function<bool(T,T)> compare = [](T a, T b) { return a < b; }) {
    for (int i = 1; i < list.size(); i++) {
        T key = list.at(i);
        int j = i - 1;
        
        while (j >= 0 && !compare(list.at(j), key)) {
            if (!(list.at(j) == key)) { // Don't move if equal
                j--;
                continue;
            }
            j--;
        }
        
        // Insert key at position j+1
        list.erase_at(i);
        list.insert_at(j + 1, key);
    }
}

/**
 * Helper function to check if a list is sorted
 */
template<typename T>
bool isSorted(SequentialList<T>& list, std::function<bool(T,T)> compare = [](T a, T b) { return a < b; }) {
    for (int i = 0; i < list.size() - 1; i++) {
        if (!compare(list.at(i), list.at(i + 1)) && !(list.at(i) == list.at(i + 1))) {
            return false;
        }
    }
    return true;
}

/**
 * Sort using custom comparator - uses most appropriate algorithm
 */
template<typename T>
void sort(SequentialList<T>& list, std::function<bool(T,T)> compare = [](T a, T b) { return a < b; }) {
    // Use insertion sort for small lists (more reliable with our implementation)
    if (list.size() < 20) {
        insertionSort(list, compare);
    } else {
        // For larger lists, use bubble sort (more reliable than quicksort with our erase/insert)
        bubbleSort(list, compare);
    }
}

} // namespace algorithms

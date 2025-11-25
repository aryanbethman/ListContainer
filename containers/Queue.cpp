#include "Queue.h"

// --- Public Methods ---
template <typename T>
void Queue<T>::push(T item) {
    // Add to the back of the list
    storage.insert_at(storage.size(), item);
}

template <typename T>
T Queue<T>::pop() {
    if (storage.size() == 0) {
        throw list_err("Cannot pop from an empty Queue");
    }
    // Remove from the front of the list
    T val = storage.at(0);
    storage.erase_at(0);
    return val;
}

template <typename T>
int Queue<T>::size() {
    return storage.size();
}

template <typename T>
void Queue<T>::clear() {
    storage.clear();
}

template <typename T>
const char* Queue<T>::name() {
    return "Queue";
}

template <typename T>
T Queue<T>::front() {
    if (storage.size() == 0) {
        throw list_err("Cannot get front of an empty Queue");
    }
    return storage.at(0);
}

// --- Forbidden Methods ---
template <typename T>
void Queue<T>::insert_at(int pos, T item) {
    throw list_err("insert_at is not a valid operation for a Queue");
}

template <typename T>
void Queue<T>::erase_at(int pos) {
    throw list_err("erase_at is not a valid operation for a Queue");
}

template <typename T>
T Queue<T>::at(int pos) {
    throw list_err("at is not a valid operation for a Queue");
}

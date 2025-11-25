#include "Deque.h"

// --- Public Methods ---
template <typename T>
void Deque<T>::push(T item) {
    // Default push adds to the back
    storage.insert_at(storage.size(), item);
}

template <typename T>
T Deque<T>::pop() {
    // Default pop removes from the back
    if (storage.size() == 0) {
        throw list_err("Cannot pop from an empty Deque");
    }
    return storage.pop(); // LinkedList's pop is from the back
}

template <typename T>
int Deque<T>::size() {
    return storage.size();
}

template <typename T>
void Deque<T>::clear() {
    storage.clear();
}

template <typename T>
const char* Deque<T>::name() {
    return "Deque";
}

// --- Deque Specific Methods ---
template <typename T>
void Deque<T>::push_front(T item) {
    storage.insert_at(0, item);
}

template <typename T>
T Deque<T>::pop_front() {
    if (storage.size() == 0) {
        throw list_err("Cannot pop_front from an empty Deque");
    }
    T val = storage.at(0);
    storage.erase_at(0);
    return val;
}

template <typename T>
T Deque<T>::front() {
    if (storage.size() == 0) {
        throw list_err("Cannot get front of an empty Deque");
    }
    return storage.at(0);
}

template <typename T>
T Deque<T>::back() {
    if (storage.size() == 0) {
        throw list_err("Cannot get back of an empty Deque");
    }
    return storage.at(storage.size() - 1);
}

// --- Forbidden Methods ---
template <typename T>
void Deque<T>::insert_at(int pos, T item) {
    throw list_err("insert_at is not a valid operation for a Deque");
}

template <typename T>
void Deque<T>::erase_at(int pos) {
    throw list_err("erase_at is not a valid operation for a Deque");
}

template <typename T>
T Deque<T>::at(int pos) {
    throw list_err("at is not a valid operation for a Deque");
}

#include "Stack.h"

template <typename T>
void Stack<T>::push(T item) {
    storage.push(item);
}

template <typename T>
T Stack<T>::pop() {
    if (storage.size() == 0) {
        throw list_err("Cannot pop from an empty Stack");
    }
    return storage.pop();
}

template <typename T>
int Stack<T>::size() {
    return storage.size();
}

template <typename T>
void Stack<T>::clear() {
    storage.clear();
}

template <typename T>
const char* Stack<T>::name() {
    return "Stack";
}

template <typename T>
T Stack<T>::top() {
    if (storage.size() == 0) {
        throw list_err("Cannot top an empty Stack");
    }
    return storage.at(storage.size() - 1);
}

// --- Forbidden Methods ---
template <typename T>
void Stack<T>::insert_at(int pos, T item) {
    throw list_err("insert_at is not a valid operation for a Stack");
}

template <typename T>
void Stack<T>::erase_at(int pos) {
    throw list_err("erase_at is not a valid operation for a Stack");
}

template <typename T>
T Stack<T>::at(int pos) {
    throw list_err("at is not a valid operation for a Stack");
}

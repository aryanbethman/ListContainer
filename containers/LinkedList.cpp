#include "LinkedList.h"

// --- Constructor ---
template <typename T>
LinkedList<T>::LinkedList() {
    _size = 0;
    sentinel.head_node = &sentinel;
}

// --- Destructor ---
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// --- Private Helper ---
template <typename T>
ListNode<T>* LinkedList<T>::node_at(int pos) {
    if (pos < 0 || pos >= _size) {
        return nullptr;
    }
    ListNode<T>* current = sentinel.next;
    for (int i = 0; i < pos; ++i) {
        current = current->next;
    }
    return current;
}

// --- Public Methods ---
template <typename T>
void LinkedList<T>::push(T item) {
    // Pushes to the back of the list
    insert_at(_size, item);
}

template <typename T>
T LinkedList<T>::pop() {
    // Pops from the back of the list
    if (_size == 0) {
        throw list_err("Cannot pop from an empty LinkedList");
    }
    T val = sentinel.prev->val;
    erase_at(_size - 1);
    return val;
}

template <typename T>
int LinkedList<T>::size() {
    return _size;
}

template <typename T>
void LinkedList<T>::clear() {
    while (_size > 0) {
        erase_at(0);
    }
}

template <typename T>
const char* LinkedList<T>::name() {
    return "LinkedList";
}

template <typename T>
void LinkedList<T>::insert_at(int pos, T item) {
    if (pos < 0 || pos > _size) {
        throw list_err("Index out of bounds for insert_at");
    }

    ListNode<T>* new_node = new ListNode<T>();
    new_node->val = item;

    ListNode<T>* target_node = (pos == _size) ? &sentinel : node_at(pos);
    
    target_node->insert_before(new_node);
    _size++;
}

template <typename T>
void LinkedList<T>::erase_at(int pos) {
    if (pos < 0 || pos >= _size) {
        throw list_err("Index out of bounds for erase_at");
    }
    ListNode<T>* target_node = node_at(pos);
    target_node->remove();
    delete target_node;
    _size--;
}

template <typename T>
T LinkedList<T>::at(int pos) {
    if (pos < 0 || pos >= _size) {
        throw list_err("Index out of bounds for at");
    }
    return node_at(pos)->val;
}

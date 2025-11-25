#include "Heap.h"

// --- Heap Helpers ---
template <typename T>
void Heap<T>::sift_up(int index) {
    // Sift up until the heap property is restored (for a min-heap)
    while (index > 0 && storage.at(index) < storage.at(parent(index))) {
        storage.swap(parent(index), index);
        index = parent(index);
    }
}

template <typename T>
void Heap<T>::sift_down(int index) {
    int min_index = index;

    int l = left_child(index);
    if (l < size() && storage.at(l) < storage.at(min_index)) {
        min_index = l;
    }

    int r = right_child(index);
    if (r < size() && storage.at(r) < storage.at(min_index)) {
        min_index = r;
    }

    if (index != min_index) {
        storage.swap(index, min_index);
        sift_down(min_index);
    }
}

// --- Public Methods ---
template <typename T>
void Heap<T>::push(T item) {
    storage.push(item);
    sift_up(size() - 1);
}

template <typename T>
T Heap<T>::pop() {
    if (size() == 0) {
        throw list_err("Cannot pop from an empty Heap");
    }
    T result = storage.at(0);
    T last_item = storage.pop(); // Pop from the end
    
    if (size() > 0) {
        storage.set_at(0, last_item); // Move last item to the root
        sift_down(0); // Restore heap property
    }
    
    return result;
}

template <typename T>
int Heap<T>::size() {
    return storage.size();
}

template <typename T>
void Heap<T>::clear() {
    storage.clear();
}

template <typename T>
const char* Heap<T>::name() {
    return "Heap";
}

template <typename T>
T Heap<T>::top() {
    if (size() == 0) {
        throw list_err("Cannot top an empty Heap");
    }
    return storage.at(0);
}

template <typename T>
void Heap<T>::heapify() {
    // Start from the last non-leaf node and sift down
    for (int i = (size() / 2) - 1; i >= 0; --i) {
        sift_down(i);
    }
}

template <typename T>
T Heap<T>::at(int pos) {
    if (pos < 0 || pos >= size()) {
        throw list_err("Index out of bounds for at");
    }
    return storage.at(pos);
}

#include "VectorList.h"

// --- Constructor ---
template <typename T>
VectorList<T>::VectorList() {
    _capacity = 2; // Initial capacity
    _size = 0;
    _data = new T[_capacity];
}

// --- Copy Constructor (Deep Copy) ---
template <typename T>
VectorList<T>::VectorList(const VectorList<T>& other) {
    _capacity = other._capacity;
    _size = other._size;
    _data = new T[_capacity];
    
    // Deep copy all elements
    for (int i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

// --- Assignment Operator (Deep Copy) ---
template <typename T>
VectorList<T>& VectorList<T>::operator=(const VectorList<T>& other) {
    // Check for self-assignment
    if (this == &other) {
        return *this;
    }
    
    // Delete old data
    delete[] _data;
    
    // Copy from other
    _capacity = other._capacity;
    _size = other._size;
    _data = new T[_capacity];
    
    for (int i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
    
    return *this;
}

// --- Destructor ---
template <typename T>
VectorList<T>::~VectorList() {
    delete[] _data;
}

// --- Private resize helper ---
template <typename T>
void VectorList<T>::resize(int new_capacity) {
    T* new_data = new T[new_capacity];
    for (int i = 0; i < _size; ++i) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
}

// --- Public Methods ---
template <typename T>
void VectorList<T>::push(T item) {
    if (_size == _capacity) {
        resize(_capacity * 2);
    }
    _data[_size] = item;
    _size++;
}

template <typename T>
T VectorList<T>::pop() {
    if (_size == 0) {
        throw list_err("Cannot pop from an empty VectorList");
    }
    _size--;
    return _data[_size];
}

template <typename T>
int VectorList<T>::size() {
    return _size;
}

template <typename T>
void VectorList<T>::clear() {
    _size = 0;
}

template <typename T>
const char* VectorList<T>::name() {
    return "VectorList";
}

template <typename T>
void VectorList<T>::insert_at(int pos, T item) {
    if (pos < 0 || pos > _size) {
        throw list_err("Index out of bounds for insert_at");
    }
    if (_size == _capacity) {
        resize(_capacity * 2);
    }
    // Shift elements to the right
    for (int i = _size; i > pos; --i) {
        _data[i] = _data[i - 1];
    }
    _data[pos] = item;
    _size++;
}

template <typename T>
void VectorList<T>::erase_at(int pos) {
    if (pos < 0 || pos >= _size) {
        throw list_err("Index out of bounds for erase_at");
    }
    // Shift elements to the left
    for (int i = pos; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
    }
    _size--;
}

template <typename T>
T VectorList<T>::at(int pos) {
    if (pos < 0 || pos >= _size) {
        throw list_err("Index out of bounds for at");
    }
    return _data[pos];
}

template <typename T>
void VectorList<T>::swap(int pos1, int pos2) {
    if (pos1 < 0 || pos1 >= _size || pos2 < 0 || pos2 >= _size) {
        throw list_err("Index out of bounds for swap");
    }
    T temp = _data[pos1];
    _data[pos1] = _data[pos2];
    _data[pos2] = temp;
}

template <typename T>
void VectorList<T>::set_at(int pos, T item) {
    if (pos < 0 || pos >= _size) {
        throw list_err("Index out of bounds for set_at");
    }
    _data[pos] = item;
}

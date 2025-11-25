#include <iostream>
#include <cassert>
#include <string>
#include "../containers/Heap.h"

void test_heap() {
    std::cout << "Running tests for Heap..." << std::endl;

    Heap<int> heap;

    // Test name()
    assert(std::string(heap.name()) == "Heap");

    // Test push() - should maintain min-heap property
    heap.push(30);
    heap.push(20);
    heap.push(10);
    assert(heap.size() == 3);
    assert(heap.top() == 10);

    // Test pop() - should always return the smallest item
    assert(heap.pop() == 10);
    assert(heap.top() == 20);
    assert(heap.pop() == 20);
    assert(heap.top() == 30);
    assert(heap.pop() == 30);
    assert(heap.size() == 0);

    // Test heapify()
    heap.clear();
    heap.push(50); // Not pushing in order
    heap.push(10);
    heap.push(40);
    heap.push(20);
    heap.push(30);
    // Manually call heapify to fix the order
    heap.heapify();
    assert(heap.top() == 10);
    assert(heap.pop() == 10);
    assert(heap.top() == 20);
    assert(heap.pop() == 20);
    assert(heap.top() == 30);

    std::cout << "Heap tests passed!" << std::endl;
}

// Custom struct for testing
struct Person {
    std::string name;
    int age;

    bool operator>(const Person& other) const {
        return age > other.age;
    }
    // Needed for assertion
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }

    // Overload the < operator, which is used by the heap implementation
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

void test_heap_custom() {
    std::cout << "Running custom type tests for Heap..." << std::endl;
    Heap<Person> heap;
    // Push items in wrong order
    heap.push({"David", 50});
    heap.push({"Eve", 20});
    heap.push({"Frank", 45});

    // Heapify should fix the order
    heap.heapify();
    assert(heap.top().name == "Eve");
    assert(heap.pop().name == "Eve");
    assert(heap.top().name == "Frank");

    std::cout << "Heap custom type tests passed!" << std::endl;
}

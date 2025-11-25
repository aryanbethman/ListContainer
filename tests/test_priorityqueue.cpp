#include <iostream>
#include <cassert>
#include <string>
#include "../containers/PriorityQueue.h"

void test_priority_queue() {
    std::cout << "Running tests for PriorityQueue..." << std::endl;

    PriorityQueue<int> pq;

    // Test name()
    assert(std::string(pq.name()) == "PriorityQueue");

    // Test push() - should maintain min-heap property
    pq.push(30);
    pq.push(20);
    pq.push(10);
    assert(pq.size() == 3);
    assert(pq.top() == 10);

    // Test pop() - should always return the smallest item
    assert(pq.pop() == 10);
    assert(pq.top() == 20);
    assert(pq.pop() == 20);
    assert(pq.top() == 30);
    assert(pq.pop() == 30);
    assert(pq.size() == 0);

    // Test clear()
    pq.push(100);
    pq.clear();
    assert(pq.size() == 0);

    std::cout << "PriorityQueue tests passed!" << std::endl;
}

// Custom struct for testing
struct Person {
    std::string name;
    int age;

    // Overload the > operator for the min-heap comparison
    bool operator>(const Person& other) const {
        return age > other.age;
    }

    // Overload the < operator, which is used by the heap implementation
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

void test_priority_queue_custom() {
    std::cout << "Running custom type tests for PriorityQueue..." << std::endl;
    PriorityQueue<Person> pq;

    pq.push({"Carol", 30});
    pq.push({"Alice", 25});
    pq.push({"Bob", 40});

    assert(pq.size() == 3);
    assert(pq.top().name == "Alice"); // Alice is youngest, so highest priority

    assert(pq.pop().name == "Alice");
    assert(pq.pop().name == "Carol");
    assert(pq.pop().name == "Bob");

    assert(pq.size() == 0);
    std::cout << "PriorityQueue custom type tests passed!" << std::endl;
}

#include <iostream>
#include <cassert>
#include <string>
#include "../containers/Deque.h"

void test_deque() {
    std::cout << "Running tests for Deque..." << std::endl;

    Deque<int> d;

    // Test name()
    assert(std::string(d.name()) == "Deque");

    // Test default push (back) and push_front
    d.push(20);       // [20]
    d.push_front(10); // [10, 20]
    d.push(30);       // [10, 20, 30]
    assert(d.size() == 3);

    // Test front() and back()
    assert(d.front() == 10);
    assert(d.back() == 30);
    assert(d.size() == 3);

    // Test default pop (back) and pop_front
    assert(d.pop() == 30);       // [10, 20]
    assert(d.pop_front() == 10); // [20]
    assert(d.front() == 20);
    assert(d.back() == 20);
    assert(d.size() == 1);

    // Test clear()
    d.clear();
    assert(d.size() == 0);

    // Test exceptions
    bool thrown = false;
    try { d.pop(); } catch (const list_err& e) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { d.pop_front(); } catch (const list_err& e) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { d.front(); } catch (const list_err& e) { thrown = true; }
    assert(thrown);

    thrown = false;
    try { d.back(); } catch (const list_err& e) { thrown = true; }
    assert(thrown);

    std::cout << "Deque tests passed!" << std::endl;
}

void test_deque_string() {
    std::cout << "Running string tests for Deque..." << std::endl;
    Deque<std::string> d;
    d.push("middle");
    d.push_front("front");
    d.push("back");
    assert(d.size() == 3);
    assert(d.front() == "front");
    assert(d.back() == "back");
    assert(d.pop_front() == "front");
    assert(d.pop() == "back");
    assert(d.front() == "middle");
    std::cout << "Deque string tests passed!" << std::endl;
}

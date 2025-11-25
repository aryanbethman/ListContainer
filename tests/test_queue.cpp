#include <iostream>
#include <cassert>
#include <string>
#include "../containers/Queue.h"

void test_queue() {
    std::cout << "Running tests for Queue..." << std::endl;

    Queue<int> q;

    // Test name()
    assert(std::string(q.name()) == "Queue");

    // Test push() and size()
    q.push(10);
    q.push(20);
    q.push(30);
    assert(q.size() == 3);

    // Test front()
    assert(q.front() == 10);
    assert(q.size() == 3); // front() should not remove the item

    // Test pop() - FIFO
    assert(q.pop() == 10);
    assert(q.front() == 20);
    assert(q.pop() == 20);
    assert(q.pop() == 30);
    assert(q.size() == 0);

    // Test clear()
    q.push(100);
    q.push(200);
    q.clear();
    assert(q.size() == 0);

    // Test exceptions
    bool thrown = false;
    try {
        q.pop();
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        q.front();
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    std::cout << "Queue tests passed!" << std::endl;
}

void test_queue_string() {
    std::cout << "Running string tests for Queue..." << std::endl;
    Queue<std::string> q;
    q.push("first in");
    q.push("second in");
    assert(q.size() == 2);
    assert(q.front() == "first in");
    assert(q.pop() == "first in");
    assert(q.front() == "second in");
    assert(q.size() == 1);
    std::cout << "Queue string tests passed!" << std::endl;
}

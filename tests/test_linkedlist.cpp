#include <iostream>
#include <cassert>
#include <string>
#include "../containers/LinkedList.h"

void test_linked_list() {
    std::cout << "Running tests for LinkedList..." << std::endl;

    LinkedList<int> ll;

    // Test name()
    assert(std::string(ll.name()) == "LinkedList");

    // Test push() and size()
    ll.push(10);
    ll.push(20);
    ll.push(30);
    assert(ll.size() == 3);

    // Test at()
    assert(ll.at(0) == 10);
    assert(ll.at(1) == 20);
    assert(ll.at(2) == 30);

    // Test pop()
    assert(ll.pop() == 30);
    assert(ll.size() == 2);

    // Test insert_at()
    ll.insert_at(1, 99); // Insert 99 between 10 and 20
    assert(ll.size() == 3);
    assert(ll.at(0) == 10);
    assert(ll.at(1) == 99);
    assert(ll.at(2) == 20);

    // Test erase_at()
    ll.erase_at(0); // Erase 10
    assert(ll.size() == 2);
    assert(ll.at(0) == 99);
    assert(ll.at(1) == 20);

    // Test clear()
    ll.clear();
    assert(ll.size() == 0);

    // Test exceptions
    bool thrown = false;
    try {
        ll.pop();
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        ll.at(0);
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    std::cout << "LinkedList tests passed!" << std::endl;
}

void test_linked_list_string() {
    std::cout << "Running string tests for LinkedList..." << std::endl;
    LinkedList<std::string> ll;
    ll.push("alpha");
    ll.push("beta");
    ll.insert_at(0, "gamma");
    assert(ll.size() == 3);
    assert(ll.at(0) == "gamma");
    assert(ll.at(1) == "alpha");
    assert(ll.pop() == "beta");
    assert(ll.size() == 2);
    std::cout << "LinkedList string tests passed!" << std::endl;
}

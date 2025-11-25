#include <iostream>
#include <cassert>
#include "../containers/VectorList.h"

void test_vector_list() {
    std::cout << "Running tests for VectorList..." << std::endl;

    VectorList<int> vec;

    // Test name()
    assert(std::string(vec.name()) == "VectorList");

    // Test push() and size()
    vec.push(10);
    vec.push(20);
    vec.push(30);
    assert(vec.size() == 3);

    // Test at()
    assert(vec.at(0) == 10);
    assert(vec.at(1) == 20);
    assert(vec.at(2) == 30);

    // Test pop()
    assert(vec.pop() == 30);
    assert(vec.size() == 2);

    // Test insert_at()
    vec.insert_at(1, 99); // Insert 99 between 10 and 20
    assert(vec.size() == 3);
    assert(vec.at(0) == 10);
    assert(vec.at(1) == 99);
    assert(vec.at(2) == 20);

    // Test erase_at()
    vec.erase_at(0); // Erase 10
    assert(vec.size() == 2);
    assert(vec.at(0) == 99);
    assert(vec.at(1) == 20);

    // Test clear()
    vec.clear();
    assert(vec.size() == 0);

    // Test exceptions
    bool thrown = false;
    try {
        vec.pop();
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        vec.at(0);
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    std::cout << "VectorList tests passed!" << std::endl;
}

void test_vector_list_string() {
    std::cout << "Running string tests for VectorList..." << std::endl;
    VectorList<std::string> vec;
    vec.push("hello");
    vec.push("world");
    assert(vec.size() == 2);
    assert(vec.at(0) == "hello");
    assert(vec.pop() == "world");
    assert(vec.size() == 1);
    vec.clear();
    assert(vec.size() == 0);
    std::cout << "VectorList string tests passed!" << std::endl;
}

void test_vector_list_resize() {
    std::cout << "Running resize tests for VectorList..." << std::endl;
    VectorList<int> vec;
    for (int i = 0; i < 1000; ++i) {
        vec.push(i);
    }
    assert(vec.size() == 1000);
    assert(vec.at(999) == 999);
    assert(vec.pop() == 999);
    assert(vec.size() == 999);
    std::cout << "VectorList resize tests passed!" << std::endl;
}

#include <iostream>
#include <cassert>
#include <string>
#include "../containers/Stack.h"

void test_stack() {
    std::cout << "Running tests for Stack..." << std::endl;

    Stack<int> stack;

    // Test name()
    assert(std::string(stack.name()) == "Stack");

    // Test push() and size()
    stack.push(10);
    stack.push(20);
    stack.push(30);
    assert(stack.size() == 3);

    // Test top()
    assert(stack.top() == 30);
    assert(stack.size() == 3); // top() should not remove the item

    // Test pop()
    assert(stack.pop() == 30);
    assert(stack.top() == 20);
    assert(stack.pop() == 20);
    assert(stack.pop() == 10);
    assert(stack.size() == 0);

    // Test clear()
    stack.push(100);
    stack.push(200);
    stack.clear();
    assert(stack.size() == 0);

    // Test exceptions
    bool thrown = false;
    try {
        stack.pop();
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    thrown = false;
    try {
        stack.top();
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);
    
    // Test forbidden methods
    thrown = false;
    try {
        stack.at(0);
    } catch (const list_err& e) {
        thrown = true;
    }
    assert(thrown);

    std::cout << "Stack tests passed!" << std::endl;
}

void test_stack_string() {
    std::cout << "Running string tests for Stack..." << std::endl;
    Stack<std::string> stack;
    stack.push("first");
    stack.push("second");
    assert(stack.size() == 2);
    assert(stack.top() == "second");
    assert(stack.pop() == "second");
    assert(stack.pop() == "first");
    assert(stack.size() == 0);
    std::cout << "Stack string tests passed!" << std::endl;
}

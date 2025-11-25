#include <iostream>
#include <string> // Needed for string tests

// Forward declarations for all test functions
void test_vector_list();
void test_vector_list_string();
void test_vector_list_resize();
void test_linked_list();
void test_linked_list_string();
void test_stack();
void test_stack_string();
void test_queue();
void test_queue_string();
void test_deque();
void test_deque_string();
void test_heap();
void test_heap_custom();
void test_priority_queue();
void test_priority_queue_custom();

int main() {
    std::cout << "--- Running Full Test Suite --- " << std::endl;
    test_vector_list();
    test_vector_list_string();
    test_vector_list_resize();
    std::cout << std::endl;

    test_linked_list();
    test_linked_list_string();
    std::cout << std::endl;

    test_stack();
    test_stack_string();
    std::cout << std::endl;

    test_queue();
    test_queue_string();
    std::cout << std::endl;

    test_deque();
    test_deque_string();
    std::cout << std::endl;

    test_heap();
    test_heap_custom();
    std::cout << std::endl;

    test_priority_queue();
    test_priority_queue_custom();

    std::cout << "\n--- All Tests Passed Successfully! --- " << std::endl;
    return 0;
}
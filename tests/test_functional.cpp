/*
 * Test Suite for Functional Operations
 * 
 * This file demonstrates the desired API for functional programming features
 * added to the ListContainer library. Tests are written in TDD style:
 * write the test first, then implement to make it pass.
 * 
 * Functional Operations to Test:
 * - map: Transform each element
 * - filter: Select elements matching a predicate
 * - reduce: Aggregate elements to a single value
 * - forEach: Perform side effects on each element
 * - Method chaining: Compose operations
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include "../containers.h"

// ANSI color codes for output
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

int tests_passed = 0;
int tests_failed = 0;

void assert_test(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << GREEN << "✓ PASS: " << test_name << RESET << std::endl;
        tests_passed++;
    } else {
        std::cout << RED << "✗ FAIL: " << test_name << RESET << std::endl;
        tests_failed++;
    }
}

// ============================================================================
// TEST 1: MAP - Transform elements to same type
// ============================================================================
void test_map_same_type() {
    std::cout << "\n" << YELLOW << "=== Testing MAP (same type) ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    numbers.push(4);
    numbers.push(5);
    
    // Map: square each number
    VectorList<int> squared = numbers.map<int>([](int x) { return x * x; });
    
    assert_test(squared.size() == 5, "Map preserves size");
    assert_test(squared.at(0) == 1, "Map: 1^2 = 1");
    assert_test(squared.at(1) == 4, "Map: 2^2 = 4");
    assert_test(squared.at(2) == 9, "Map: 3^2 = 9");
    assert_test(squared.at(3) == 16, "Map: 4^2 = 16");
    assert_test(squared.at(4) == 25, "Map: 5^2 = 25");
    
    // Original list should be unchanged (immutability)
    assert_test(numbers.at(0) == 1, "Map does not modify original list");
}

// ============================================================================
// TEST 2: MAP - Transform to different type
// ============================================================================
void test_map_different_type() {
    std::cout << "\n" << YELLOW << "=== Testing MAP (type transformation) ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    
    // Map: convert int to string
    VectorList<std::string> strings = numbers.map<std::string>([](int x) {
        return std::to_string(x) + " items";
    });
    
    assert_test(strings.size() == 3, "Map with type change preserves size");
    assert_test(strings.at(0) == "1 items", "Map: int 1 -> string '1 items'");
    assert_test(strings.at(1) == "2 items", "Map: int 2 -> string '2 items'");
    assert_test(strings.at(2) == "3 items", "Map: int 3 -> string '3 items'");
}

// ============================================================================
// TEST 3: FILTER - Select matching elements
// ============================================================================
void test_filter() {
    std::cout << "\n" << YELLOW << "=== Testing FILTER ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    for (int i = 1; i <= 10; i++) {
        numbers.push(i);
    }
    
    // Filter: keep only even numbers
    VectorList<int> evens = numbers.filter([](int x) { return x % 2 == 0; });
    
    assert_test(evens.size() == 5, "Filter: 5 even numbers in 1-10");
    assert_test(evens.at(0) == 2, "Filter: first even is 2");
    assert_test(evens.at(1) == 4, "Filter: second even is 4");
    assert_test(evens.at(4) == 10, "Filter: last even is 10");
    
    // Filter: numbers greater than 7
    VectorList<int> large = numbers.filter([](int x) { return x > 7; });
    assert_test(large.size() == 3, "Filter: 3 numbers > 7");
    assert_test(large.at(0) == 8, "Filter: first large number is 8");
}

// ============================================================================
// TEST 4: REDUCE - Aggregate to single value
// ============================================================================
void test_reduce() {
    std::cout << "\n" << YELLOW << "=== Testing REDUCE ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    numbers.push(4);
    numbers.push(5);
    
    // Reduce: sum
    int sum = numbers.reduce<int>(0, [](int acc, int x) { return acc + x; });
    assert_test(sum == 15, "Reduce: sum of 1-5 = 15");
    
    // Reduce: product
    int product = numbers.reduce<int>(1, [](int acc, int x) { return acc * x; });
    assert_test(product == 120, "Reduce: product of 1-5 = 120");
    
    // Reduce: max
    int max = numbers.reduce<int>(numbers.at(0), [](int acc, int x) { 
        return (x > acc) ? x : acc; 
    });
    assert_test(max == 5, "Reduce: max of 1-5 = 5");
    
    // Reduce with type change: count elements greater than 2
    int count = numbers.reduce<int>(0, [](int acc, int x) { 
        return (x > 2) ? acc + 1 : acc; 
    });
    assert_test(count == 3, "Reduce: count of elements > 2 = 3");
}

// ============================================================================
// TEST 5: FOREACH - Side effects
// ============================================================================
void test_forEach() {
    std::cout << "\n" << YELLOW << "=== Testing FOREACH ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    
    // ForEach: accumulate in external variable
    int external_sum = 0;
    numbers.forEach([&external_sum](int x) { external_sum += x; });
    assert_test(external_sum == 6, "ForEach: side effect on external variable");
    
    // ForEach: count iterations
    int iteration_count = 0;
    numbers.forEach([&iteration_count](int x) { iteration_count++; });
    assert_test(iteration_count == 3, "ForEach: called for each element");
}

// ============================================================================
// TEST 6: METHOD CHAINING - Composition
// ============================================================================
void test_method_chaining() {
    std::cout << "\n" << YELLOW << "=== Testing METHOD CHAINING ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    for (int i = 1; i <= 10; i++) {
        numbers.push(i);
    }
    
    // Chain: filter evens, then square them, then sum
    int result = numbers
        .filter([](int x) { return x % 2 == 0; })      // {2, 4, 6, 8, 10}
        .map<int>([](int x) { return x * x; })         // {4, 16, 36, 64, 100}
        .reduce<int>(0, [](int acc, int x) { return acc + x; }); // 220
    
    assert_test(result == 220, "Chain: filter evens -> square -> sum = 220");
    
    // Verify: 2^2 + 4^2 + 6^2 + 8^2 + 10^2 = 4 + 16 + 36 + 64 + 100 = 220
}

// ============================================================================
// TEST 7: EDGE CASES - Empty lists, single elements
// ============================================================================
void test_edge_cases() {
    std::cout << "\n" << YELLOW << "=== Testing EDGE CASES ===" << RESET << std::endl;
    
    // Empty list
    VectorList<int> empty;
    
    VectorList<int> mapped_empty = empty.map<int>([](int x) { return x * 2; });
    assert_test(mapped_empty.size() == 0, "Map on empty list returns empty list");
    
    VectorList<int> filtered_empty = empty.filter([](int x) { return x > 0; });
    assert_test(filtered_empty.size() == 0, "Filter on empty list returns empty list");
    
    int reduced_empty = empty.reduce<int>(42, [](int acc, int x) { return acc + x; });
    assert_test(reduced_empty == 42, "Reduce on empty list returns initial value");
    
    // Single element
    VectorList<int> single;
    single.push(5);
    
    VectorList<int> mapped_single = single.map<int>([](int x) { return x * 3; });
    assert_test(mapped_single.size() == 1, "Map on single element list has size 1");
    assert_test(mapped_single.at(0) == 15, "Map on single element: 5 * 3 = 15");
    
    // Filter that matches nothing
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    
    VectorList<int> none = numbers.filter([](int x) { return x > 100; });
    assert_test(none.size() == 0, "Filter with no matches returns empty list");
}

// ============================================================================
// TEST 8: WORKS WITH LinkedList too
// ============================================================================
void test_linkedlist_functional() {
    std::cout << "\n" << YELLOW << "=== Testing LINKEDLIST with Functional Ops ===" << RESET << std::endl;
    
    LinkedList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    numbers.push(4);
    
    // Note: Functional operations return VectorList (design decision for consistency)
    VectorList<int> doubled = numbers.map<int>([](int x) { return x * 2; });
    assert_test(doubled.size() == 4, "LinkedList: Map preserves size");
    assert_test(doubled.at(0) == 2, "LinkedList: Map works correctly");
    
    VectorList<int> odds = numbers.filter([](int x) { return x % 2 == 1; });
    assert_test(odds.size() == 2, "LinkedList: Filter works");
    
    int sum = numbers.reduce<int>(0, [](int acc, int x) { return acc + x; });
    assert_test(sum == 10, "LinkedList: Reduce works (1+2+3+4=10)");
}

// ============================================================================
// TEST 9: COMPLEX EXAMPLE - Real-world use case
// ============================================================================
void test_real_world_example() {
    std::cout << "\n" << YELLOW << "=== Testing REAL-WORLD Example ===" << RESET << std::endl;
    
    // Scenario: Process a list of student scores
    VectorList<int> scores;
    scores.push(45);  // Fail
    scores.push(78);  // Pass
    scores.push(92);  // Pass
    scores.push(38);  // Fail
    scores.push(85);  // Pass
    scores.push(67);  // Pass
    scores.push(55);  // Pass
    
    // Calculate average of passing scores (>= 50)
    VectorList<int> passing = scores.filter([](int score) { return score >= 50; });
    int total = passing.reduce<int>(0, [](int acc, int score) { return acc + score; });
    double average = static_cast<double>(total) / passing.size();
    
    assert_test(passing.size() == 5, "Real-world: 5 students passed");
    assert_test(total == 377, "Real-world: sum of passing scores = 377");
    assert_test(std::abs(average - 75.4) < 0.1, "Real-world: average = 75.4");
}

// ============================================================================
// MAIN - Run all tests
// ============================================================================
int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Functional Operations Test Suite                     ║\n";
    std::cout << "║  Testing: map, filter, reduce, forEach, chaining      ║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
    
    test_map_same_type();
    test_map_different_type();
    test_filter();
    test_reduce();
    test_forEach();
    test_method_chaining();
    test_edge_cases();
    test_linkedlist_functional();
    test_real_world_example();
    
    // Summary
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  TEST SUMMARY                                          ║\n";
    std::cout << "╠════════════════════════════════════════════════════════╣\n";
    std::cout << "║  " << GREEN << "Passed: " << tests_passed << RESET;
    for (int i = 0; i < 46 - std::to_string(tests_passed).length(); i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "║  " << RED << "Failed: " << tests_failed << RESET;
    for (int i = 0; i < 46 - std::to_string(tests_failed).length(); i++) std::cout << " ";
    std::cout << "║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
    
    return (tests_failed == 0) ? 0 : 1;
}

/*
 * Test Suite for Advanced Aggregation Operations
 * 
 * Tests statistical and advanced functional operations:
 * - min, max, sum, average, median
 * - countInversions
 * - any, all, none
 * - find, contains
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cmath>
#include "../containers.h"

// ANSI color codes
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
// TEST 1: MIN and MAX
// ============================================================================
void test_min_max() {
    std::cout << "\n" << YELLOW << "=== Testing MIN and MAX ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(5);
    numbers.push(2);
    numbers.push(8);
    numbers.push(1);
    numbers.push(9);
    numbers.push(3);
    
    assert_test(numbers.min() == 1, "Min: finds minimum value");
    assert_test(numbers.max() == 9, "Max: finds maximum value");
    
    // Single element
    VectorList<int> single;
    single.push(42);
    assert_test(single.min() == 42, "Min: single element");
    assert_test(single.max() == 42, "Max: single element");
}

// ============================================================================
// TEST 2: SUM and AVERAGE
// ============================================================================
void test_sum_average() {
    std::cout << "\n" << YELLOW << "=== Testing SUM and AVERAGE ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    numbers.push(4);
    numbers.push(5);
    
    assert_test(numbers.sum() == 15, "Sum: 1+2+3+4+5 = 15");
    assert_test(std::abs(numbers.average() - 3.0) < 0.001, "Average: mean of 1-5 is 3.0");
    
    VectorList<int> tens;
    tens.push(10);
    tens.push(20);
    tens.push(30);
    assert_test(tens.sum() == 60, "Sum: 10+20+30 = 60");
    assert_test(std::abs(tens.average() - 20.0) < 0.001, "Average: mean is 20.0");
}

// ============================================================================
// TEST 3: MEDIAN
// ============================================================================
void test_median() {
    std::cout << "\n" << YELLOW << "=== Testing MEDIAN ===" << RESET << std::endl;
    
    // Odd number of elements
    VectorList<int> odd;
    odd.push(3);
    odd.push(1);
    odd.push(5);
    odd.push(2);
    odd.push(4);
    
    assert_test(std::abs(odd.median() - 3.0) < 0.001, "Median: odd count (3.0)");
    
    // Even number of elements
    VectorList<int> even;
    even.push(1);
    even.push(2);
    even.push(3);
    even.push(4);
    
    assert_test(std::abs(even.median() - 2.5) < 0.001, "Median: even count (2.5)");
    
    // Single element
    VectorList<int> single;
    single.push(7);
    assert_test(std::abs(single.median() - 7.0) < 0.001, "Median: single element");
}

// ============================================================================
// TEST 4: COUNT INVERSIONS
// ============================================================================
void test_inversions() {
    std::cout << "\n" << YELLOW << "=== Testing COUNT INVERSIONS ===" << RESET << std::endl;
    
    // Sorted list - 0 inversions
    VectorList<int> sorted;
    sorted.push(1);
    sorted.push(2);
    sorted.push(3);
    sorted.push(4);
    assert_test(sorted.countInversions() == 0, "Inversions: sorted list has 0");
    
    // Reverse sorted - maximum inversions
    VectorList<int> reverse;
    reverse.push(4);
    reverse.push(3);
    reverse.push(2);
    reverse.push(1);
    assert_test(reverse.countInversions() == 6, "Inversions: reverse has 6");
    // (4,3), (4,2), (4,1), (3,2), (3,1), (2,1)
    
    // Partially sorted
    VectorList<int> partial;
    partial.push(3);
    partial.push(1);
    partial.push(2);
    assert_test(partial.countInversions() == 2, "Inversions: partial has 2");
    // (3,1), (3,2)
}

// ============================================================================
// TEST 5: ANY, ALL, NONE
// ============================================================================
void test_predicates() {
    std::cout << "\n" << YELLOW << "=== Testing ANY, ALL, NONE ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(2);
    numbers.push(4);
    numbers.push(6);
    numbers.push(7);
    numbers.push(8);
    
    // ANY
    assert_test(numbers.any([](int x) { return x > 5; }), 
                "Any: at least one element > 5");
    assert_test(!numbers.any([](int x) { return x > 10; }), 
                "Any: no element > 10");
    
    // ALL
    assert_test(numbers.all([](int x) { return x > 0; }), 
                "All: all elements > 0");
    assert_test(!numbers.all([](int x) { return x % 2 == 0; }), 
                "All: not all elements are even (7 is odd)");
    
    // NONE
    assert_test(numbers.none([](int x) { return x < 0; }), 
                "None: no negative elements");
    assert_test(!numbers.none([](int x) { return x % 2 == 0; }), 
                "None: some elements are even");
}

// ============================================================================
// TEST 6: FIND
// ============================================================================
void test_find() {
    std::cout << "\n" << YELLOW << "=== Testing FIND ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);
    numbers.push(40);
    
    int found = numbers.find([](int x) { return x > 25; });
    assert_test(found == 30, "Find: first element > 25 is 30");
    
    found = numbers.find([](int x) { return x % 20 == 0; });
    assert_test(found == 20, "Find: first multiple of 20 is 20");
    
    // Test exception for no match
    bool exception_thrown = false;
    try {
        numbers.find([](int x) { return x > 100; });
    } catch (const list_err& e) {
        exception_thrown = true;
    }
    assert_test(exception_thrown, "Find: throws exception when no match");
}

// ============================================================================
// TEST 7: CONTAINS
// ============================================================================
void test_contains() {
    std::cout << "\n" << YELLOW << "=== Testing CONTAINS ===" << RESET << std::endl;
    
    VectorList<int> numbers;
    numbers.push(5);
    numbers.push(10);
    numbers.push(15);
    numbers.push(20);
    
    assert_test(numbers.contains(10), "Contains: list has 10");
    assert_test(numbers.contains(5), "Contains: list has 5");
    assert_test(!numbers.contains(7), "Contains: list doesn't have 7");
    assert_test(!numbers.contains(100), "Contains: list doesn't have 100");
}

// ============================================================================
// TEST 8: Combined Operations
// ============================================================================
void test_combined() {
    std::cout << "\n" << YELLOW << "=== Testing COMBINED Operations ===" << RESET << std::endl;
    
    // Scenario: Filter positive numbers, then compute statistics
    VectorList<int> mixed;
    mixed.push(-5);
    mixed.push(3);
    mixed.push(-2);
    mixed.push(7);
    mixed.push(1);
    mixed.push(-8);
    mixed.push(4);
    
    auto positive = mixed.filter([](int x) { return x > 0; });
    
    assert_test(positive.size() == 4, "Combined: 4 positive numbers");
    assert_test(positive.min() == 1, "Combined: min of positives is 1");
    assert_test(positive.max() == 7, "Combined: max of positives is 7");
    assert_test(positive.sum() == 15, "Combined: sum of positives is 15");
    assert_test(std::abs(positive.average() - 3.75) < 0.001, 
                "Combined: average of positives is 3.75");
}

// ============================================================================
// TEST 9: Real-World Example - Student Scores
// ============================================================================
void test_real_world() {
    std::cout << "\n" << YELLOW << "=== Testing REAL-WORLD Example ===" << RESET << std::endl;
    
    VectorList<int> scores;
    scores.push(85);
    scores.push(92);
    scores.push(78);
    scores.push(95);
    scores.push(88);
    scores.push(76);
    scores.push(90);
    
    // Statistics
    int highest = scores.max();
    int lowest = scores.min();
    double avg = scores.average();
    double med = scores.median();
    
    assert_test(highest == 95, "Real-world: highest score is 95");
    assert_test(lowest == 76, "Real-world: lowest score is 76");
    assert_test(std::abs(avg - 86.29) < 0.1, "Real-world: average ~86.29");
    assert_test(std::abs(med - 88.0) < 0.1, "Real-world: median is 88");
    
    // Queries
    bool hasExcellent = scores.any([](int s) { return s >= 90; });
    bool allPassing = scores.all([](int s) { return s >= 60; });
    int excellentCount = scores.filter([](int s) { return s >= 90; }).size();
    
    assert_test(hasExcellent, "Real-world: has excellent scores (>=90)");
    assert_test(allPassing, "Real-world: all scores are passing");
    assert_test(excellentCount == 3, "Real-world: 3 excellent scores");
}

// ============================================================================
// MAIN
// ============================================================================
int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Advanced Aggregations Test Suite                     ║\n";
    std::cout << "║  Testing: statistical and functional operations       ║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
    
    test_min_max();
    test_sum_average();
    test_median();
    test_inversions();
    test_predicates();
    test_find();
    test_contains();
    test_combined();
    test_real_world();
    
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

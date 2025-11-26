#include <iostream>
#include <cassert>
#include "../containers.h"
#include "../functional/FunctionalOps.h"
#include "../functional/Aggregators.h"

using namespace std;
using namespace functional;

void test_map() {
    cout << "Testing MAP... ";
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    
    auto squared = map<int, int>(numbers, [](int x) { return x * x; });
    
    assert(squared.size() == 3);
    assert(squared.at(0) == 1);
    assert(squared.at(1) == 4);
    assert(squared.at(2) == 9);
    
    cout << "✓ PASSED\n";
}

void test_filter() {
    cout << "Testing FILTER... ";
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    numbers.push(4);
    numbers.push(5);
    
    auto evens = filter<int>(numbers, [](int x) { return x % 2 == 0; });
    
    assert(evens.size() == 2);
    assert(evens.at(0) == 2);
    assert(evens.at(1) == 4);
    
    cout << "✓ PASSED\n";
}

void test_reduce() {
    cout << "Testing REDUCE... ";
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    numbers.push(4);
    numbers.push(5);
    
    int sum = reduce<int>(numbers, [](int a, int b) { return a + b; }, 0);
    assert(sum == 15);
    
    int product = reduce<int>(numbers, [](int a, int b) { return a * b; }, 1);
    assert(product == 120);
    
    cout << "✓ PASSED\n";
}

void test_forEach() {
    cout << "Testing FOREACH... ";
    
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    
    int sum = 0;
    forEach<int>(numbers, [&sum](int x) { sum += x; });
    
    assert(sum == 6);
    
    cout << "✓ PASSED\n";
}

void test_aggregators() {
    cout << "Testing AGGREGATORS... ";
    
    VectorList<int> numbers;
    numbers.push(5);
    numbers.push(2);
    numbers.push(8);
    numbers.push(1);
    numbers.push(9);
    
    assert(sum(numbers) == 25);
    assert(average(numbers) == 5.0);
    assert(minimum(numbers) == 1);
    assert(maximum(numbers) == 9);
    assert(product(numbers) == 720);
    
    cout << "✓ PASSED\n";
}

void test_chained_operations() {
    cout << "Testing CHAINED OPERATIONS... ";
    
    VectorList<int> numbers;
    for (int i = 1; i <= 10; i++) {
        numbers.push(i);
    }
    
    // Get even numbers, square them, then sum
    auto evens = filter<int>(numbers, [](int x) { return x % 2 == 0; });
    auto squared = map<int, int>(evens, [](int x) { return x * x; });
    int result = reduce<int>(squared, [](int a, int b) { return a + b; }, 0);
    
    // Evens: 2, 4, 6, 8, 10
    // Squared: 4, 16, 36, 64, 100
    // Sum: 220
    assert(result == 220);
    
    cout << "✓ PASSED\n";
}

int main() {
    cout << "\n========================================\n";
    cout << "  Functional Operations Test Suite\n";
    cout << "========================================\n\n";
    
    test_map();
    test_filter();
    test_reduce();
    test_forEach();
    test_aggregators();
    test_chained_operations();
    
    cout << "\n✓ All functional tests passed!\n\n";
    
    return 0;
}

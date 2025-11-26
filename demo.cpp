#include <iostream>
#include <string>
#include <iomanip>
#include "containers.h"
#include "functional/FunctionalOps.h"
#include "functional/Aggregators.h"
#include "algorithms/Search.h"
#include "algorithms/Sort.h"
#include "io/FileReader.h"
#include "io/TextTokenizer.h"
#include "analysis/KeywordCounter.h"

using namespace std;
using namespace functional;
using namespace algorithms;

// Forward declarations
void displayMainMenu();
void handleContainerDemo();
void handleFunctionalOps();
void handleFileIO();
void handleKeywordAnalysis();
void handleSearchSort();
void handleAggregation();
void displayHeader(const string& title);
void pause();
void clearScreen();

int main() {
    int choice = -1;
    
    while (choice != 0) {
        displayMainMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline
        
        clearScreen();
        
        switch (choice) {
            case 1:
                handleContainerDemo();
                break;
            case 2:
                handleFunctionalOps();
                break;
            case 3:
                handleFileIO();
                break;
            case 4:
                handleKeywordAnalysis();
                break;
            case 5:
                handleSearchSort();
                break;
            case 6:
                handleAggregation();
                break;
            case 0:
                cout << "\nThank you for using the List Container System!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                pause();
        }
    }
    
    return 0;
}

void displayMainMenu() {
    clearScreen();
    displayHeader("FUNCTIONAL-OO LIST CONTAINER SYSTEM");
    
    cout << "\nMain Menu:\n";
    cout << "----------\n";
    cout << "1. Container Demonstrations\n";
    cout << "2. Functional Operations (Map, Filter, Reduce)\n";
    cout << "3. File I/O & Text Analysis\n";
    cout << "4. ⭐ Keyword Frequency Analysis (Assignment Demo)\n";
    cout << "5. Search & Sort Demonstrations\n";
    cout << "6. Aggregation Operations\n";
    cout << "0. Exit\n";
}

void handleContainerDemo() {
    displayHeader("Container Demonstrations");
    
    cout << "\nDemonstrating VectorList with integers:\n";
    cout << "----------------------------------------\n";
    VectorList<int> vec;
    vec.push(10);
    vec.push(20);
    vec.push(30);
    cout << "Pushed: 10, 20, 30\n";
    cout << "Size: " << vec.size() << "\n";
    cout << "Popped: " << vec.pop() << "\n";
    cout << "Size after pop: " << vec.size() << "\n\n";
    
    cout << "Demonstrating Stack (LIFO):\n";
    cout << "---------------------------\n";
    Stack<string> stack;
    stack.push("First");
    stack.push("Second");
    stack.push("Third");
    cout << "Pushed: First, Second, Third\n";
    cout << "Popped (LIFO): " << stack.pop() << "\n";
    cout << "Popped (LIFO): " << stack.pop() << "\n\n";
    
    cout << "Demonstrating Queue (FIFO):\n";
    cout << "---------------------------\n";
    Queue<string> queue;
    queue.push("First");
    queue.push("Second");
    queue.push("Third");
    cout << "Pushed: First, Second, Third\n";
    cout << "Popped (FIFO): " << queue.pop() << "\n";
    cout << "Popped (FIFO): " << queue.pop() << "\n\n";
    
    pause();
}

void handleFunctionalOps() {
    displayHeader("Functional Operations");
    
    // Setup demo data
    VectorList<int> numbers;
    numbers.push(1);
    numbers.push(2);
    numbers.push(3);
    numbers.push(4);
    numbers.push(5);
    
    cout << "\nOriginal list: [1, 2, 3, 4, 5]\n\n";
    
    // MAP demonstration
    cout << "MAP: Square all numbers\n";
    cout << "-----------------------\n";
    auto squared = map<int, int>(numbers, [](int x) { return x * x; });
    cout << "Result: [";
    for (int i = 0; i < squared.size(); i++) {
        cout << squared.at(i);
        if (i < squared.size() - 1) cout << ", ";
    }
    cout << "]\n\n";
    
    // FILTER demonstration
    cout << "FILTER: Get even numbers only\n";
    cout << "------------------------------\n";
    auto evens = filter<int>(numbers, [](int x) { return x % 2 == 0; });
    cout << "Result: [";
    for (int i = 0; i < evens.size(); i++) {
        cout << evens.at(i);
        if (i < evens.size() - 1) cout << ", ";
    }
    cout << "]\n\n";
    
    // REDUCE demonstration
    cout << "REDUCE: Sum all numbers\n";
    cout << "-----------------------\n";
    int sum = reduce<int>(numbers, [](int a, int b) { return a + b; }, 0);
    cout << "Result: " << sum << "\n\n";
    
    // FOREACH demonstration
    cout << "FOREACH: Print with formatting\n";
    cout << "-------------------------------\n";
    cout << "Output: ";
    forEach<int>(numbers, [](int x) { cout << "[" << x << "] "; });
    cout << "\n\n";
    
    // CHAINED operations
    cout << "CHAINED: filter(even) -> map(square) -> reduce(sum)\n";
    cout << "---------------------------------------------------\n";
    auto evenSquared = map<int, int>(evens, [](int x) { return x * x; });
    int evenSquaredSum = reduce<int>(evenSquared, [](int a, int b) { return a + b; }, 0);
    cout << "Result: " << evenSquaredSum << "\n";
    cout << "(Evens [2,4] -> Squared [4,16] -> Sum = 20)\n\n";
    
    pause();
}

void handleFileIO() {
    displayHeader("File I/O & Text Processing");
    
    FileReader reader;
    TextTokenizer tokenizer;
    
    cout << "\nReading sample file: test_data/sample_texts/doc1.txt\n";
    cout << "----------------------------------------------------\n";
    
    string content = reader.readFileContent("test_data/sample_texts/doc1.txt");
    
    if (content.empty()) {
        cout << "Error: " << reader.getLastError() << "\n";
    } else {
        cout << "✓ File read successfully\n";
        cout << "File size: " << content.length() << " characters\n\n";
        
        cout << "Tokenizing text...\n";
        VectorList<string> words = tokenizer.tokenizeToLower(content);
        cout << "Total words: " << words.size() << "\n\n";
        
        cout << "First 10 words:\n";
        for (int i = 0; i < 10 && i < words.size(); i++) {
            cout << "  " << (i+1) << ". " << words.at(i) << "\n";
        }
        cout << "\n";
    }
    
    cout << "Reading directory: test_data/sample_texts/\n";
    cout << "-------------------------------------------\n";
    VectorList<string> files = reader.listFiles("test_data/sample_texts");
    cout << "Files found: " << files.size() << "\n";
    for (int i = 0; i < files.size(); i++) {
        cout << "  " << (i+1) << ". " << files.at(i) << "\n";
    }
    cout << "\n";
    
    pause();
}

void handleKeywordAnalysis() {
    displayHeader("⭐ KEYWORD FREQUENCY ANALYSIS ⭐");
    cout << "\nThis demonstrates the primary assignment requirement:\n";
    cout << "Analyze text files for keyword frequencies and display results\n";
    cout << "in descending order.\n\n";
    
    KeywordCounter counter;
    counter.setCaseSensitive(false);
    
    cout << "Step 1: Loading keywords from file...\n";
    cout << "--------------------------------------\n";
    VectorList<string> keywords = counter.loadKeywords("test_data/keywords.txt");
    cout << "✓ Loaded " << keywords.size() << " keywords:\n  ";
    for (int i = 0; i < min(10, keywords.size()); i++) {
        cout << keywords.at(i);
        if (i < min(10, keywords.size()) - 1) cout << ", ";
    }
    if (keywords.size() > 10) cout << "...";
    cout << "\n\n";
    
    cout << "Step 2: Analyzing directory of text files...\n";
    cout << "--------------------------------------------\n";
    VectorList<KeywordFrequency> results = counter.analyzeDirectory(
        keywords,
        "test_data/sample_texts"
    );
    
    cout << "✓ Analysis complete!\n";
    cout << "  Files processed: " << counter.getFilesProcessed() << "\n";
    cout << "  Total words: " << counter.getTotalWordsProcessed() << "\n";
    cout << "  Keywords found: " << counter.getKeywordsFound() << " of " << keywords.size() << "\n\n";
    
    cout << "Step 3: Results (Descending by frequency)\n";
    cout << "=========================================\n";
    cout << left << setw(20) << "Keyword" << setw(10) << "Count" << "\n";
    cout << string(30, '-') << "\n";
    
    for (int i = 0; i < results.size(); i++) {
        if (results.at(i).count > 0) {
            cout << left << setw(20) << results.at(i).keyword 
                 << setw(10) << results.at(i).count << "\n";
        }
    }
    
    cout << "\n✓ Assignment demonstration complete!\n\n";
    pause();
}

void handleSearchSort() {
    displayHeader("Search & Sort Demonstrations");
    
    // Create and populate a list
    VectorList<int> numbers;
    int values[] = {42, 17, 93, 8, 56, 23, 71, 35};
    cout << "\nOriginal list: [";
    for (int i = 0; i < 8; i++) {
        numbers.push(values[i]);
        cout << values[i];
        if (i < 7) cout << ", ";
    }
    cout << "]\n\n";
    
    // Linear search
    cout << "LINEAR SEARCH: Finding value 56\n";
    cout << "--------------------------------\n";
    int index = linearSearch(numbers, 56);
    cout << "Found at index: " << index << "\n\n";
    
    // Sort the list
    cout << "SORTING: Using sort algorithm\n";
    cout << "-----------------------------\n";
    sort(numbers);
    cout << "Sorted list: [";
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers.at(i);
        if (i < numbers.size() - 1) cout << ", ";
    }
    cout << "]\n\n";
    
    // Binary search on sorted list
    cout << "BINARY SEARCH: Finding value 56 in sorted list\n";
    cout << "----------------------------------------------\n";
    index = binarySearch(numbers, 56);
    cout << "Found at index: " << index << "\n\n";
    
    // Custom comparator sort (descending)
    VectorList<int> desc;
    for (int i = 0; i < 8; i++) {
        desc.push(values[i]);
    }
    std::function<bool(int,int)> descCompare = [](int a, int b) { return a > b; };
    sort(desc, descCompare); // Descending
    cout << "CUSTOM SORT: Descending order\n";
    cout << "-----------------------------\n";
    cout << "Result: [";
    for (int i = 0; i < desc.size(); i++) {
        cout << desc.at(i);
        if (i < desc.size() - 1) cout << ", ";
    }
    cout << "]\n\n";
    
    pause();
}

void handleAggregation() {
    displayHeader("Aggregation Operations");
    
    VectorList<int> numbers;
    numbers.push(5);
    numbers.push(12);
    numbers.push(8);
    numbers.push(20);
    numbers.push(3);
    
    cout << "\nSample list: [5, 12, 8, 20, 3]\n\n";
    
    cout << "SUM: " << sum(numbers) << "\n";
    cout << "AVERAGE: " << average(numbers) << "\n";
    cout << "MINIMUM: " << minimum(numbers) << "\n";
    cout << "MAXIMUM: " << maximum(numbers) << "\n";
    cout << "PRODUCT: " << product(numbers) << "\n\n";
    
    std::function<bool(int)> greaterThan10 = [](int x) { return x > 10; };
    std::function<bool(int)> greaterThan15 = [](int x) { return x > 15; };
    std::function<bool(int)> greaterThan0 = [](int x) { return x > 0; };
    
    cout << "COUNT IF (> 10): " << countIf(numbers, greaterThan10) << "\n";
    cout << "ANY (> 15): " << (any(numbers, greaterThan15) ? "true" : "false") << "\n";
    cout << "ALL (> 0): " << (all(numbers, greaterThan0) ? "true" : "false") << "\n\n";
    
    pause();
}

void displayHeader(const string& title) {
    cout << "\n";
    cout << string(60, '=') << "\n";
    cout << "  " << title << "\n";
    cout << string(60, '=') << "\n";
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void clearScreen() {
    // Platform-independent screen clear
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

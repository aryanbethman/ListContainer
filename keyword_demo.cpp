/*
 * Keyword Frequency Counter Demo
 * 
 * This program demonstrates the complete functional-OO solution to the
 * assignment's example use case: counting keyword frequencies across
 * multiple text files.
 * 
 * Run: ./keyword_demo
 */

#include <iostream>
#include <iomanip>
#include "analysis/KeywordCounter.h"

int main() {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║      Keyword Frequency Counter - Functional-OO Demo     ║\n";
    std::cout << "╠══════════════════════════════════════════════════════════╣\n";
    std::cout << "║  Assignment Example: Count keywords across text files   ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
    
    // ========================================================================
    // The complete functional-OO pipeline in one function call
    // ========================================================================
    
    std::cout << "Running analysis...\n" << std::endl;
    
    auto results = KeywordCounter::analyzeDirectory(
        "test_data/keywords.txt",   // Keywords to search for
        "test_data",                 // Directory to search in
        ".txt",                      // File extension filter
        false                        // Case-insensitive
    );
    
    // ========================================================================
    // Display results
    // ========================================================================
    
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Results: Keywords by Frequency (Descending)            ║\n";
    std::cout << "╠══════════════════════════════════════════════════════════╣\n";
    
    int rank = 1;
    for (const auto& kc : results) {
        std::cout << "║  " << std::setw(2) << rank++ << ". "
                  << std::left << std::setw(25) << kc.keyword
                  << std::right << std::setw(5) << kc.count 
                  << " occurrences      ║\n";
    }
    
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    
    // ========================================================================
    // Demonstrate functional operations on results
    // ========================================================================
    
    std::cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Functional Operations on Results                       ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
    
    // Filter: Keywords with >2 occurrences
    std::cout << "Keywords with more than 2 occurrences:" << std::endl;
    for (const auto& kc : results) {
        if (kc.count > 2) {
            std::cout << "  - " << kc.keyword << " (" << kc.count << ")" << std::endl;
        }
    }
    
    // Count total keyword occurrences
    int total = 0;
    for (const auto& kc : results) {
        total += kc.count;
    }
    std::cout << "\nTotal keyword occurrences across all files: " << total << std::endl;
    
    // Find top 3
    std::cout << "\nTop 3 most frequent keywords:" << std::endl;
    for (int i = 0; i < 3 && i < results.size(); i++) {
        std::cout << "  " << (i+1) << ". " << results[i].keyword 
                  << " - " << results[i].count << " times" << std::endl;
    }
    
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║  This demonstrates Functional-OO principles:            ║\n";
    std::cout << "║  • Declarative WHAT (not imperative HOW)               ║\n";
    std::cout << "║  • Composition of simple operations                     ║\n";
    std::cout << "║  • FileReader + map/filter/reduce integration          ║\n";
    std::cout << "║  • Clean, readable, maintainable code                   ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n\n";
    
    return 0;
}

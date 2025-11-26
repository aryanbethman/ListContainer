#include <iostream>
#include <cassert>
#include "../analysis/KeywordCounter.h"

using namespace std;

void test_keyword_loading() {
    cout << "Testing KEYWORD LOADING... ";
    
    KeywordCounter counter;
    VectorList<string> keywords = counter.loadKeywords("test_data/keywords.txt");
    
    assert(keywords.size() > 0);
    
    cout << "✓ PASSED\n";
}

void test_keyword_analysis() {
    cout << "Testing KEYWORD ANALYSIS... ";
    
    KeywordCounter counter;
    counter.setCaseSensitive(false);
    
    VectorList<string> keywords = counter.loadKeywords("test_data/keywords.txt");
    VectorList<KeywordFrequency> results = counter.analyzeDirectory(
        keywords,
        "test_data/sample_texts"
    );
    
    assert(results.size() > 0);
    assert(counter.getTotalWordsProcessed() > 0);
    assert(counter.getFilesProcessed() > 0);
    
    // Check that results are sorted (descending)
    for (int i = 0; i < results.size() - 1; i++) {
        assert(results.at(i).count >= results.at(i + 1).count);
    }
    
    cout << "✓ PASSED\n";
}

void test_case_sensitivity() {
    cout << "Testing CASE SENSITIVITY... ";
    
    // Test with case-insensitive (default)
    KeywordCounter counter1;
    counter1.setCaseSensitive(false);
    
    VectorList<string> keywords;
    keywords.push("data");
    keywords.push("algorithm");
    
    VectorList<KeywordFrequency> results = counter1.analyzeDirectory(
        keywords,
        "test_data/sample_texts"
    );
    
    // Should find occurrences regardless of case
    assert(results.at(0).count > 0 || results.at(1).count > 0);
    
    cout << "✓ PASSED\n";
}

int main() {
    cout << "\n========================================\n";
    cout << "  Text Analysis Test Suite\n";
    cout << "========================================\n\n";
    
    test_keyword_loading();
    test_keyword_analysis();
    test_case_sensitivity();
    
    cout << "\n✓ All text analysis tests passed!\n\n";
    
    return 0;
}

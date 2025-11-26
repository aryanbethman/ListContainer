#include <iostream>
#include "analysis/KeywordCounter.h"

using namespace std;

int main() {
    cout << "Testing Keyword Frequency Analysis...\n";
    cout << "======================================\n\n";
    
    KeywordCounter counter;
    counter.setCaseSensitive(false);
    
    cout << "Step 1: Loading keywords...\n";
    VectorList<string> keywords = counter.loadKeywords("test_data/keywords.txt");
    cout << "✓ Loaded " << keywords.size() << " keywords\n\n";
    
    cout << "Step 2: Analyzing directory...\n";
    VectorList<KeywordFrequency> results = counter.analyzeDirectory(
        keywords,
        "test_data/sample_texts"
    );
    
    cout << "✓ Analysis complete!\n";
    cout << "  Files processed: " << counter.getFilesProcessed() << "\n";
    cout << "  Total words: " << counter.getTotalWordsProcessed() << "\n";
    cout << "  Keywords found: " << counter.getKeywordsFound() << "\n\n";
    
    cout << "Step 3: Results (Top 10)\n";
    cout << "========================\n";
    for (int i = 0; i < 10 && i < results.size(); i++) {
        if (results.at(i).count > 0) {
            cout << results.at(i).keyword << "\t: " << results.at(i).count << "\n";
        }
    }
    
    cout << "\n✓ Test completed successfully!\n";
    
    return 0;
}

#include <iostream>
#include <cassert>
#include "../io/FileReader.h"
#include "../io/TextTokenizer.h"

using namespace std;

void test_file_reading() {
    cout << "Testing FILE READING... ";
    
    FileReader reader;
    string content = reader.readFileContent("test_data/keywords.txt");
    
    assert(!content.empty());
    assert(reader.fileExists("test_data/keywords.txt"));
    
    cout << "✓ PASSED\n";
}

void test_tokenization() {
    cout << "Testing TOKENIZATION... ";
    
    TextTokenizer tokenizer;
    VectorList<string> tokens = tokenizer.tokenize("Hello world, this is a test!");
    
    assert(tokens.size() > 0);
    
    cout << "✓ PASSED\n";
}

void test_directory_listing() {
    cout << "Testing DIRECTORY LISTING... ";
    
    FileReader reader;
    VectorList<string> files = reader.listFiles("test_data/sample_texts");
    
    assert(files.size() > 0);
    
    cout << "✓ PASSED\n";
}

int main() {
    cout << "\n========================================\n";
    cout << "  File I/O Test Suite\n";
    cout << "========================================\n\n";
    
    test_file_reading();
    test_tokenization();
    test_directory_listing();
    
    cout << "\n✓ All file I/O tests passed!\n\n";
    
    return 0;
}

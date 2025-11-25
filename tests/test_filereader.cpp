/*
 * Test Suite for FileReader
 * 
 * Tests file I/O functionality and integration with functional operations
 */

#include <iostream>
#include <string>
#include <cassert>
#include "../io/FileReader.h"

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
// TEST 1: Read Lines
// ============================================================================
void test_readLines() {
    std::cout << "\n" << YELLOW << "=== Testing readLines ===" << RESET << std::endl;
    
    auto lines = FileReader::readLines("test_data/sample.txt");
    
    assert_test(lines.size() == 4, "readLines: correct number of lines");
    assert_test(lines.at(0) == "Hello World", "readLines: first line correct");
    assert_test(lines.at(3) == "For testing FileReader", "readLines: last line correct");
}

// ============================================================================
// TEST 2: Read Words
// ============================================================================
void test_readWords() {
    std::cout << "\n" << YELLOW << "=== Testing readWords ===" << RESET << std::endl;
    
    auto words = FileReader::readWords("test_data/words.txt");
    
    assert_test(words.size() == 8, "readWords: correct word count");
    assert_test(words.at(0) == "apple", "readWords: first word correct");
    assert_test(words.at(7) == "honeydew", "readWords: last word correct");
}

// ============================================================================
// TEST 3: Read File
// ============================================================================
void test_readFile() {
    std::cout << "\n" << YELLOW << "=== Testing readFile ===" << RESET << std::endl;
    
    std::string content = FileReader::readFile("test_data/sample.txt");
    
    assert_test(!content.empty(), "readFile: returns non-empty content");
    assert_test(content.find("Hello World") != std::string::npos, 
                "readFile: contains expected text");
}

// ============================================================================
// TEST 4: Tokenize
// ============================================================================
void test_tokenize() {
    std::cout << "\n" << YELLOW << "=== Testing tokenize ===" << RESET << std::endl;
    
    auto tokens1 = FileReader::tokenize("hello,world,test", ",");
    assert_test(tokens1.size() == 3, "tokenize: comma-separated");
    assert_test(tokens1.at(1) == "world", "tokenize: middle token correct");
    
    auto tokens2 = FileReader::tokenize("one two  three", " ");
    assert_test(tokens2.size() == 3, "tokenize: handles multiple spaces");
    
    auto tokens3 = FileReader::tokenize("a|b|c|d", "|");
    assert_test(tokens3.size() == 4, "tokenize: pipe delimiter");
}

// ============================================================================
// TEST 5: To Lower
// ============================================================================
void test_toLower() {
    std::cout << "\n" << YELLOW << "=== Testing toLower ===" << RESET << std::endl;
    
    assert_test(FileReader::toLower("HELLO") == "hello", "toLower: all caps");
    assert_test(FileReader::toLower("HeLLo WoRLd") == "hello world", "toLower: mixed case");
    assert_test(FileReader::toLower("already lowercase") == "already lowercase", 
                "toLower: already lowercase");
}

// ============================================================================
// TEST 6: File Exists
// ============================================================================
void test_fileExists() {
    std::cout << "\n" << YELLOW << "=== Testing fileExists ===" << RESET << std::endl;
    
    assert_test(FileReader::fileExists("test_data/sample.txt"), 
                "fileExists: existing file returns true");
    assert_test(!FileReader::fileExists("test_data/nonexistent.txt"), 
                "fileExists: non-existing file returns false");
}

// ============================================================================
// TEST 7: Read Files In Directory
// ============================================================================
void test_readFilesInDirectory() {
    std::cout << "\n" << YELLOW << "=== Testing readFilesInDirectory ===" << RESET << std::endl;
    
    auto files = FileReader::readFilesInDirectory("test_data", ".txt");
    
    assert_test(files.size() >= 5, "readFilesInDirectory: finds multiple files");
    
    // Check that at least one expected file is found
    bool foundSample = false;
    for (int i = 0; i < files.size(); i++) {
        if (files.at(i).find("sample.txt") != std::string::npos) {
            foundSample = true;
            break;
        }
    }
    assert_test(foundSample, "readFilesInDirectory: finds sample.txt");
}

// ============================================================================
// TEST 8: Integration with Functional Operations
// ============================================================================
void test_functional_integration() {
    std::cout << "\n" << YELLOW << "=== Testing Functional Integration ===" << RESET << std::endl;
    
    // Read lines and use functional operations
    auto lines = FileReader::readLines("test_data/sample.txt");
    
    // Map: convert to uppercase (simplified)
    auto upperLines = lines.map<std::string>([](std::string line) {
        std::string result = line;
        for (char& c : result) c = toupper(c);
        return result;
    });
    assert_test(upperLines.at(0) == "HELLO WORLD", "Integration: map works with readLines");
    
    // Filter: lines containing "test"
    auto testLines = lines.filter([](std::string line) {
        return FileReader::toLower(line).find("test") != std::string::npos;
    });
    assert_test(testLines.size() == 2, "Integration: filter works with readLines");
    
    // Reduce: count total characters
    int totalChars = lines.reduce<int>(0, [](int acc, std::string line) {
        return acc + line.length();
    });
    assert_test(totalChars > 0, "Integration: reduce works with readLines");
}

// ============================================================================
// TEST 9: Read Words and Process
// ============================================================================
void test_word_processing() {
    std::cout << "\n" << YELLOW << "=== Testing Word Processing ===" << RESET << std::endl;
    
    auto words = FileReader::readWords("test_data/keywords.txt");
    
    // Convert all to lowercase
    auto lowerWords = words.map<std::string>([](std::string word) {
        return FileReader::toLower(word);
    });
    
    // Filter words with more than 5 characters
    auto longWords = lowerWords.filter([](std::string word) {
        return word.length() > 5;
    });
    
    assert_test(longWords.size() >= 3, "Word processing: filters long words");
    
    // Count total length of all words
    int totalLength = words.reduce<int>(0, [](int acc, std::string word) {
        return acc + word.length();
    });
    
    assert_test(totalLength > 0, "Word processing: reduces to total length");
}

// ============================================================================
// TEST 10: Multi-file Processing
// ============================================================================
void test_multifile_processing() {
    std::cout << "\n" << YELLOW << "=== Testing Multi-File Processing ===" << RESET << std::endl;
    
    // Get all document files
    auto files = FileReader::readFilesInDirectory("test_data", ".txt")
        .filter([](std::string path) {
            return path.find("document") != std::string::npos;
        });
    
    assert_test(files.size() >= 2, "Multi-file: finds document files");
    
    // Read content of all files
    auto allContent = files.map<std::string>([](std::string path) {
        return FileReader::readFile(path);
    });
    
    assert_test(allContent.size() == files.size(), 
                "Multi-file: reads all files");
    
    // Count total lines across all files
    int totalLines = files.reduce<int>(0, [](int acc, std::string path) {
        return acc + FileReader::readLines(path).size();
    });
    
    assert_test(totalLines >= 8, "Multi-file: counts total lines");
}

// ============================================================================
// MAIN
// ============================================================================
int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════╗\n";
    std::cout << "║  FileReader Test Suite                                ║\n";
    std::cout << "║  Testing: I/O operations and functional integration   ║\n";
    std::cout << "╚════════════════════════════════════════════════════════╝\n";
    
    test_readLines();
    test_readWords();
    test_readFile();
    test_tokenize();
    test_toLower();
    test_fileExists();
    test_readFilesInDirectory();
    test_functional_integration();
    test_word_processing();
    test_multifile_processing();
    
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

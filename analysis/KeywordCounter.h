/*
 * Keyword Frequency Counter
 * 
 * WHAT: Count occurrences of keywords across multiple text files
 * 
 * This is the primary example use case from the assignment specification:
 * "Given a directory full of text files, scrape all keywords (from a keyword 
 * file) and list them in decreasing order of occurrence frequency."
 * 
 * Demonstrates:
 * - Functional-OO composition
 * - Method chaining
 * - Data transformation pipelines
 * - Integration of FileReader + functional operations
 */

#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "../containers/VectorList.h"
#include "../io/FileReader.h"

struct KeywordCount {
    std::string keyword;
    int count;
    
    // For sorting
    bool operator<(const KeywordCount& other) const {
        return count > other.count;  // Descending order
    }
};

class KeywordCounter {
public:
    /**
     * Count keyword occurrences in a single file.
     * 
     * WHAT: For each keyword, count how many times it appears in the file
     * 
     * @param filepath Path to the text file
     * @param keywords List of keywords to search for
     * @param caseSensitive Whether matching should be case-sensitive
     * @return Map of keyword -> count
     */
    static std::map<std::string, int> countInFile(
        const std::string& filepath,
        VectorList<std::string>& keywords,
        bool caseSensitive = false
    );

    /**
     * Count keyword occurrences across multiple files.
     * 
     * WHAT: Aggregate keyword counts from all files in a directory
     * 
     * @param dirpath Directory containing text files
     * @param keywords List of keywords to search for
     * @param extension File extension filter (default: ".txt")
     * @param caseSensitive Whether matching should be case-sensitive
     * @return Map of keyword -> total count
     */
    static std::map<std::string, int> countInDirectory(
        const std::string& dirpath,
        VectorList<std::string>& keywords,
        const std::string& extension = ".txt",
        bool caseSensitive = false
    );

    /**
     * Sort keyword counts by frequency (descending).
     * 
     * WHAT: Convert map to sorted vector of KeywordCount structs
     * 
     * @param counts Map of keyword -> count
     * @return Sorted vector (highest count first)
     */
    static std::vector<KeywordCount> sortByFrequency(
        const std::map<std::string, int>& counts
    );

    /**
     * Full pipeline: read keywords, count in directory, return sorted results.
     * 
     * WHAT: Complete solution to the assignment example use case
     * 
     * @param keywordFile Path to file containing keywords (one per line or whitespace-separated)
     * @param dataDir Directory containing data files
     * @param extension File extension to process (default: ".txt")
     * @param caseSensitive Whether matching should be case-sensitive
     * @return Sorted vector of keyword counts (descending by frequency)
     * 
     * Example:
     *   auto results = KeywordCounter::analyzeDirectory(
     *       "keywords.txt", 
     *       "data/"
     *   );
     *   for (const auto& kc : results) {
     *       std::cout << kc.keyword << ": " << kc.count << std::endl;
     *   }
     */
    static std::vector<KeywordCount> analyzeDirectory(
        const std::string& keywordFile,
        const std::string& dataDir,
        const std::string& extension = ".txt",
        bool caseSensitive = false
    );

private:
    /**
     * Count occurrences of a keyword in text.
     * 
     * @param text The text to search in
     * @param keyword The keyword to search for
     * @param caseSensitive Whether matching should be case-sensitive
     * @return Number of occurrences
     */
    static int countOccurrences(
        const std::string& text,
        const std::string& keyword,
        bool caseSensitive
    );
};

#include "KeywordCounter.cpp"

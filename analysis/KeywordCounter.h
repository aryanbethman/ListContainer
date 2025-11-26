#pragma once

#include <string>
#include <iostream>
#include "../containers/VectorList.h"
#include "../io/FileReader.h"
#include "../io/TextTokenizer.h"

/**
 * KeywordFrequency Structure
 * 
 * Stores a keyword and its occurrence count.
 * Supports comparison for sorting by frequency.
 */
struct KeywordFrequency {
    std::string keyword;
    int count;
    
    KeywordFrequency(const std::string& kw = "", int c = 0) 
        : keyword(kw), count(c) {}
    
    // Comparison operators for sorting
    bool operator>(const KeywordFrequency& other) const {
        return count > other.count;
    }
    
    bool operator<(const KeywordFrequency& other) const {
        return count < other.count;
    }
    
    bool operator==(const KeywordFrequency& other) const {
        return keyword == other.keyword && count == other.count;
    }
    
    // For printing
    friend std::ostream& operator<<(std::ostream& os, const KeywordFrequency& kf) {
        os << kf.keyword << ": " << kf.count;
        return os;
    }
};

/**
 * KeywordCounter Class
 * 
 * Analyzes text files for keyword frequencies.
 * Main class for the assignment's primary use case.
 */
class KeywordCounter {
public:
    KeywordCounter();
    
    /**
     * Analyze files for keyword frequencies
     * 
     * @param keywords List of keywords to search for
     * @param filepaths List of file paths to analyze
     * @return VectorList of KeywordFrequency sorted by count (descending)
     */
    VectorList<KeywordFrequency> analyzeFiles(
        VectorList<std::string>& keywords,
        VectorList<std::string>& filepaths
    );
    
    /**
     * Analyze directory for keyword frequencies
     * 
     * @param keywords List of keywords to search for
     * @param dirpath Directory containing text files
     * @return VectorList of KeywordFrequency sorted by count (descending)
     */
    VectorList<KeywordFrequency> analyzeDirectory(
        VectorList<std::string>& keywords,
        const std::string& dirpath
    );
    
    /**
     * Load keywords from a file (whitespace-separated)
     * 
     * @param filepath Path to keyword file
     * @return VectorList of keywords
     */
    VectorList<std::string> loadKeywords(const std::string& filepath);
    
    /**
     * Set case sensitivity for matching
     * @param sensitive true for case-sensitive matching
     */
    void setCaseSensitive(bool sensitive);
    
    /**
     * Set minimum count threshold (keywords below this won't be included)
     * @param minCount Minimum count threshold
     */
    void setMinimumCount(int minCount);
    
    /**
     * Get total number of words processed
     */
    int getTotalWordsProcessed() const;
    
    /**
     * Get number of keywords that were found at least once
     */
    int getKeywordsFound() const;
    
    /**
     * Get total number of files processed
     */
    int getFilesProcessed() const;
    
private:
    bool caseSensitive_;
    int minimumCount_;
    int totalWordsProcessed_;
    int keywordsFound_;
    int filesProcessed_;
    
    FileReader fileReader_;
    TextTokenizer tokenizer_;
    
    /**
     * Find index of keyword in results list
     * @return index if found, -1 otherwise
     */
    int findKeywordIndex(VectorList<KeywordFrequency>& list, const std::string& keyword);
    
    /**
     * Sort results by count (descending)
     */
    void sortResults(VectorList<KeywordFrequency>& results);
    
    /**
     * Compare two strings based on case sensitivity setting
     */
    bool matchStrings(const std::string& a, const std::string& b);
    
    /**
     * Convert string to lowercase if case-insensitive
     */
    std::string normalizeString(const std::string& str);
};

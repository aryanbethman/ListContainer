#include "KeywordCounter.h"
#include "../algorithms/Sort.h"
#include <algorithm>
#include <cctype>

KeywordCounter::KeywordCounter() 
    : caseSensitive_(false),
      minimumCount_(0),
      totalWordsProcessed_(0),
      keywordsFound_(0),
      filesProcessed_(0) {
    // Configure tokenizer for word extraction
    tokenizer_.setRemovePunctuation(true);
    tokenizer_.setFilterEmpty(true);
}

VectorList<KeywordFrequency> KeywordCounter::analyzeFiles(
    VectorList<std::string>& keywords,
    VectorList<std::string>& filepaths) {
    
    // Initialize results with all keywords at count 0
    VectorList<KeywordFrequency> results;
    for (int i = 0; i < keywords.size(); i++) {
        std::string keyword = normalizeString(keywords.at(i));
        results.push(KeywordFrequency(keyword, 0));
    }
    
    // Reset statistics
    totalWordsProcessed_ = 0;
    filesProcessed_ = 0;
    
    // Process each file
    for (int fileIdx = 0; fileIdx < filepaths.size(); fileIdx++) {
        std::string content = fileReader_.readFileContent(filepaths.at(fileIdx));
        
        if (content.empty()) {
            continue; // Skip empty or unreadable files
        }
        
        filesProcessed_++;
        
        // Tokenize the content
        VectorList<std::string> words;
        if (caseSensitive_) {
            words = tokenizer_.tokenize(content);
        } else {
            words = tokenizer_.tokenizeToLower(content);
        }
        
        totalWordsProcessed_ += words.size();
        
        // Count occurrences of each keyword
        for (int wordIdx = 0; wordIdx < words.size(); wordIdx++) {
            std::string word = normalizeString(words.at(wordIdx));
            
            // Check if this word matches any keyword
            for (int kwIdx = 0; kwIdx < results.size(); kwIdx++) {
                if (matchStrings(word, results.at(kwIdx).keyword)) {
                    // Increment count - need to modify in place
                    KeywordFrequency kf = results.at(kwIdx);
                    kf.count++;
                    results.erase_at(kwIdx);
                    results.insert_at(kwIdx, kf);
                    break;
                }
            }
        }
    }
    
    // Count how many keywords were found
    keywordsFound_ = 0;
    for (int i = 0; i < results.size(); i++) {
        if (results.at(i).count > 0) {
            keywordsFound_++;
        }
    }
    
    // Filter by minimum count if set
    if (minimumCount_ > 0) {
        VectorList<KeywordFrequency> filtered;
        for (int i = 0; i < results.size(); i++) {
            if (results.at(i).count >= minimumCount_) {
                filtered.push(results.at(i));
            }
        }
        results = filtered;
    }
    
    // Sort by count (descending)
    sortResults(results);
    
    return results;
}

VectorList<KeywordFrequency> KeywordCounter::analyzeDirectory(
    VectorList<std::string>& keywords,
    const std::string& dirpath) {
    
    // Get list of files in directory
    VectorList<std::string> filenames = fileReader_.listFiles(dirpath);
    
    // Build full paths
    VectorList<std::string> filepaths;
    for (int i = 0; i < filenames.size(); i++) {
        std::string fullpath = dirpath;
        if (fullpath.back() != '/') {
            fullpath += "/";
        }
        fullpath += filenames.at(i);
        filepaths.push(fullpath);
    }
    
    return analyzeFiles(keywords, filepaths);
}

VectorList<std::string> KeywordCounter::loadKeywords(const std::string& filepath) {
    std::string content = fileReader_.readFileContent(filepath);
    
    if (content.empty()) {
        return VectorList<std::string>();
    }
    
    // Tokenize the keyword file (whitespace-separated)
    tokenizer_.setRemovePunctuation(false); // Keep keywords as-is
    VectorList<std::string> keywords = tokenizer_.tokenize(content);
    tokenizer_.setRemovePunctuation(true); // Restore default
    
    return keywords;
}

void KeywordCounter::setCaseSensitive(bool sensitive) {
    caseSensitive_ = sensitive;
}

void KeywordCounter::setMinimumCount(int minCount) {
    minimumCount_ = minCount;
}

int KeywordCounter::getTotalWordsProcessed() const {
    return totalWordsProcessed_;
}

int KeywordCounter::getKeywordsFound() const {
    return keywordsFound_;
}

int KeywordCounter::getFilesProcessed() const {
    return filesProcessed_;
}

int KeywordCounter::findKeywordIndex(VectorList<KeywordFrequency>& list, const std::string& keyword) {
    for (int i = 0; i < list.size(); i++) {
        if (matchStrings(list.at(i).keyword, keyword)) {
            return i;
        }
    }
    return -1;
}

void KeywordCounter::sortResults(VectorList<KeywordFrequency>& results) {
    // Use our sorting algorithm with custom comparator (descending by count)
    algorithms::sort<KeywordFrequency>(results, 
        [](KeywordFrequency a, KeywordFrequency b) {
            // Sort by count descending, then alphabetically by keyword
            if (a.count != b.count) {
                return a.count > b.count; // Higher counts first
            }
            return a.keyword < b.keyword; // Alphabetical for ties
        }
    );
}

bool KeywordCounter::matchStrings(const std::string& a, const std::string& b) {
    if (caseSensitive_) {
        return a == b;
    } else {
        return normalizeString(a) == normalizeString(b);
    }
}

std::string KeywordCounter::normalizeString(const std::string& str) {
    if (caseSensitive_) {
        return str;
    }
    
    std::string lower = str;
    for (size_t i = 0; i < lower.length(); i++) {
        lower[i] = std::tolower(lower[i]);
    }
    return lower;
}

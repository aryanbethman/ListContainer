/*
 * KeywordCounter Implementation
 * 
 * Demonstrates functional-OO composition:
 * - FileReader provides WHAT data to process
 * - Functional operations specify WHAT transformations to apply
 * - Implementation handles HOW automatically
 */

#include <iostream>

// ============================================================================
// Count occurrences of a keyword in text
// ============================================================================
int KeywordCounter::countOccurrences(
    const std::string& text,
    const std::string& keyword,
    bool caseSensitive
) {
    if (keyword.empty()) return 0;
    
    std::string searchText = caseSensitive ? text : FileReader::toLower(text);
    std::string searchKeyword = caseSensitive ? keyword : FileReader::toLower(keyword);
    
    int count = 0;
    size_t pos = 0;
    
    while ((pos = searchText.find(searchKeyword, pos)) != std::string::npos) {
        count++;
        pos += searchKeyword.length();
    }
    
    return count;
}

// ============================================================================
// Count keywords in a single file
// ============================================================================
std::map<std::string, int> KeywordCounter::countInFile(
    const std::string& filepath,
    VectorList<std::string>& keywords,
    bool caseSensitive
) {
    std::map<std::string, int> counts;
    
    // Read entire file content
    std::string content = FileReader::readFile(filepath);
    
    if (content.empty()) {
        return counts;
    }
    
    // Count each keyword using functional reduce
    keywords.forEach([&](std::string keyword) {
        int occurrences = countOccurrences(content, keyword, caseSensitive);
        counts[keyword] = occurrences;
    });
    
    return counts;
}

// ============================================================================
// Count keywords across multiple files in a directory
// ============================================================================
std::map<std::string, int> KeywordCounter::countInDirectory(
    const std::string& dirpath,
    VectorList<std::string>& keywords,
    const std::string& extension,
    bool caseSensitive
) {
    std::map<std::string, int> totalCounts;
    
    // Initialize counts for all keywords
    keywords.forEach([&](std::string keyword) {
        totalCounts[keyword] = 0;
    });
    
    // Get all files in directory
    auto files = FileReader::readFilesInDirectory(dirpath, extension);
    
    // For each file, count keywords and aggregate
    files.forEach([&](std::string filepath) {
        auto fileCounts = countInFile(filepath, keywords, caseSensitive);
        
        // Merge counts
        for (const auto& pair : fileCounts) {
            totalCounts[pair.first] += pair.second;
        }
    });
    
    return totalCounts;
}

// ============================================================================
// Sort keyword counts by frequency (descending)
// ============================================================================
std::vector<KeywordCount> KeywordCounter::sortByFrequency(
    const std::map<std::string, int>& counts
) {
    std::vector<KeywordCount> results;
    
    // Convert map to vector
    for (const auto& pair : counts) {
        results.push_back({pair.first, pair.second});
    }
    
    // Sort by count (descending)
    std::sort(results.begin(), results.end());
    
    return results;
}

// ============================================================================
// Full pipeline: analyze directory with keywords from file
// ============================================================================
std::vector<KeywordCount> KeywordCounter::analyzeDirectory(
    const std::string& keywordFile,
    const std::string& dataDir,
    const std::string& extension,
    bool caseSensitive
) {
    // Step 1: Read keywords from file
    // WHAT: Get list of keywords to search for
    auto keywords = FileReader::readWords(keywordFile);
    
    std::cout << "Loaded " << keywords.size() << " keywords from " << keywordFile << std::endl;
    
    // Step 2: Count keywords in all files
    // WHAT: Aggregate keyword occurrences across directory
    auto counts = countInDirectory(dataDir, keywords, extension, caseSensitive);
    
    std::cout << "Analyzed files in " << dataDir << std::endl;
    
    // Step 3: Sort by frequency
    // WHAT: Order results by most frequent first
    auto sorted = sortByFrequency(counts);
    
    return sorted;
}

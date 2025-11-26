#pragma once

#include <string>
#include "../containers/VectorList.h"

/**
 * TextTokenizer Class
 * 
 * Tokenizes text into words based on delimiters.
 * Supports various options for handling punctuation and case.
 */

class TextTokenizer {
public:
    TextTokenizer();
    
    /**
     * Tokenize text using current delimiters
     * @param text Text to tokenize
     * @return VectorList of tokens
     */
    VectorList<std::string> tokenize(const std::string& text);
    
    /**
     * Tokenize and convert all tokens to lowercase
     * @param text Text to tokenize
     * @return VectorList of lowercase tokens
     */
    VectorList<std::string> tokenizeToLower(const std::string& text);
    
    /**
     * Set custom delimiters
     * @param delims String containing delimiter characters
     */
    void setDelimiters(const std::string& delims);
    
    /**
     * Enable/disable punctuation removal
     * @param remove true to remove punctuation from tokens
     */
    void setRemovePunctuation(bool remove);
    
    /**
     * Enable/disable empty token filtering
     * @param filter true to filter out empty tokens
     */
    void setFilterEmpty(bool filter);
    
private:
    std::string delimiters_;
    bool removePunctuation_;
    bool filterEmpty_;
    
    /**
     * Remove punctuation from a token
     */
    std::string cleanToken(const std::string& token);
    
    /**
     * Convert string to lowercase
     */
    std::string toLowerCase(const std::string& str);
    
    /**
     * Check if character is a delimiter
     */
    bool isDelimiter(char c);
    
    /**
     * Check if character is punctuation
     */
    bool isPunctuation(char c);
};

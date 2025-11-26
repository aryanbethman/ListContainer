#include "TextTokenizer.h"
#include <cctype>
#include <algorithm>

TextTokenizer::TextTokenizer() 
    : delimiters_(" \t\n\r"), 
      removePunctuation_(true),
      filterEmpty_(true) {}

VectorList<std::string> TextTokenizer::tokenize(const std::string& text) {
    VectorList<std::string> tokens;
    std::string current = "";
    
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];
        
        if (isDelimiter(c)) {
            // End of token
            if (!current.empty()) {
                if (removePunctuation_) {
                    current = cleanToken(current);
                }
                
                if (!filterEmpty_ || !current.empty()) {
                    tokens.push(current);
                }
                current = "";
            }
        } else {
            current += c;
        }
    }
    
    // Don't forget the last token
    if (!current.empty()) {
        if (removePunctuation_) {
            current = cleanToken(current);
        }
        
        if (!filterEmpty_ || !current.empty()) {
            tokens.push(current);
        }
    }
    
    return tokens;
}

VectorList<std::string> TextTokenizer::tokenizeToLower(const std::string& text) {
    VectorList<std::string> tokens = tokenize(text);
    VectorList<std::string> lowerTokens;
    
    for (int i = 0; i < tokens.size(); i++) {
        lowerTokens.push(toLowerCase(tokens.at(i)));
    }
    
    return lowerTokens;
}

void TextTokenizer::setDelimiters(const std::string& delims) {
    delimiters_ = delims;
}

void TextTokenizer::setRemovePunctuation(bool remove) {
    removePunctuation_ = remove;
}

void TextTokenizer::setFilterEmpty(bool filter) {
    filterEmpty_ = filter;
}

std::string TextTokenizer::cleanToken(const std::string& token) {
    std::string cleaned = "";
    
    for (size_t i = 0; i < token.length(); i++) {
        if (!isPunctuation(token[i])) {
            cleaned += token[i];
        }
    }
    
    return cleaned;
}

std::string TextTokenizer::toLowerCase(const std::string& str) {
    std::string lower = str;
    for (size_t i = 0; i < lower.length(); i++) {
        lower[i] = std::tolower(lower[i]);
    }
    return lower;
}

bool TextTokenizer::isDelimiter(char c) {
    return delimiters_.find(c) != std::string::npos;
}

bool TextTokenizer::isPunctuation(char c) {
    // Common punctuation marks
    const std::string punctuation = ".,;:!?\"'()[]{}@#$%^&*-_=+|\\/<>`~";
    return punctuation.find(c) != std::string::npos;
}

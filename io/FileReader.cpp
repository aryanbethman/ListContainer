/*
 * FileReader Implementation
 */

#include <iostream>

// ============================================================================
// Read all lines from a file
// ============================================================================
VectorList<std::string> FileReader::readLines(const std::string& filepath) {
    VectorList<std::string> lines;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open file: " << filepath << std::endl;
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push(line);
    }
    
    file.close();
    return lines;
}

// ============================================================================
// Read all words from a file
// ============================================================================
VectorList<std::string> FileReader::readWords(const std::string& filepath) {
    VectorList<std::string> words;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open file: " << filepath << std::endl;
        return words;
    }
    
    std::string word;
    while (file >> word) {
        words.push(word);
    }
    
    file.close();
    return words;
}

// ============================================================================
// Read entire file as single string
// ============================================================================
std::string FileReader::readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open file: " << filepath << std::endl;
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

// ============================================================================
// List all files in a directory
// ============================================================================
VectorList<std::string> FileReader::readFilesInDirectory(
    const std::string& dirpath,
    const std::string& extension
) {
    VectorList<std::string> files;
    
#ifdef _WIN32
    // Windows implementation
    WIN32_FIND_DATAA findFileData;
    std::string search_path = dirpath + "/*" + extension;
    HANDLE hFind = FindFirstFileA(search_path.c_str(), &findFileData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Warning: Could not open directory: " << dirpath << std::endl;
        return files;
    }
    
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::string filename = findFileData.cFileName;
            if (extension.empty() || 
                (filename.size() >= extension.size() && 
                 filename.substr(filename.size() - extension.size()) == extension)) {
                files.push(dirpath + "/" + filename);
            }
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);
    
    FindClose(hFind);
#else
    // Unix/Linux/macOS implementation
    DIR* dir = opendir(dirpath.c_str());
    
    if (!dir) {
        std::cerr << "Warning: Could not open directory: " << dirpath << std::endl;
        return files;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        
        // Skip . and ..
        if (filename == "." || filename == "..") {
            continue;
        }
        
        std::string fullpath = dirpath + "/" + filename;
        
        // Check if it's a regular file (not directory)
        struct stat statbuf;
        if (stat(fullpath.c_str(), &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            // Check extension filter
            if (extension.empty() || 
                (filename.size() >= extension.size() && 
                 filename.substr(filename.size() - extension.size()) == extension)) {
                files.push(fullpath);
            }
        }
    }
    
    closedir(dir);
#endif
    
    return files;
}

// ============================================================================
// Tokenize a string
// ============================================================================
VectorList<std::string> FileReader::tokenize(
    const std::string& text,
    const std::string& delimiters
) {
    VectorList<std::string> tokens;
    
    size_t start = 0;
    size_t end = text.find_first_of(delimiters);
    
    while (end != std::string::npos) {
        if (end > start) {
            tokens.push(text.substr(start, end - start));
        }
        start = end + 1;
        end = text.find_first_of(delimiters, start);
    }
    
    // Add last token
    if (start < text.length()) {
        tokens.push(text.substr(start));
    }
    
    return tokens;
}

// ============================================================================
// Convert string to lowercase
// ============================================================================
std::string FileReader::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

// ============================================================================
// Check if file exists
// ============================================================================
bool FileReader::fileExists(const std::string& filepath) {
    std::ifstream file(filepath);
    return file.good();
}

// ============================================================================
// Check if path is directory
// ============================================================================
bool FileReader::isDirectory(const std::string& path) {
#ifdef _WIN32
    DWORD attrs = GetFileAttributesA(path.c_str());
    return (attrs != INVALID_FILE_ATTRIBUTES && 
            (attrs & FILE_ATTRIBUTE_DIRECTORY));
#else
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0) {
        return false;
    }
    return S_ISDIR(statbuf.st_mode);
#endif
}

#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>

FileReader::FileReader() : lastError_("") {}

std::string FileReader::readFileContent(const std::string& filepath) {
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        setError("Could not open file: " + filepath);
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    lastError_ = "";
    return buffer.str();
}

VectorList<std::string> FileReader::readFileLines(const std::string& filepath) {
    VectorList<std::string> lines;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        setError("Could not open file: " + filepath);
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push(line);
    }
    
    file.close();
    lastError_ = "";
    return lines;
}

VectorList<std::string> FileReader::readDirectory(const std::string& dirpath) {
    VectorList<std::string> contents;
    VectorList<std::string> files = listFiles(dirpath);
    
    for (int i = 0; i < files.size(); i++) {
        std::string filepath = dirpath;
        if (filepath.back() != '/') {
            filepath += "/";
        }
        filepath += files.at(i);
        
        std::string content = readFileContent(filepath);
        if (!content.empty() || lastError_.empty()) {
            contents.push(content);
        }
    }
    
    return contents;
}

VectorList<std::string> FileReader::listFiles(const std::string& dirpath) {
    VectorList<std::string> files;
    
    DIR* dir = opendir(dirpath.c_str());
    if (dir == nullptr) {
        setError("Could not open directory: " + dirpath);
        return files;
    }
    
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string filename = entry->d_name;
        
        // Skip . and ..
        if (filename == "." || filename == "..") {
            continue;
        }
        
        // Check if it's a .txt file
        if (isTextFile(filename)) {
            files.push(filename);
        }
    }
    
    closedir(dir);
    lastError_ = "";
    return files;
}

bool FileReader::fileExists(const std::string& filepath) {
    struct stat buffer;
    return (stat(filepath.c_str(), &buffer) == 0);
}

std::string FileReader::getLastError() const {
    return lastError_;
}

bool FileReader::isTextFile(const std::string& filename) {
    if (filename.length() < 4) {
        return false;
    }
    
    std::string extension = filename.substr(filename.length() - 4);
    return extension == ".txt";
}

void FileReader::setError(const std::string& error) {
    lastError_ = error;
}

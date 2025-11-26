#pragma once

#include <string>
#include "../containers/VectorList.h"

/**
 * FileReader Class
 * 
 * Handles reading text files and directories.
 * Provides simple interface for file I/O operations.
 */

class FileReader {
public:
    FileReader();
    
    /**
     * Read entire file content as a single string
     * @param filepath Path to the file
     * @return File content as string, or empty string on error
     */
    std::string readFileContent(const std::string& filepath);
    
    /**
     * Read file and split into lines
     * @param filepath Path to the file
     * @return VectorList of lines
     */
    VectorList<std::string> readFileLines(const std::string& filepath);
    
    /**
     * Read all .txt files from a directory
     * @param dirpath Path to the directory
     * @return VectorList of file contents (one entry per file)
     */
    VectorList<std::string> readDirectory(const std::string& dirpath);
    
    /**
     * Get list of all .txt files in a directory
     * @param dirpath Path to the directory
     * @return VectorList of filenames
     */
    VectorList<std::string> listFiles(const std::string& dirpath);
    
    /**
     * Check if a file exists and is readable
     * @param filepath Path to check
     * @return true if file exists and can be read
     */
    bool fileExists(const std::string& filepath);
    
    /**
     * Get the last error message
     * @return Error message from last operation
     */
    std::string getLastError() const;
    
private:
    std::string lastError_;
    
    /**
     * Check if filename has .txt extension
     */
    bool isTextFile(const std::string& filename);
    
    /**
     * Set error message
     */
    void setError(const std::string& error);
};

/*
 * FileReader - Functional I/O for ListContainer
 * 
 * WHAT: Read files and directories into lists for functional processing
 * HOW: Uses standard C++ file I/O, returns VectorList for immediate functional ops
 * 
 * Design Principles:
 * - Static methods (utility class)
 * - Returns VectorList for immediate chaining with map/filter/reduce
 * - Declarative API: readLines(), readWords(), readFiles()
 */

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "containers/VectorList.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

class FileReader {
public:
    /**
     * Read all lines from a file.
     * 
     * WHAT: Get a list of all lines in a text file
     * 
     * @param filepath Path to the file
     * @return VectorList of strings, one per line
     * 
     * Example:
     *   auto lines = FileReader::readLines("data.txt");
     *   lines.forEach([](std::string line) { std::cout << line << std::endl; });
     */
    static VectorList<std::string> readLines(const std::string& filepath);

    /**
     * Read all words from a file (whitespace-separated).
     * 
     * WHAT: Get a list of all words in a text file
     * 
     * @param filepath Path to the file
     * @return VectorList of words
     * 
     * Example:
     *   auto words = FileReader::readWords("keywords.txt");
     *   int count = words.size();
     */
    static VectorList<std::string> readWords(const std::string& filepath);

    /**
     * Read entire file as single string.
     * 
     * WHAT: Get complete file content as one string
     * 
     * @param filepath Path to the file
     * @return File content as string
     */
    static std::string readFile(const std::string& filepath);

    /**
     * List all files in a directory.
     * 
     * WHAT: Get paths to all files in a directory
     * 
     * @param dirpath Path to directory
     * @param extension Optional file extension filter (e.g., ".txt")
     * @return VectorList of file paths
     * 
     * Example:
     *   auto files = FileReader::readFilesInDirectory("data/", ".txt");
     *   auto allContent = files.map<std::string>([](std::string path) {
     *       return FileReader::readFile(path);
     *   });
     */
    static VectorList<std::string> readFilesInDirectory(
        const std::string& dirpath, 
        const std::string& extension = ""
    );

    /**
     * Tokenize a string by delimiters.
     * 
     * WHAT: Split string into tokens
     * 
     * @param text The text to tokenize
     * @param delimiters Characters to split on (default: whitespace)
     * @return VectorList of tokens
     * 
     * Example:
     *   auto tokens = FileReader::tokenize("hello,world", ",");
     *   // Result: {"hello", "world"}
     */
    static VectorList<std::string> tokenize(
        const std::string& text,
        const std::string& delimiters = " \t\n\r"
    );

    /**
     * Convert string to lowercase.
     * 
     * WHAT: Normalize text to lowercase
     * 
     * @param str Input string
     * @return Lowercase version
     */
    static std::string toLower(const std::string& str);

    /**
     * Check if a file exists.
     * 
     * @param filepath Path to check
     * @return true if file exists and is readable
     */
    static bool fileExists(const std::string& filepath);

    /**
     * Check if a path is a directory.
     * 
     * @param path Path to check
     * @return true if path is a directory
     */
    static bool isDirectory(const std::string& path);
};

#include "FileReader.cpp"

# Functional-OO Design Document
**Project:** ListContainer Functional Extensions  
**Date Started:** November 25, 2025  
**Author:** [Your Name/Team]

---

## 1. Assignment Interpretation

### What is Required?
Based on the assignment specification, we need to:
1. Extend existing ListContainer library with **functional programming** capabilities
2. Support reading, searching, and sorting files and network streams
3. Implement aggregation methods (counting inversions, averaging, mapping transformations)
4. Provide a high-level interface (menu-driven, command-driven, or library API)
5. Focus on the **WHAT** (declarative) rather than the **HOW** (imperative)

### Example Use Case from Assignment
> Given a directory full of text files, scrape all keywords (from a keyword file) and list them in decreasing order of occurrence frequency across all documents.

---

## 2. Functional-OO Principles

### What is Functional Programming?
- **Declarative**: Describe WHAT you want, not HOW to get it
- **Immutability**: Prefer creating new data over modifying existing
- **Higher-order functions**: Functions that take/return other functions
- **Composition**: Build complex operations from simple ones

### How Does This Apply to Our ListContainer?
Our existing OO hierarchy provides:
- **Abstraction**: `AbstractList<T>` defines WHAT a container can do
- **Polymorphism**: Different containers implement HOW differently
- **Encapsulation**: Internal details are hidden

We'll add functional operations that:
- Use **lambdas** to specify transformations
- Enable **method chaining** for composition
- Maintain **type safety** through templates

---

## 3. Core Functional Operations Design

### 3.1 Map (Transform)
**WHAT:** Apply a transformation to every element, producing a new list.

```cpp
template <typename U>
VectorList<U> map(std::function<U(T)> transform);
```

**Example Use:**
```cpp
VectorList<int> numbers = {1, 2, 3, 4, 5};
VectorList<int> squared = numbers.map([](int x) { return x * x; });
// Result: {1, 4, 9, 16, 25}
```

### 3.2 Filter (Select)
**WHAT:** Keep only elements that satisfy a predicate.

```cpp
VectorList<T> filter(std::function<bool(T)> predicate);
```

**Example Use:**
```cpp
VectorList<int> numbers = {1, 2, 3, 4, 5};
VectorList<int> evens = numbers.filter([](int x) { return x % 2 == 0; });
// Result: {2, 4}
```

### 3.3 Reduce (Fold/Aggregate)
**WHAT:** Combine all elements into a single value.

```cpp
template <typename U>
U reduce(U initial, std::function<U(U, T)> combine);
```

**Example Use:**
```cpp
VectorList<int> numbers = {1, 2, 3, 4, 5};
int sum = numbers.reduce(0, [](int acc, int x) { return acc + x; });
// Result: 15
```

### 3.4 ForEach (Side Effects)
**WHAT:** Perform an action on each element (for I/O, logging, etc.).

```cpp
void forEach(std::function<void(T)> action);
```

**Example Use:**
```cpp
VectorList<std::string> words = {"hello", "world"};
words.forEach([](std::string s) { std::cout << s << std::endl; });
```

### 3.5 Method Chaining
Enable composition:
```cpp
auto result = list
    .filter([](int x) { return x > 0; })
    .map([](int x) { return x * 2; })
    .reduce(0, [](int a, int b) { return a + b; });
```

---

## 4. File Processing Design

### 4.1 FileReader Class
**WHAT:** Read text files and produce lists of lines/words/tokens.

```cpp
class FileReader {
public:
    static VectorList<std::string> readLines(const std::string& filepath);
    static VectorList<std::string> readWords(const std::string& filepath);
    static VectorList<std::string> readFilesInDirectory(const std::string& dirpath);
};
```

### 4.2 Tokenizer
**WHAT:** Split text into tokens based on delimiters.

```cpp
VectorList<std::string> tokenize(const std::string& text, const std::string& delimiters = " \t\n");
```

---

## 5. Keyword Frequency Counter Design

### High-Level Algorithm (Declarative)
```cpp
// WHAT we want:
// 1. Read keyword file -> list of keywords
// 2. Read all data files -> list of file contents
// 3. For each file, count occurrences of each keyword
// 4. Aggregate counts across files
// 5. Sort by frequency (descending)
// 6. Output results
```

### Functional Implementation Strategy
```cpp
auto keywords = FileReader::readWords("keywords.txt");
auto dataFiles = FileReader::readFilesInDirectory("data/");

// Map each file to a word frequency map
auto allCounts = dataFiles
    .map([&keywords](std::string filepath) {
        return countKeywords(filepath, keywords);
    })
    .reduce(emptyMap, mergeMaps);

// Sort and display
auto sorted = sortByValue(allCounts);
sorted.forEach(printResult);
```

---

## 6. Advanced Aggregations Design

### 6.1 Statistical Operations
```cpp
double average();
T min();
T max();
T median();
```

### 6.2 Inversion Counting
**WHAT:** Count pairs (i, j) where i < j but list[i] > list[j].

```cpp
int countInversions();
```

### 6.3 GroupBy
**WHAT:** Group elements by a key function.

```cpp
template <typename K>
std::map<K, VectorList<T>> groupBy(std::function<K(T)> keyExtractor);
```

**Example:**
```cpp
VectorList<std::string> words = {"apple", "apricot", "banana", "blueberry"};
auto grouped = words.groupBy([](std::string s) { return s[0]; });
// Result: {'a': ["apple", "apricot"], 'b': ["banana", "blueberry"]}
```

---

## 7. Interface Design

### Option A: Library API
Users import and use functions programmatically.

### Option B: Command-Line Interface
```bash
./functional_list --operation count-keywords --keywords keywords.txt --data-dir ./data/
./functional_list --operation sort --input numbers.txt --order desc
```

### Option C: Interactive Menu
```
=== Functional List Operations ===
1. Count keyword frequencies
2. Sort file
3. Statistical analysis
4. Custom transformation
5. Exit
Enter choice:
```

**Decision:** Implement all three for flexibility.

---

## 8. Design Decisions & Rationale

### Why Functional-OO?
1. **Composability**: Chain operations naturally
2. **Readability**: Code reads like problem description
3. **Testability**: Pure functions are easy to test
4. **Flexibility**: Users specify behavior via lambdas

### Why Lambdas?
- Inline specification of transformations
- Type inference reduces boilerplate
- Closures capture context naturally

### Why Templates?
- Type-safe generic operations
- Compile-time optimization
- Works with any type (including custom structs)

---

## 9. Implementation Plan

### Phase 1: Core Functional Operations (Task 2)
- Add `map`, `filter`, `reduce`, `forEach` to `SequentialList<T>`
- Implement in both `VectorList` and `LinkedList`
- Enable method chaining (return `*this` or new instance)

### Phase 2: File I/O (Task 3)
- `FileReader` class
- `Tokenizer` utilities
- Directory scanning

### Phase 3: Keyword Counter (Task 4)
- Implement example use case
- Use functional operations for entire pipeline

### Phase 4: Advanced Features (Task 5)
- Statistical operations
- Inversion counting
- GroupBy

### Phase 5: Interface (Task 6)
- CLI argument parsing
- Interactive menu
- API documentation

---

## 10. Testing Strategy

Each functional operation needs:
1. **Unit tests**: Individual operation correctness
2. **Integration tests**: Chained operations
3. **Edge cases**: Empty lists, single elements, large datasets
4. **Performance tests**: Ensure reasonable efficiency

---

## Next Steps
1. ✅ Create design document
2. ⏭️ Implement functional operations in `SequentialList<T>`
3. ⏭️ Test with existing containers
4. ⏭️ Build file I/O module
5. ⏭️ Implement keyword counter example

---

**Last Updated:** November 25, 2025

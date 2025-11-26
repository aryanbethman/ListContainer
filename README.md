# Functional-OO List Container System
**CS F301 POPL Assignment | November 2025**

A C++ implementation combining OO design with functional programming paradigms for file I/O and keyword frequency analysis.

## Quick Start

```bash
# Build and run (single command)
make all && ./demo
```

## Project Structure

```
ListContainer/
├── README.md
├── Makefile
├── design_log.md
├── genai_usage.md
│
├── common/
│   └── list_err.h              # Error handling
│
├── containers/                 # Core container implementations
│   ├── AbstractList.h          # Base interface for all containers
│   ├── SequentialList.h        # Interface for index-based access
│   ├── RestrictedSequentialList.h
│   ├── PriorityBased.h         # Interface for priority-based access
│   ├── VectorList.h/cpp        # Dynamic array implementation
│   ├── LinkedList.h/cpp        # Doubly linked list implementation
│   ├── ListNode.h              # Node structure for LinkedList
│   ├── Stack.h/cpp             # LIFO adapter
│   ├── Queue.h/cpp             # FIFO adapter
│   ├── Deque.h/cpp             # Double-ended queue
│   ├── Heap.h/cpp              # Min-heap implementation
│   └── PriorityQueue.h/cpp     # Priority queue (Heap wrapper)
│
├── functional/                 # Functional programming operations
│   ├── FunctionalOps.h         # map, filter, reduce, forEach
│   └── Aggregators.h           # sum, average, min, max, product, etc.
│
├── algorithms/                 # Search and sort algorithms
│   ├── Search.h                # Linear, binary, predicate-based search
│   └── Sort.h                  # QuickSort, bubble sort, insertion sort
│
├── io/                         # File I/O operations
│   ├── FileReader.h/cpp        # Read files and directories
│   └── TextTokenizer.h/cpp     # Tokenize text into words
│
├── analysis/                   # Text analysis
│   └── KeywordCounter.h/cpp    # Keyword frequency analysis (primary feature)
│
├── test_data/                  # Sample data for testing
│   ├── keywords.txt            # Sample keywords
│   └── sample_texts/           # Sample text files
│       ├── doc1.txt
│       ├── doc2.txt
│       ├── doc3.txt
│       └── programming_article.txt
│
├── tests/                      # Comprehensive test suite
│   ├── test_functional.cpp     # Tests for map, filter, reduce, aggregators
│   ├── test_fileio.cpp         # Tests for FileReader and TextTokenizer
│   └── test_textanalysis.cpp   # Tests for KeywordCounter
│
├── demo.cpp                    # Interactive CLI demonstration
└── main.cpp                    # Original container demo (preserved)
```

## Key Features

- **Functional Operations**: map, filter, reduce on list containers
- **Keyword Frequency Analysis**: Count keyword occurrences from files (assignment requirement)
- **File I/O**: Read files/directories, tokenize text
- **Search/Sort**: Linear, binary search; QuickSort, bubble, insertion sort
- **Interactive Demo**: Menu-driven CLI with 6 sections

## Class Hierarchy

`AbstractList<T>` is the root interface defining `push`, `pop`, `size`, `clear`, `name`.

-   `SequentialList<T>`: This abstract class inherits from `AbstractList` and represents containers that are accessed by an integer index. It adds the abstract methods `insert_at`, `erase_at`, and `at`.

    -   `VectorList<T>` and `LinkedList<T>`: These are the two main concrete implementations of `SequentialList`. They provide the full functionality of a sequential list, one using a from-scratch dynamic array and the other using from-scratch nodes and pointers.

    -   `RestrictedSequentialList<T>`: This is an abstract "marker" class. Its purpose is to group the adapter classes (`Stack`, `Queue`, `Deque`) that have a sequential nature but do not allow arbitrary access with `insert_at` or `at`.

        -   `Stack<T>`, `Queue<T>`, `Deque<T>`: These are adapter classes. They contain a more fundamental container (`VectorList` or `LinkedList`) and provide a simpler, more specific interface (LIFO for Stack, FIFO for Queue, etc.).

-   `PriorityBased<T>`: This abstract class inherits from `AbstractList` and is for containers where elements are accessed by priority, not position. It adds the abstract `top` method.


## Build & Run

```bash
make all        # Build everything
./demo          # Run interactive demo
make tests      # Run test suite
make clean      # Clean build artifacts
make bundle     # Create submission zip
```

## Demo Menu

1. Container Operations (basic push/pop/size)
2. Functional Operations (map/filter/reduce examples)
3. Aggregation Functions (sum/average/min/max)
4. **Keyword Frequency Analysis** (primary assignment feature)
5. Search & Sort Demos
6. File I/O Operations

## Documentation

- `design_log.md` - Chronological development log
- `genai_usage.md` - GenAI interaction documentation
- `README.md` - This file

## Running Tests

```bash
# Build all tests
make tests

# Run individual test suites
./test_functional       # Test map, filter, reduce, aggregators (6 tests)
./test_fileio          # Test FileReader and TextTokenizer (3 tests)
./test_textanalysis    # Test KeywordCounter analysis (3 tests)

# Or run all tests sequentially
./test_functional && ./test_fileio && ./test_textanalysis
```

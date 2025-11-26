# ListContainer — Submission Report
**CS F301 POPL Assignment | November 2025**

**Team:** Solo  
**Member:** Aryan Bethmangalkar (2023A7PS0433G)

---

## Abstract (one paragraph)
This project extends a from-scratch C++ list container library with a small Functional-OO layer: template functions for functional operations (map, filter, reduce), utility aggregators, file I/O for reading and tokenizing plain text, basic search and sort algorithms, and a keyword-frequency analysis tool which is the primary deliverable for the assignment. The code is modular, tested, and accompanied by an interactive CLI demo and concise documentation.

---

## Contents of this report
1. Quick start & prerequisites
2. Detailed project structure
3. Design philosophy and key decisions
4. Module-by-module descriptions and API summary
5. How the primary feature (keyword frequency) works
6. Tests and verification
7. Implementation notes and notable code excerpts
8. GenAI usage log (refer to genai_usage.md)
9. Known limitations and future work
10. Submission checklist and how to reproduce

---

## 1. Quick start & prerequisites
Prerequisites
- macOS or Linux (POSIX APIs used for directory listing)
- g++ (C++11 or later)
- make

Build and run demo (recommended):

```bash
# Build everything and run the interactive demo
make all && ./demo
```

Run only tests (recommended for graders who prefer automated verification):

```bash
make tests
./test_functional
./test_fileio
./test_textanalysis
# or run all three sequentially
./test_functional && ./test_fileio && ./test_textanalysis
```

Notes
- All required demo inputs are in `test_data/` (keywords.txt + sample_texts/).
- The demo is menu-driven and interactive; option 4 runs the keyword frequency analysis (primary assignment requirement).

---

## 2. Detailed project structure
```
ListContainer/
├── Makefile
├── README.md
├── SUBMISSION_REPORT.md    # This file
├── design_log.md
├── genai_usage.md
├── .gitignore
│
├── common/
│   └── list_err.h          # error definitions and utility macros
│
├── containers/             # core, from-scratch data structures
│   ├── AbstractList.h
│   ├── SequentialList.h
│   ├── RestrictedSequentialList.h
│   ├── PriorityBased.h
│   ├── VectorList.h
│   ├── VectorList.cpp
│   ├── LinkedList.h
│   ├── LinkedList.cpp
│   ├── ListNode.h
│   ├── Stack.h
│   ├── Stack.cpp
│   ├── Queue.h
│   ├── Queue.cpp
│   ├── Deque.h
│   ├── Deque.cpp
│   ├── Heap.h
│   ├── Heap.cpp
│   └── PriorityQueue.h
│
├── functional/             # functional-OO layer (header-only templates)
│   ├── FunctionalOps.h     # map, filter, reduce, forEach
│   └── Aggregators.h       # sum, average, min, max, countIf, any/all
│
├── algorithms/             # small algorithm utilities
│   ├── Search.h            # linear, binary, predicate-based
│   └── Sort.h              # insertion, bubble, quicksort variants (custom comparator)
│
├── io/                     # file and text utilities
│   ├── FileReader.h
│   ├── FileReader.cpp
│   └── TextTokenizer.h
│   └── TextTokenizer.cpp
│
├── analysis/               # assignment-specific analysis tools
│   └── KeywordCounter.h
│   └── KeywordCounter.cpp
│
├── test_data/
│   ├── keywords.txt
│   └── sample_texts/ (doc1.txt, doc2.txt, doc3.txt, programming_article.txt)
│
├── tests/
│   ├── test_functional.cpp
│   ├── test_fileio.cpp
│   └── test_textanalysis.cpp
│
├── demo.cpp                # interactive CLI demonstration (menu-driven)
└── main.cpp                # original demo / compatibility
```

---

## 3. Design philosophy and key decisions
High-level goals
- Separate WHAT (high-level specification) from HOW (implementation details).
- Keep the functional layer at the top (free template functions that express WHAT), and implement HOW using OO classes that manage resources and encapsulate behavior.
- Preserve and extend the from-scratch container implementations from the earlier assignment; avoid using standard library associative containers for the core assignment features (as required).

Key decisions
- Functional operations implemented as header-only free template functions (in `functional/FunctionalOps.h`) — this preserves the Open-Closed Principle and allows operating on any `AbstractList<T>`.
- For containers without random-access (`Stack`, `Queue`), `FunctionalOps` uses a fallback path (pop/push with temporary buffer) and an optimized path for `SequentialList` (which exposes `at()`). This provides generality with acceptable trade-offs.
- Keyword frequency uses `VectorList<KeywordFrequency>` (from-scratch) and a custom sort; chosen for clarity and to meet the "from-scratch" constraint.
- File I/O uses POSIX `dirent.h` for directory listing (documented in genai_usage.md); this is simple and reliable on the target platform (macOS/linux).

---

## 4. Module-by-module descriptions and API summary
This section gives a concise API-like summary so graders can quickly locate and test relevant pieces.

containers/
- AbstractList<T> — pure abstract interface (push/pop/size/clear/name)
- SequentialList<T> — adds index-based methods (insert_at, erase_at, at)
- VectorList<T> — dynamic array implementation. Important methods: `push`, `pop`, `insert_at`, `erase_at`, `at`, `size`.
  - Also implements copy constructor and copy-assignment operator (deep copy) to enforce Rule of Three.
- LinkedList<T> — node-based sequential container with similar API.
- Stack/Queue/Deque — adapters around `VectorList`/`LinkedList` for restricted behavior.
- Heap/PriorityQueue — priority-based containers built on top of `VectorList`.

functional/
- map<AbstractList<T>, F> → returns a `VectorList<U>` containing transform(x) for each x
- filter<AbstractList<T>, P> → returns `VectorList<T>` with elements satisfying predicate
- reduce<AbstractList<T>, Combiner> → accumulates values using combiner and initial value
- forEach<AbstractList<T>, Action> → applies side-effect action to each element
- Aggregators: `sum`, `average`, `min`, `max`, `countIf`, `any`, `all`

algorithms/
- Search.h: `indexOf`, `contains`, `findAll` (supports predicate)
- Sort.h: `insertionSort`, `bubbleSort`, `quickSort` variants that accept comparator functions

io/
- FileReader
  - `VectorList<string> readDirectory(const string &path)` — returns a list of file paths
  - `string readFileToString(const string &path)`
- TextTokenizer
  - `VectorList<string> tokenize(const string &text, bool toLower=true, bool removePunct=true)`

analysis/
- KeywordCounter
  - `VectorList<KeywordFrequency> analyzeFiles(VectorList<string> keywords, VectorList<string> filepaths)`
  - Supports case-sensitive or case-insensitive modes via configuration
  - Tracks statistics: totalWordsProcessed, keywordsFound

---

## 5. How the primary feature works (keyword frequency analysis)
Algorithm (high-level)
1. Load keywords from `keywords.txt` into a `VectorList<string>`.
2. Initialize a `VectorList<KeywordFrequency>` with each keyword and count=0.
3. For each data file in the selected directory:
   - Read file content with `FileReader`.
   - Tokenize using `TextTokenizer` (case normalization and punctuation removal are optional settings).
   - For each token (word), scan the `KeywordFrequency` list to find a match. If found, increment its count.
4. When all files processed, sort `KeywordFrequency` list by count descending and present results.

Complexity and trade-offs
- This approach is O(totalWords * numKeywords) — O(n*m) — not optimal for extremely large corpora but simple, easy to validate, and consistent with a "from-scratch" constraint (no hash tables).
- For larger data, a hash-table or trie would be significantly faster and could be added as an extension.

Sample expected output (from demo)
```
Loading keywords: keywords.txt (15 keywords)
Analyzing directory: test_data/sample_texts/ (4 files)
Files processed: 4
Total tokens: 1051
Top keywords:
  data        34
  search      18
  structure   12
  algorithm   10
  sort         7
```

---

## 6. Tests and verification
Test suite overview (located in `tests/`)
- `test_functional.cpp` — verifies `map`, `filter`, `reduce`, `forEach`, and aggregators (6 tests)
- `test_fileio.cpp` — verifies `FileReader::readFileToString`, `readDirectory`, and `TextTokenizer` (3 tests)
- `test_textanalysis.cpp` — verifies `KeywordCounter` correctness and case handling (3 tests)

How to run

```bash
make tests
./test_functional
./test_fileio
./test_textanalysis
```

Expected outcome
- All tests should pass. The Makefile contains targets to build each test binary individually and a combined `make tests` target.

Automated verification note
- The test binaries are small and run in < 1 second on a typical laptop; they print PASS/FAIL messages for quick evaluation.

---

## 7. Implementation notes and notable code excerpts
Memory management
- `VectorList` manages a raw dynamic array; originally the class had a destructor but no copy-constructor/assignment operator, which caused a double-free bug when a temporary or copy was destroyed. The fix:
  - Implemented `VectorList(const VectorList<T>& other)` which allocates new memory and copies elements.
  - Implemented `VectorList<T>& operator=(const VectorList<T>& other)` with self-assignment check and deep copy.

Functional operations design
- `map`/`filter`/`reduce` are header-only template functions that accept `std::function` or callable objects (lambdas). They return a new `VectorList` to preserve immutability at the operation level.

File I/O and tokenization
- `FileReader::readDirectory` uses POSIX `opendir`/`readdir` and filters for regular files (optionally `.txt`).
- `TextTokenizer` strips punctuation and optionally lowercases tokens for case-insensitive matching.

Sorting and presentation
- `KeywordFrequency` is a small struct (`string keyword; int count;`) with comparison operators defined to allow sorting by count descending.

---

## 8. GenAI usage log (summarized)
We documented the GenAI interactions in `genai_usage.md`. Summary:
- Six major Copilot-assisted interactions: architecture, handling non-sequential containers, file I/O, sorting strategy, keyword counting algorithm, and the memory bug fix.
- Most impactful guidance: prefer template functions for functional semantics and provide a fallback path for non-sequential containers.
- Helped in creation of sample data for tests, logs and finishing touches on the report.

---

## 9. Known limitations and suggested future work
Limitations
- Keyword counting uses O(n*m) scanning; not suitable for very large corpora.
- File I/O relies on POSIX `dirent.h` (not natively portable to Windows without compatibility layers).
- Sorting implementations are simple and may not be as optimized as `std::sort`.

Suggested improvements
- Add a `HashMap`-based `KeywordCounter` for large-scale performance.
- Replace POSIX APIs with C++17 `std::filesystem` for cross-platform portability.
- Add more unit tests and fuzz tests for tokenization edge cases.

---

## 10. Submission checklist & reproducibility
Files to include in submission (zip)
- Source code (all folders listed above)
- `Makefile`
- `README.md`, `SUBMISSION_REPORT.md`, `design_log.md`, `genai_usage.md`
- `test_data/` sample input files
- `tests/` test sources and the resulting test binaries (optional but helpful)

Commands to create submission zip (example)

```bash
make bundle   # if Makefile target exists and creates ListContainer_Submission.zip
# or manual
zip -r ListContainer_Submission.zip . -x '*.git*' '*/obj/*' '*/build/*' '*.DS_Store'
```

Verification
- After creating the zip, extract it into a fresh directory and run the quick-start commands above to verify build+demo.

---

## Closing notes
This project demonstrates a clear separation between high-level functional specifications (map/filter/reduce) and low-level OO implementations (containers, file I/O). The codebase is compact, documented, and easy to evaluate. If you want, I can:
- produce the zipped submission and confirm its size, or
- create a short transcript and annotated screenshot set to accompany the demo video.

**Status:** Expanded consolidated submission report created on 26/11/2025

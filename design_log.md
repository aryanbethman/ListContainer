# Design and Development Log
**CS F301 POPL Assignment | November 2025**

**Team:** Solo  
**Members:** Aryan Bethmangalkar (2023A7PS0433G)

---

## Entry 1: Assignment Analysis (23/11/2025 14:30)

**Requirements Identified:**
- Extend list containers with functional programming (map, filter, reduce)
- File I/O for reading and tokenizing text files
- Keyword frequency analysis from multiple files
- Menu-driven interface for demonstration

**Design Philosophy:**
- Focus on WHAT (specification) before HOW (implementation)
- Free template functions for functional operations (not modifying base classes)
- Composition for I/O modules (FileReader, TextTokenizer)

---

## Entry 2: Key Design Decisions (23/11/2025 14:45)

**1. Functional Operations as Free Functions**
- Why: Maintains Open-Closed Principle, works with any AbstractList<T>
- Implementation: Template functions using std::function for lambda support

**2. Interactive Menu-Driven CLI**
- Why: Easy to demonstrate and test, clear for evaluators
- Alternative considered: Command-line args (less interactive)

**3. Keyword Counting with VectorList<KeywordFrequency>**
- Why: Maintains from-scratch requirement, simple and testable

---

## Entry 3: Module Architecture (23/11/2026 15:30)

**Directory Structure:**
```
functional/  - map, filter, reduce, aggregators
io/          - FileReader, TextTokenizer  
analysis/    - KeywordCounter (primary feature)
algorithms/  - Search and sort
test_data/   - Sample keywords and text files
tests/       - Comprehensive test suite
```

**Dependency Chain:** containers → functional → algorithms → io → analysis → demo

---

## Entry 4: Implementation Phase 

### **Implemented Components:** (23/11/2025 16:00)
- Functional operations: map, filter, reduce, forEach, aggregators
- File I/O: Read files/directories, tokenize with punctuation removal

### **Implemented Components:** (25/11/2025 20:00)
- Keyword analysis: Load keywords, count frequencies, sort descending
- Search/Sort: Linear, binary search; QuickSort, bubble, insertion sort

### **Implemented Components:** (26/11/2025 9:00)
- Interactive demo with 6 menu sections
- Test suite: 15 tests covering all modules

**Time Spent:** ~5 hours total

---

## Entry 5: Critical Bug Fix (26/11/2025 11:30)

**Problem:** Double free error - `malloc: double free for ptr 0x151810600`

**Root Cause:** VectorList violated Rule of Three (had destructor, no copy constructor/assignment operator)

**Solution:** Implemented deep copy semantics:
- Copy constructor allocates new memory, copies elements
- Assignment operator with self-assignment check

**Result:** All 15 tests passing, no memory errors

---

**Status:** Complete


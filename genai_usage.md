# GenAI Usage Report
**CS F301 POPL Assignment | November 2025**

**Team:** Solo  
**Members:** Aryan Bethmangalkar (2023A7PS0433G)

---

## Interaction 1: Architecture Design
**Tool:** GitHub Copilot  
**Date:** 23/11/2025 14:00

**Prompt:** "Analyze PoPL assignment and create implementation plan with directory structure and testing strategy"

**Key Suggestions:**
- Modular structure: functional/, io/, analysis/, algorithms/
- Free template functions for functional ops (not methods in container classes)
- Interactive menu-driven CLI for easy demonstration

**Insight:** Functional programming in C++ works best with free functions using templates and std::function. Keeps functional paradigm separate from OO structure.

**Incorporation:** Adopted modular structure, implemented all functional operations as free template functions.

**Result:** Successful - Clean, maintainable architecture

---

## Interaction 2: Handling Non-Sequential Containers
**Tool:** GitHub Copilot  
**Date:** 23/11/2025 14:30

**Prompt:** "How to implement map/filter/reduce for containers without random access like Stack?"

**Suggestion:** Use `dynamic_cast` to check container type, use efficient path for SequentialList (has `at()`), fall back to pop/push for others.

**Insight:** Generic algorithms need multiple implementation paths based on container capabilities.

**Incorporation:** Added runtime type checking in FunctionalOps.h with conditional logic.

**Result:** Works for all container types

---

## Interaction 3: File I/O Implementation
**Tool:** GitHub Copilot Autocomplete  
**Date:** 23/11/2025 15:00

**Suggestions:**
- Use `<fstream>` for file reading
- Use `<dirent.h>` for directory listing (POSIX)
- Use `<sys/stat.h>` for file existence checks

**Trade-off:** POSIX APIs work on macOS/Linux but not Windows. Acceptable for this assignment's platform.

**Incorporation:** Implemented FileReader using POSIX APIs with proper error handling.

**Result:** Works perfectly on macOS

---

## Interaction 4: Sorting Algorithm Choice
**Tool:** GitHub Copilot  
**Date:** 25/11/2025 19:00

**Prompt:** "Best way to sort VectorList with custom comparator without std::sort?"

**Warning:** Using `erase_at`/`insert_at` in sorting is inefficient (O(n) per operation). Suggested simpler algorithms like insertion sort.

**Insight:** With constrained API, simpler algorithms (insertion sort) are more reliable than complex ones (quicksort).

**Incorporation:** Implemented insertion sort and bubble sort for sorting operations.

**Result:** Works but not optimal - acceptable for assignment scope

---

## Interaction 5: Keyword Frequency Algorithm
**Tool:** GitHub Copilot  
**Date:** 25/11/2025 20:30

**Prompt:** "Implement keyword frequency counting without std::map"

**Suggestion:** Use `VectorList<KeywordFrequency>` struct. For each word: search list, increment if found, add if not found, then sort by count.

**Trade-off:** O(n*m*k) complexity vs O(n*m) with hash table. Simple and meets "from-scratch" requirement.

**Incorporation:** Implemented exactly as suggested in KeywordCounter.

**Result:** Works correctly for moderate-sized files

---

## Interaction 6: Memory Management Bug
**Tool:** GitHub Copilot  
**Date:** 26/11/2025 11:00

**Prompt:** "Double free error in VectorList - how to implement Rule of Three properly?"

**Suggestions:**
- Add copy constructor with deep copy (allocate new array, copy elements)
- Add assignment operator with self-assignment check
- Both need to prevent shared pointers between objects

**Insight:** C++ Rule of Three - if class manages resources (has destructor), must define copy constructor and assignment operator.

**Incorporation:** Implemented deep copy semantics in VectorList.h/cpp.

**Result:** All tests passing, no memory errors

---

## Summary

**Total Interactions:** 6 major interactions  
**Success Rate:** 5 fully successful, 1 partially successful  
**Most Valuable Insight:** Free template functions for functional programming in C++ maintain separation of concerns and work with any AbstractList<T> type.

**Key Learnings:**
- Design decisions documented before implementation
- Simple solutions often better with API constraints  
- GenAI excellent for architecture guidance, human judgment needed for trade-offs
- Rule of Three is critical for resource-managing classes

---

**Status:** Complete

# Development Log - Functional ListContainer Extension

**Project:** CS F301 PoPL End-Semester Assignment  
**Team Members:** [Add your name(s) here]  
**Repository:** [Add GitHub repo URL]

---

## Entry 1: Project Setup and Version Control
**Date:** November 25, 2025, ~[Current Time]  
**Duration:** ~30 minutes  
**Activity:** Repository initialization and design planning

### Actions Taken
1. Initialized Git repository in existing `ListContainer` directory
2. Created `.gitignore` to exclude build artifacts (*.o, executables, .DS_Store)
3. Made initial commit with existing ListContainer implementation from previous assignment
4. Pushed to GitHub remote repository
5. Fixed accidental commit of ignored files by running `git rm -r --cached .` and re-committing

### Design Decisions
- **Version Control:** Using Git for chronological tracking (required for assignment deliverable)
- **Repository Structure:** Building upon existing ListContainer rather than starting from scratch
- **Branching Strategy:** Will use feature branches for major additions

### GenAI Assistance Used
**Tool:** GitHub Copilot (in VS Code)  
**Prompts:**
1. "Read PoPL assignment PDF and create implementation plan"
2. "How do I remove files from git that are in gitignore"

**Responses & Insights:**
- Copilot generated comprehensive 12-step todo list covering all assignment requirements
- Explained `git rm --cached` for removing tracked files without deleting local copies
- Suggested creating design document before implementation (functional-OO principle)

**What Was Incorporated:**
✅ Todo list structure accepted and refined  
✅ Git cleanup strategy implemented  
✅ Design-first approach adopted  

**Success/Failure:**
✅ **Success** - Clean repository established with proper gitignore
✅ **Success** - Clear roadmap created

### Insights Gained
- Assignment emphasizes **documentation of the process** as much as the final code
- Functional-OO approach means design must precede implementation
- The "WHAT before HOW" principle applies to project planning itself

---

## Entry 2: Functional Interface Design
**Date:** November 25, 2025, ~[Current Time]  
**Duration:** ~45 minutes  
**Activity:** Creating high-level design document

### Actions Taken
1. Created `DESIGN.md` with comprehensive functional-OO architecture
2. Defined core operations: `map`, `filter`, `reduce`, `forEach`
3. Specified interfaces for file I/O and keyword counting
4. Documented design rationale and testing strategy

### Design Decisions

#### Why Add Functional Methods to SequentialList?
- **Reasoning:** `SequentialList<T>` is the abstract class for indexed containers
- Both `VectorList` and `LinkedList` will inherit these operations
- Enables polymorphic use of functional operations
- **Alternative Considered:** Free functions that take containers as arguments
- **Decision:** Member functions for better encapsulation and method chaining

#### Lambda Signatures Chosen
```cpp
map:    std::function<U(T)> transform
filter: std::function<bool(T)> predicate  
reduce: std::function<U(U, T)> combine
forEach: std::function<void(T)> action
```

**Reasoning:** 
- `std::function` enables both lambdas and regular functions
- Template parameter `U` allows type transformation in `map` and `reduce`
- Generic enough for all use cases in assignment

### GenAI Assistance Used
**Tool:** GitHub Copilot  
**Prompts:**
1. "Design functional programming interfaces for C++ list containers using lambdas"
2. "How to implement method chaining in C++ with templates"

**Responses & Insights:**
- Suggested using `std::function` wrapper for lambda parameters
- Recommended return-by-value for immutability vs return-by-reference for chaining
- Provided examples of functional patterns in C++11/14/17

**What Was Incorporated:**
✅ `std::function` signatures for all operations  
✅ Template parameter `U` for map/reduce transformations  
⚠️ Method chaining design still needs refinement (mutable vs immutable approach)  

**What Was NOT Incorporated:**
❌ Suggestion to use `std::ranges` (C++20) - staying with C++11 for compatibility  
❌ Complex monadic patterns - keeping it simple for clarity  

**Success/Failure:**
✅ **Success** - Clear, implementable design created  
⚠️ **Partial** - Still need to decide on mutable vs immutable operations  

### Open Questions
1. Should `map`/`filter` modify the list in-place or return a new list?
   - **Immutable (functional):** Better for safety, more memory usage
   - **Mutable (pragmatic):** Better performance, less functional purity
   - **Decision needed:** Will consult assignment requirements emphasis on "functional"

2. How to handle method chaining with templates?
   - Need to ensure return types work with auto keyword
   - Consider builder pattern vs direct returns

### Next Steps
1. Implement `map`, `filter`, `reduce`, `forEach` in `SequentialList.h`
2. Test with existing `VectorList` and `LinkedList`
3. Commit with message: "Add functional operations to SequentialList"

---

## Entry 3: TDD Implementation of Functional Operations
**Date:** November 25, 2025, Evening  
**Duration:** ~2 hours  
**Activity:** Implementing map, filter, reduce, forEach using Test-Driven Development

### Actions Taken
1. Created feature branch `feature/functional-operations` for version control
2. Wrote comprehensive test suite (`test_functional.cpp`) with 37 test cases BEFORE implementation
3. Implemented functional operations in `SequentialList.h` and `SequentialList.cpp`
4. Verified all 37 tests pass
5. Committed and pushed to GitHub

### Design Decisions

#### TDD Approach (Test-Driven Development)
- **Decision:** Write tests first, then implement to make them pass
- **Reasoning:** 
  - Tests serve as specification of desired API
  - Ensures code meets actual requirements
  - Catches edge cases early
  - Documents expected behavior
- **Alternative:** Implementation-first approach
- **Why TDD Won:** Assignment emphasizes documentation and process; TDD provides both

#### Return Type: VectorList (Immutable Pattern)
- **Decision:** Functional operations return NEW `VectorList<T>` or `VectorList<U>`
- **Reasoning:**
  - Immutability is core functional programming principle
  - Original list remains unchanged (no side effects)
  - Enables safe method chaining
  - Matches behavior of functional languages (Haskell, Scala)
- **Tradeoff:** More memory usage, but clearer semantics
- **Consequence:** Even `LinkedList.map()` returns `VectorList` (documented in tests)

#### Implementation Location
- **Decision:** Implement in base class `SequentialList<T>`
- **Reasoning:**
  - Operations only need `at(int)` and `size()` - already in SequentialList
  - Automatic inheritance by VectorList, LinkedList, and RestrictedSequentialList
  - Code reuse (DRY principle)
- **Note:** Used template implementation file `.cpp` included in `.h` header

### Test Coverage
Created 9 test suites with 37 total assertions:
1. **Map (same type)** - Transform int→int (squaring)
2. **Map (type change)** - Transform int→string  
3. **Filter** - Even numbers, threshold filtering
4. **Reduce** - Sum, product, max, conditional counting
5. **ForEach** - Side effects on external variables
6. **Method Chaining** - filter→map→reduce composition
7. **Edge Cases** - Empty lists, single elements, no matches
8. **LinkedList** - Verify inheritance works
9. **Real-World** - Student grade processing example

### GenAI Assistance Used

**Tool:** GitHub Copilot  
**Prompt 1:** "Create TDD test suite for functional operations on C++ list containers"

**Response:**
- Generated template test file structure with assert functions
- Suggested using ANSI color codes for output formatting
- Provided examples of lambda test cases

**What Was Incorporated:**
✅ Test structure with color-coded pass/fail  
✅ Comprehensive edge case testing  
✅ Real-world example pattern  

**Prompt 2:** "Implement map, filter, reduce for C++ template class using std::function"

**Response:**
- Showed template<typename T> template<typename U> syntax for nested templates
- Explained forward declaration for VectorList to break circular dependency
- Suggested including .cpp implementation in header for templates

**What Was Incorporated:**
✅ Nested template syntax for `map` and `reduce`  
✅ Forward declaration pattern  
✅ `.cpp` include strategy  

**What Was NOT Incorporated:**
❌ Suggested using `auto` return types (C++14) - stayed with explicit types for clarity
❌ Move semantics optimization - keeping simple for now

**Prompt 3:** "Fix compilation error: no viable conversion from VectorList to LinkedList"

**Response:**
- Identified that functional ops return VectorList, not original container type
- Suggested either:
  1. Change return type to be polymorphic (complex)
  2. Document that operations always return VectorList (simple)
- Explained tradeoff between purity and pragmatism

**Decision Made:**
✅ Document VectorList return type in tests  
✅ Add comment explaining design choice  

### Success/Failure Assessment

✅ **COMPLETE SUCCESS:**
- All 37 tests pass on first run after implementation
- Clean compilation with no warnings
- Method chaining works perfectly
- Both VectorList and LinkedList compatible

**Example Output:**
```
✓ PASS: Map preserves size
✓ PASS: Filter: 5 even numbers in 1-10  
✓ PASS: Chain: filter evens -> square -> sum = 220
✓ PASS: Real-world: average = 75.4
```

### Insights Gained

1. **TDD is powerful for API design:**
   - Writing tests first forced clear thinking about WHAT we want
   - Caught the VectorList return type issue early
   - Tests serve as live documentation

2. **Functional-OO synergy:**
   - OO hierarchy (SequentialList) provides WHAT operations exist
   - Functional lambdas let users specify WHAT transformation to apply
   - HOW is completely hidden in base class implementation

3. **Immutability simplifies reasoning:**
   - `numbers.filter(x > 0).map(x*2)` clearly creates new lists
   - No concerns about modifying shared state
   - Easier to test (no setup/teardown needed)

4. **Template metaprogramming challenges:**
   - Nested templates (`template<T> template<U>`) are tricky
   - Forward declarations needed to break circular dependencies
   - Implementation must be in header for template instantiation

### Open Questions RESOLVED

1. ~~Mutable vs Immutable?~~ → **RESOLVED: Immutable (returns new list)**
2. ~~Method chaining?~~ → **RESOLVED: Works via return values**
3. ~~Works with LinkedList?~~ → **RESOLVED: Yes, via inheritance**

### Next Steps
1. ✅ Commit functional operations
2. ✅ Push to GitHub
3. ⏭️ Implement file I/O module (Task 3)
4. ⏭️ Build keyword counter example (Task 4)

---

## Entry 4: [Next development session]
**Date:** [Timestamp]  
**Duration:** [Time spent]  
**Activity:** [What you're working on]

---

## Summary of GenAI Usage (Updated Continuously)

| Date | Tool | Purpose | Outcome |
|------|------|---------|---------|
| Nov 25 | GitHub Copilot | Project planning | ✅ Todo list created |
| Nov 25 | GitHub Copilot | Git cleanup | ✅ Removed ignored files |
| Nov 25 | GitHub Copilot | Functional interface design | ✅ Design document created |
| Nov 25 | GitHub Copilot | TDD test suite generation | ✅ 37-test suite created |
| Nov 25 | GitHub Copilot | Template implementation | ✅ All operations working |
| Nov 25 | GitHub Copilot | Compilation error resolution | ✅ VectorList return type clarified |

---

**Note:** This log will be updated chronologically as development progresses. Each significant decision, implementation, and assistance will be documented with timestamps.

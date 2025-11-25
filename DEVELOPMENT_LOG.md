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

## Entry 3: [To be filled as development progresses]
**Date:** [Timestamp]  
**Duration:** [Time spent]  
**Activity:** [What you're working on]

### Template for Future Entries
- Actions Taken
- Design Decisions (with reasoning and alternatives)
- GenAI Assistance Used (prompts, responses, interpretations)
- What Was Incorporated / Not Incorporated
- Success/Failure assessment
- Insights Gained
- Open Questions
- Next Steps

---

## Summary of GenAI Usage (Updated Continuously)

| Date | Tool | Purpose | Outcome |
|------|------|---------|---------|
| Nov 25 | GitHub Copilot | Project planning | ✅ Todo list created |
| Nov 25 | GitHub Copilot | Git cleanup | ✅ Removed ignored files |
| Nov 25 | GitHub Copilot | Functional interface design | ✅ Design document created |

---

**Note:** This log will be updated chronologically as development progresses. Each significant decision, implementation, and assistance will be documented with timestamps.

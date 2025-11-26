
# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

# Directories
CONTAINER_DIR = containers
TEST_DIR = tests
IO_DIR = io
ANALYSIS_DIR = analysis
OBJ_DIR = obj

# Source files
MAIN_SRCS = main.cpp
DEMO_SRCS = demo.cpp
IO_SRCS = $(wildcard $(IO_DIR)/*.cpp)
ANALYSIS_SRCS = $(wildcard $(ANALYSIS_DIR)/*.cpp)
COMMON_SRCS = $(IO_SRCS) $(ANALYSIS_SRCS)

# Test source files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
MAIN_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
DEMO_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(DEMO_SRCS))
COMMON_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(COMMON_SRCS))
TEST_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

# Executable names
MAIN_EXEC = main
DEMO_EXEC = demo
TEST_EXEC = run_tests

# Individual test executables
TEST_FUNCTIONAL = test_functional
TEST_FILEIO = test_fileio
TEST_TEXTANALYSIS = test_textanalysis

# Default target
all: $(DEMO_EXEC) $(MAIN_EXEC)

# Demo executable (interactive CLI)
$(DEMO_EXEC): $(DEMO_OBJS) $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "✓ Demo executable built successfully!"
	@echo "Run with: ./$(DEMO_EXEC)"

# Main executable (original demo)
$(MAIN_EXEC): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# All tests
tests: test_functional test_fileio test_textanalysis
	@echo ""
	@echo "========================================="
	@echo "  Running All Tests"
	@echo "========================================="
	@echo ""
	@./$(TEST_FUNCTIONAL)
	@./$(TEST_FILEIO)
	@./$(TEST_TEXTANALYSIS)
	@echo "✓ All test suites completed!"

# Individual test targets
test_functional: $(OBJ_DIR)/$(TEST_DIR)/test_functional.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_fileio: $(OBJ_DIR)/$(TEST_DIR)/test_fileio.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_textanalysis: $(OBJ_DIR)/$(TEST_DIR)/test_textanalysis.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run demo (build first if needed)
run_demo: $(DEMO_EXEC)
	@echo ""
	@echo "Starting interactive demo..."
	@echo ""
	@./$(DEMO_EXEC)

# Quick test target
quicktest: test_functional
	@./$(TEST_FUNCTIONAL)

# Bundle for submission
bundle: clean all tests
	@echo "Creating submission bundle..."
	@zip -r ListContainer_Submission.zip \
		*.cpp *.h *.md *.mp4 *.pdf Makefile \
		containers/ functional/ io/ analysis/ algorithms/ interface/ \
		test_data/ tests/ docs/ \
		-x "*.o" "*/.DS_Store" "*.zip"
	@echo "✓ Bundle created: ListContainer_Submission.zip"

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(MAIN_EXEC) $(DEMO_EXEC) $(TEST_EXEC)
	rm -f $(TEST_FUNCTIONAL) $(TEST_FILEIO) $(TEST_TEXTANALYSIS)
	@echo "✓ Clean complete"

# Help target
help:
	@echo "Available targets:"
	@echo "  make all          - Build demo and main executables"
	@echo "  make run_demo     - Build and run interactive demo"
	@echo "  make tests        - Run all test suites"
	@echo "  make quicktest    - Run functional tests only"
	@echo "  make bundle       - Create submission bundle"
	@echo "  make clean        - Remove build artifacts"
	@echo "  make help         - Show this help message"

.PHONY: all tests run_demo quicktest bundle clean help test_functional test_fileio test_textanalysis

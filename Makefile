
# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

# Directories
CONTAINER_DIR = containers
TEST_DIR = tests
OBJ_DIR = obj

# Source files
SRCS = main.cpp
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

# Executable names
EXEC = main
TEST_EXEC = run_tests

# Default target
all: $(EXEC)

# Main executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test executable
tests: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $^

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(EXEC) $(TEST_EXEC)

.PHONY: all tests clean

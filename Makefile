# Makefile for Stack ADT and String Reversal Project
# Author: Jaden Mardini
# Professional C project build configuration

# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror -O2 -g
CPPFLAGS = -Iinclude
LDFLAGS = 
LDLIBS = 

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
OBJ_DIR = obj
TEST_DIR = tests
DOC_DIR = docs

# Source files
DYNAMIC_STACK_SOURCES = $(SRC_DIR)/dynamic_stack/dynamic_stack.c $(SRC_DIR)/dynamic_stack/main.c
STATIC_STACK_SOURCES = $(SRC_DIR)/static_stack/static_stack.c $(SRC_DIR)/static_stack/main.c

# Object files
DYNAMIC_STACK_OBJECTS = $(OBJ_DIR)/dynamic_stack.o $(OBJ_DIR)/dynamic_main.o
STATIC_STACK_OBJECTS = $(OBJ_DIR)/static_stack.o $(OBJ_DIR)/static_main.o

# Test executable
TEST_EXEC = $(BIN_DIR)/test_stacks
TEST_OBJECTS = $(OBJ_DIR)/test_stacks.o $(OBJ_DIR)/dynamic_stack.o $(OBJ_DIR)/static_stack.o

# Default target
.PHONY: all
all: directories $(DYNAMIC_STACK_EXEC) $(STATIC_STACK_EXEC) $(TEST_EXEC)

# Create necessary directories
.PHONY: directories
directories:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR) $(TEST_DIR) $(DOC_DIR)

# Dynamic stack executable
$(DYNAMIC_STACK_EXEC): $(DYNAMIC_STACK_OBJECTS)
	@echo "Linking dynamic stack demo..."
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "Built: $@"

# Test executable
$(TEST_EXEC): $(TEST_OBJECTS)
	@echo "Linking unit tests..."
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "Built: $@"

# Static stack executable  
$(STATIC_STACK_EXEC): $(STATIC_STACK_OBJECTS)
	@echo "Linking string reversal demo..."
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@echo "Built: $@"

# Object file rules
$(OBJ_DIR)/dynamic_stack.o: $(SRC_DIR)/dynamic_stack/dynamic_stack.c $(INCLUDE_DIR)/dynamic_stack.h
	@echo "Compiling dynamic_stack.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/dynamic_main.o: $(SRC_DIR)/dynamic_stack/main.c $(INCLUDE_DIR)/dynamic_stack.h
	@echo "Compiling dynamic stack main.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/static_stack.o: $(SRC_DIR)/static_stack/static_stack.c $(INCLUDE_DIR)/static_stack.h
	@echo "Compiling static_stack.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/test_stacks.o: $(TEST_DIR)/test_stacks.c $(INCLUDE_DIR)/dynamic_stack.h $(INCLUDE_DIR)/static_stack.h
	@echo "Compiling test_stacks.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/static_main.o: $(SRC_DIR)/static_stack/main.c $(INCLUDE_DIR)/static_stack.h
	@echo "Compiling static stack main.c..."
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Individual targets
.PHONY: dynamic_stack
dynamic_stack: directories $(DYNAMIC_STACK_EXEC)

.PHONY: static_stack  
static_stack: directories $(STATIC_STACK_EXEC)

# Debug builds
.PHONY: debug
debug: CFLAGS += -DDEBUG -g3 -O0
debug: all

# Release builds
.PHONY: release
release: CFLAGS += -DNDEBUG -O3 -flto
release: LDFLAGS += -flto
release: all

# Static analysis
.PHONY: analyze
analyze:
	@echo "Running static analysis..."
	@if command -v cppcheck >/dev/null 2>&1; then \
		cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem $(SRC_DIR)/; \
	else \
		echo "cppcheck not found, skipping static analysis"; \
	fi

# Code formatting
.PHONY: format
format:
	@echo "Formatting code..."
	@if command -v clang-format >/dev/null 2>&1; then \
		find $(SRC_DIR) $(INCLUDE_DIR) -name "*.c" -o -name "*.h" | xargs clang-format -i; \
		echo "Code formatted successfully"; \
	else \
		echo "clang-format not found, skipping formatting"; \
	fi

# Memory check (requires valgrind)
.PHONY: memcheck
memcheck: all
	@echo "Running memory checks..."
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Testing dynamic stack demo:"; \
		echo "quit" | valgrind --leak-check=full --show-leak-kinds=all $(DYNAMIC_STACK_EXEC); \
		echo "Testing string reversal demo:"; \
		echo "quit" | valgrind --leak-check=full --show-leak-kinds=all $(STATIC_STACK_EXEC); \
	else \
		echo "valgrind not found, skipping memory checks"; \
	fi

# Run tests
.PHONY: test
test: directories $(TEST_EXEC)
	@echo "Running unit tests..."
	@$(TEST_EXEC)
	@echo ""
	@echo "Running integration tests..."
	@echo "Testing dynamic stack demo:"
	@echo "n" | $(DYNAMIC_STACK_EXEC)
	@echo ""
	@echo "Testing string reversal demo:"
	@echo "" | $(STATIC_STACK_EXEC)

# Install (copy to system directories)
.PHONY: install
install: all
	@echo "Installing executables..."
	@mkdir -p $(HOME)/bin
	cp $(DYNAMIC_STACK_EXEC) $(HOME)/bin/
	cp $(STATIC_STACK_EXEC) $(HOME)/bin/
	@echo "Installed to $(HOME)/bin/"

# Uninstall
.PHONY: uninstall
uninstall:
	@echo "Uninstalling executables..."
	rm -f $(HOME)/bin/dynamic_stack_demo
	rm -f $(HOME)/bin/string_reversal_demo
	@echo "Uninstalled from $(HOME)/bin/"

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BIN_DIR) $(OBJ_DIR)
	@echo "Clean complete"

# Deep clean (including generated files)
.PHONY: distclean
distclean: clean
	@echo "Deep cleaning..."
	rm -rf $(DOC_DIR)/*.html $(DOC_DIR)/*.pdf
	@echo "Deep clean complete"

# Show help
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  all          - Build all executables (default)"
	@echo "  dynamic_stack - Build dynamic stack demo only"
	@echo "  static_stack  - Build string reversal demo only"
	@echo "  debug        - Build with debug flags"
	@echo "  release      - Build optimized release version"
	@echo "  analyze      - Run static code analysis"
	@echo "  format       - Format source code"
	@echo "  memcheck     - Run memory leak detection"
	@echo "  test         - Run basic functionality tests"
	@echo "  install      - Install executables to ~/bin"
	@echo "  uninstall    - Remove installed executables"
	@echo "  clean        - Remove build artifacts"
	@echo "  distclean    - Remove all generated files"
	@echo "  help         - Show this help message"

# Show project information
.PHONY: info
info:
	@echo "=== Stack ADT Project Information ==="
	@echo "Author: Jaden Mardini"
	@echo "Language: C (C11 standard)"
	@echo "Compiler: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Source directory: $(SRC_DIR)"
	@echo "Include directory: $(INCLUDE_DIR)"
	@echo "Binary directory: $(BIN_DIR)"
	@echo "Object directory: $(OBJ_DIR)"
	@echo ""
	@echo "Executables:"
	@echo "  $(DYNAMIC_STACK_EXEC) - Dynamic stack demonstration"
	@echo "  $(STATIC_STACK_EXEC) - String reversal demonstration"

# Prevent make from deleting intermediate files
.PRECIOUS: $(OBJ_DIR)/%.o

# Declare phony targets
.PHONY: all directories dynamic_stack static_stack debug release analyze format memcheck test install uninstall clean distclean help info

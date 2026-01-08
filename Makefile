# Riau Programming Language Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
DEBUG_FLAGS = -g -DDEBUG_TRACE_EXECUTION
INCLUDES = -Iengine
LIBS = -lm

# Directories
SRC_DIR = engine
BUILD_DIR = build
BIN_DIR = bin

# Source files
LEXER_SRC = $(SRC_DIR)/lexer/lexer.c
PARSER_SRC = $(SRC_DIR)/parser/parser.c
AST_SRC = $(SRC_DIR)/ast/ast.c
SEMANTIC_SRC = $(SRC_DIR)/semantic/semantic.c
BYTECODE_SRC = $(SRC_DIR)/bytecode/bytecode.c
COMPILER_SRC = $(SRC_DIR)/bytecode/compiler.c
VM_SRC = $(SRC_DIR)/vm/vm.c
ERROR_SRC = $(SRC_DIR)/errors/error_reporter.c
CLI_SRC = $(SRC_DIR)/cli/main.c

ALL_SRC = $(LEXER_SRC) $(PARSER_SRC) $(AST_SRC) $(SEMANTIC_SRC) $(BYTECODE_SRC) $(COMPILER_SRC) $(VM_SRC) $(ERROR_SRC) $(CLI_SRC)

# Object files
LEXER_OBJ = $(BUILD_DIR)/lexer.o
PARSER_OBJ = $(BUILD_DIR)/parser.o
AST_OBJ = $(BUILD_DIR)/ast.o
SEMANTIC_OBJ = $(BUILD_DIR)/semantic.o
BYTECODE_OBJ = $(BUILD_DIR)/bytecode.o
COMPILER_OBJ = $(BUILD_DIR)/compiler.o
VM_OBJ = $(BUILD_DIR)/vm.o
ERROR_OBJ = $(BUILD_DIR)/error_reporter.o
CLI_OBJ = $(BUILD_DIR)/main.o

ALL_OBJ = $(LEXER_OBJ) $(PARSER_OBJ) $(AST_OBJ) $(SEMANTIC_OBJ) $(BYTECODE_OBJ) $(COMPILER_OBJ) $(VM_OBJ) $(ERROR_OBJ) $(CLI_OBJ)

# Target executable
TARGET = $(BIN_DIR)/riau.exe

# Default target
all: directories $(TARGET)

# Create directories
directories:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"

# Link
$(TARGET): $(ALL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo Build complete: $(TARGET)

# Compile
$(BUILD_DIR)/lexer.o: $(LEXER_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/parser.o: $(PARSER_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/ast.o: $(AST_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/semantic.o: $(SEMANTIC_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/bytecode.o: $(BYTECODE_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/compiler.o: $(COMPILER_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/vm.o: $(VM_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/error_reporter.o: $(ERROR_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/main.o: $(CLI_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Clean
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"
	@if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"
	@echo Clean complete

# Run
run: all
	$(TARGET)

# Test
test: all
	@echo Running tests...
	$(TARGET) examples/hello.riau
	$(TARGET) examples/arithmetic.riau
	@echo All tests passed!

.PHONY: all directories clean debug run test

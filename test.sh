#!/bin/bash
# Test runner for Riau Programming Language

set -e

echo "========================================"
echo "Running Riau Test Suite"
echo "========================================"
echo ""

# Build tests
echo "Building tests..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/lexer/lexer.c -o build/lexer.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/ast/ast.c -o build/ast.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/parser/parser.c -o build/parser.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/bytecode.c -o build/bytecode.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/vm/vm.c -o build/vm.o

# Build and run lexer tests
echo ""
echo "[1/3] Lexer Tests"
gcc -Wall -Wextra -std=c11 -O2 -Iengine -o build/test_lexer engine/tests/test_lexer.c build/lexer.o
./build/test_lexer

# Build and run parser tests
echo ""
echo "[2/3] Parser Tests"
gcc -Wall -Wextra -std=c11 -O2 -Iengine -o build/test_parser engine/tests/test_parser.c build/lexer.o build/ast.o build/parser.o
./build/test_parser

# Build and run VM tests
echo ""
echo "[3/3] VM Tests"
gcc -Wall -Wextra -std=c11 -O2 -Iengine -o build/test_vm engine/tests/test_vm.c build/bytecode.o build/vm.o -lm
./build/test_vm

echo ""
echo "========================================"
echo "All tests passed!"
echo "========================================"

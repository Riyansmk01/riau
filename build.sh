#!/bin/bash
# Updated build script for Riau Programming Language

set -e

echo "Building Riau Programming Language..."

# Create directories
mkdir -p build bin

# Compile source files
echo "Compiling lexer..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/lexer/lexer.c -o build/lexer.o

echo "Compiling AST..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/ast/ast.c -o build/ast.o

echo "Compiling parser..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/parser/parser.c -o build/parser.o

echo "Compiling semantic analyzer..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/semantic/semantic.c -o build/semantic.o

echo "Compiling bytecode..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/bytecode.c -o build/bytecode.o

echo "Compiling compiler..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/compiler.c -o build/compiler.o

echo "Compiling VM..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/vm/vm.c -o build/vm.o

echo "Compiling CLI..."
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/cli/main.c -o build/main.o

# Link
echo "Linking..."
gcc -Wall -Wextra -std=c11 -O2 -o bin/riau build/lexer.o build/ast.o build/parser.o build/semantic.o build/bytecode.o build/compiler.o build/vm.o build/main.o -lm

# Make executable
chmod +x bin/riau

echo ""
echo "========================================"
echo "Build successful!"
echo "========================================"
echo ""
echo "Run REPL: ./bin/riau"
echo "Run file: ./bin/riau examples/hello.riau"
echo "Run tests: ./bin/riau examples/arithmetic.riau"
echo ""

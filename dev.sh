#!/bin/bash
# Development helper script for Riau

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Functions
print_header() {
    echo -e "${GREEN}========================================${NC}"
    echo -e "${GREEN}  $1${NC}"
    echo -e "${GREEN}========================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓${NC} $1"
}

print_error() {
    echo -e "${RED}✗${NC} $1"
}

print_info() {
    echo -e "${YELLOW}ℹ${NC} $1"
}

# Commands
cmd_clean() {
    print_header "Cleaning build artifacts"
    rm -rf build/ bin/
    print_success "Clean complete"
}

cmd_build() {
    print_header "Building Riau"
    chmod +x build.sh
    ./build.sh
    print_success "Build complete"
}

cmd_test() {
    print_header "Running tests"
    chmod +x test.sh
    ./test.sh
    print_success "Tests complete"
}

cmd_rebuild() {
    cmd_clean
    cmd_build
}

cmd_dev() {
    print_header "Development mode"
    cmd_rebuild
    cmd_test
    print_success "Ready for development!"
}

cmd_repl() {
    print_header "Starting REPL"
    if [ ! -f "bin/riau" ]; then
        print_error "Binary not found. Building first..."
        cmd_build
    fi
    ./bin/riau
}

cmd_run() {
    if [ -z "$1" ]; then
        print_error "Usage: ./dev.sh run <file.riau>"
        exit 1
    fi
    
    if [ ! -f "bin/riau" ]; then
        print_error "Binary not found. Building first..."
        cmd_build
    fi
    
    print_header "Running $1"
    ./bin/riau "$1"
}

cmd_examples() {
    print_header "Running all examples"
    
    if [ ! -f "bin/riau" ]; then
        print_error "Binary not found. Building first..."
        cmd_build
    fi
    
    for file in examples/*.riau; do
        if [ -f "$file" ]; then
            echo ""
            print_info "Running: $file"
            ./bin/riau "$file" || print_error "Failed: $file"
        fi
    done
    
    print_success "All examples complete"
}

cmd_help() {
    echo "Riau Development Helper"
    echo ""
    echo "Usage: ./dev.sh <command>"
    echo ""
    echo "Commands:"
    echo "  clean      - Clean build artifacts"
    echo "  build      - Build Riau"
    echo "  test       - Run tests"
    echo "  rebuild    - Clean and build"
    echo "  dev        - Full development cycle (clean, build, test)"
    echo "  repl       - Start REPL"
    echo "  run <file> - Run a .riau file"
    echo "  examples   - Run all example files"
    echo "  help       - Show this help"
}

# Main
case "$1" in
    clean)
        cmd_clean
        ;;
    build)
        cmd_build
        ;;
    test)
        cmd_test
        ;;
    rebuild)
        cmd_rebuild
        ;;
    dev)
        cmd_dev
        ;;
    repl)
        cmd_repl
        ;;
    run)
        cmd_run "$2"
        ;;
    examples)
        cmd_examples
        ;;
    help|"")
        cmd_help
        ;;
    *)
        print_error "Unknown command: $1"
        cmd_help
        exit 1
        ;;
esac

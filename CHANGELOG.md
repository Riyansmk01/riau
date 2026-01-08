# Changelog

All notable changes to Riau Programming Language will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added (Planned for v0.2.0)

**Developer Experience**
- ✅ Shebang support (`#!/usr/bin/env riau`) - Execute `.riau` files directly on Unix systems
- ✅ VS Code extension for `.riau` file association and syntax highlighting
  - File recognition for `.riau` files
  - Syntax highlighting (keywords, operators, built-in functions)
  - Auto-closing brackets and quotes
  - Comment support
  - Code folding

**Planned Features**
- POST data handling
- JSON parsing (`json_encode()`, `json_decode()`)
- Cookie & session support
- FastCGI server (`riau-fpm`)

---

## [0.1.1] - 2026-01-08

### Added

**Enhanced Error Reporting System**
- Code context display with line numbers and syntax highlighting
- "Did you mean?" suggestions using Levenshtein distance algorithm (max distance: 3)
- Context-aware helpful hints for common errors
- Color-coded terminal output (red/yellow/green/cyan)
- Visual error pointers showing exact error location (^~~~)
- Error recovery for multiple error reporting

**Performance & Benchmarking Tools**
- `tools/benchmark.riau` - Comprehensive performance testing suite
  - Arithmetic operations (10,000 iterations)
  - String operations (1,000 iterations)
  - Array operations (1,000 iterations)
  - Function calls (Fibonacci recursion)
  - Math operations (1,000 iterations)
- `tools/error_examples.riau` - Error message demonstrations (10 error types)

**Developer Tooling**
- `dev.sh` and `dev.bat` - Development helper scripts with 8 commands
  - `clean`, `build`, `test`, `rebuild`, `dev`, `repl`, `run`, `examples`
- `.editorconfig` - Consistent code formatting across editors
- GitHub Actions CI/CD for multi-platform builds (Linux, macOS, Windows)
- Enhanced `.gitignore` with 40+ patterns

**Documentation**
- `docs/PERFORMANCE.md` - Performance optimization guide (200+ lines)
- `docs/ERROR_HANDLING.md` - Comprehensive error handling guide (300+ lines)
- `docs/API_REFERENCE.md` - Complete API documentation (600+ lines)
- `CONTRIBUTING.md` - Contribution guidelines with code style and PR process
- Professional README badges (version, license, platform, PHP compatibility, build status)

### Changed

- **README.md**: Added professional badges, enhanced features section, new development tools section
- **Build System**: Updated Makefile, build.bat, and build.ps1 to include error reporter compilation
- **Error Messages**: Improved from basic line numbers to full context with suggestions

### Stability

- ✅ **Backward compatibility guaranteed** within 0.1.x minor versions
- ✅ **Deterministic VM execution** - Same bytecode always produces same results
- ✅ **Built-in Functions API** - Stable API, no breaking changes in 0.1.x
- ✅ **Semantic versioning** - Following semver strictly

### Security

- ✅ **Built-in null safety** - Prevents null pointer errors at compile time
- ✅ **Type checking** - Static type analysis prevents type-related bugs
- ✅ **Automatic garbage collection** - No manual memory management required
- ✅ **No unsafe pointer access** - Memory-safe by design
- ✅ **No buffer overflows** - Bounds checking on all array operations
- 🔄 **Sandboxed execution** (planned for v0.3.0)

### Performance

- Bytecode compilation for faster execution vs interpretation
- Reference counting garbage collection with minimal overhead
- Optimized string operations
- Efficient stack-based VM

---
- POST data handling
- Cookie support
- Session management
- JSON parsing (`json_encode()`, `json_decode()`)
- String manipulation functions (`str_split()`, `str_replace()`, `str_trim()`)
- Query string parser

### Planned for v0.3.0
- Database drivers (MySQL, PostgreSQL, SQLite)
- File I/O operations (`file_read()`, `file_write()`)
- Template engine
- WebSocket support

### Planned for v1.0.0
- JIT compilation
- Package manager
- Debugger
- Performance optimizations
- Production case studies

## [0.1.0] - 2026-01-08

### Added
- **Core Language Features**
  - Lexer with 50+ token types
  - Recursive descent parser
  - Abstract Syntax Tree (25+ node types)
  - Semantic analyzer with type checking
  - Null safety validation
  - Bytecode compiler
  - Stack-based Virtual Machine (50+ opcodes)
  - Garbage collection (reference counting)

- **Data Types** (7 types)
  - `null` - Null value
  - `bool` - Boolean (true/false)
  - `number` - Double-precision floating point
  - `string` - UTF-8 strings
  - `array` - Dynamic arrays
  - `object` - Key-value objects
  - `function` - First-class functions

- **Built-in Functions** (16 functions)
  - Output: `print()`, `log()`
  - Environment: `env()`
  - Type: `type_of()`, `len()`
  - String: `str_concat()`, `str_length()`, `str_upper()`, `str_lower()`
  - Array: `array_push()`, `array_pop()`, `array_length()`
  - Math: `math_abs()`, `math_floor()`, `math_ceil()`, `math_round()`

- **Operators** (15+ operators)
  - Arithmetic: `+`, `-`, `*`, `/`, `%`
  - Comparison: `==`, `!=`, `<`, `<=`, `>`, `>=`
  - Logical: `&&`, `||`, `!`
  - Assignment: `=`

- **Control Flow**
  - Conditionals: `if`, `else`
  - Loops: `for...in`, `while`
  - Functions: Normal & arrow functions
  - Return statements

- **Web Development (CGI)**
  - Full CGI compatibility
  - HTTP header output via `print()`
  - Environment variable access via `env()`
  - Dynamic HTML generation
  - GET request handling (QUERY_STRING)
  - Support for 15+ CGI environment variables
  - Nginx/Apache integration ready

- **Tools & Infrastructure**
  - Command-line interface (CLI)
  - Interactive REPL mode
  - File execution (.riau files)
  - Clear error reporting with line numbers
  - Cross-platform build system (Windows/Linux/macOS)
  - Automated test suite

- **Documentation**
  - Comprehensive README.md (1,293 lines)
  - PHP comparison guide (60% compatibility)
  - Complete built-in functions documentation
  - 11+ example programs
  - Installation guides for all platforms
  - Web server setup guides (Nginx/Apache)
  - Troubleshooting section

- **Example Programs**
  - `hello.riau` - Hello world
  - `arithmetic.riau` - Math operations
  - `variables.riau` - Variable declarations
  - `functions.riau` - Function examples
  - `web_hello.riau` - Web hello world
  - `web_form.riau` - Form handling
  - `comprehensive_test.riau` - Full feature test
  - And more...

### Changed
- N/A (initial release)

### Deprecated
- N/A (initial release)

### Removed
- N/A (initial release)

### Fixed
- N/A (initial release)

### Security
- Built-in null safety to prevent null pointer errors
- Type checking to prevent type-related bugs
- Safe memory management with garbage collection

## [0.0.1] - 2026-01-01

### Added
- Initial project structure
- Basic lexer implementation
- Basic parser implementation
- Proof of concept

---

## Version Comparison

| Version | Release Date | Features | PHP Compatibility |
|---------|--------------|----------|-------------------|
| 0.1.0   | 2026-01-08   | 16 built-in functions, CGI support | 60% |
| 0.2.0   | TBD          | +POST, JSON, Sessions | 70% |
| 0.3.0   | TBD          | +Database, File I/O | 80% |
| 1.0.0   | TBD          | +JIT, Package Manager | 90% |

---

**Legend**:
- `Added`: New features
- `Changed`: Changes in existing functionality
- `Deprecated`: Soon-to-be removed features
- `Removed`: Removed features
- `Fixed`: Bug fixes
- `Security`: Security improvements

For more details, see [README.md](README.md)

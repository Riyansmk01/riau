# Contributing to Riau Programming Language

Terima kasih atas minat Anda untuk berkontribusi ke Riau! 🎉

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Development Setup](#development-setup)
- [Coding Guidelines](#coding-guidelines)
- [Commit Guidelines](#commit-guidelines)
- [Pull Request Process](#pull-request-process)

## 🤝 Code of Conduct

Proyek ini mengikuti prinsip:
- **Respect**: Hormati semua kontributor
- **Collaboration**: Bekerja sama dengan baik
- **Quality**: Prioritaskan kualitas code
- **Learning**: Bantu orang lain belajar

## 🚀 How Can I Contribute?

### 1. Reporting Bugs

Jika menemukan bug, buat issue dengan informasi:
- **Versi Riau**: Output dari `.\bin\riau.exe --version`
- **OS & Compiler**: OS version dan `gcc --version`
- **Code**: Code yang menyebabkan error
- **Error Message**: Error message lengkap
- **Expected vs Actual**: Apa yang diharapkan vs yang terjadi

### 2. Suggesting Features

Untuk suggest fitur baru:
- Cek roadmap di README.md
- Jelaskan use case yang jelas
- Berikan contoh syntax yang diinginkan
- Diskusikan di issues terlebih dahulu

### 3. Writing Code

Kontribusi code sangat diterima untuk:
- Bug fixes
- New features dari roadmap
- Performance improvements
- Documentation improvements
- Test coverage

## 💻 Development Setup

### Prerequisites

```bash
# Windows
- MinGW-w64 atau MSYS2
- GCC 8.0+
- Git

# Linux
- build-essential
- GCC 8.0+
- Git

# macOS
- Xcode Command Line Tools
- GCC 8.0+
- Git
```

### Setup Steps

```bash
# 1. Fork repository
# 2. Clone fork Anda
git clone https://github.com/YOUR_USERNAME/riau.git
cd riau

# 3. Build project
.\build.bat  # Windows
./build.sh   # Linux/macOS

# 4. Run tests
.\test.bat   # Windows
./test.sh    # Linux/macOS

# 5. Test REPL
.\bin\riau.exe
```

## 📝 Coding Guidelines

### C Code Style

```c
// ✅ Good
void function_name(int param) {
    if (condition) {
        do_something();
    }
}

// ❌ Bad
void functionName(int param){
    if(condition){
        do_something();
    }
}
```

**Rules**:
- Use `snake_case` for functions and variables
- Use `PascalCase` for structs and types
- Indent with 4 spaces (no tabs)
- Max line length: 100 characters
- Always use braces for if/while/for
- Add comments for complex logic

### Riau Code Style

```riau
// ✅ Good
fn calculate_total(price, quantity) {
    return price * quantity
}

let total = calculate_total(100, 5)
print("Total: " + total)

// ❌ Bad
fn calculateTotal(price,quantity){return price*quantity}
let total=calculateTotal(100,5)
print("Total: "+total)
```

**Rules**:
- Use `snake_case` for variables and functions
- Add spaces around operators
- One statement per line
- Clear variable names

## 📦 Commit Guidelines

### Commit Message Format

```
<type>(<scope>): <subject>

<body>

<footer>
```

### Types

- **feat**: New feature
- **fix**: Bug fix
- **docs**: Documentation changes
- **style**: Code style changes (formatting)
- **refactor**: Code refactoring
- **test**: Adding tests
- **chore**: Build/tooling changes

### Examples

```bash
# Good commits
feat(vm): add support for while loops
fix(lexer): handle escape sequences in strings
docs(readme): update installation instructions
test(parser): add tests for function declarations

# Bad commits
update stuff
fixed bug
changes
```

## 🔄 Pull Request Process

### Before Submitting

1. **Update from main**:
   ```bash
   git checkout main
   git pull upstream main
   git checkout your-branch
   git rebase main
   ```

2. **Run tests**:
   ```bash
   .\test.bat  # Windows
   ./test.sh   # Linux/macOS
   ```

3. **Build successfully**:
   ```bash
   .\build.bat  # Windows
   ./build.sh   # Linux/macOS
   ```

4. **Update documentation** if needed

### PR Checklist

- [ ] Code follows style guidelines
- [ ] All tests pass
- [ ] Added tests for new features
- [ ] Updated documentation
- [ ] Commit messages follow guidelines
- [ ] No merge conflicts
- [ ] Builds successfully on all platforms

### PR Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
How was this tested?

## Checklist
- [ ] Tests pass
- [ ] Documentation updated
- [ ] Code follows style guide
```

## 🎯 Areas Needing Help

### High Priority
- [ ] POST data handling (v0.2.0)
- [ ] JSON parsing (v0.2.0)
- [ ] String manipulation functions (v0.2.0)
- [ ] Database drivers (v0.3.0)
- [ ] File I/O operations (v0.3.0)

### Medium Priority
- [ ] More test coverage
- [ ] Performance optimizations
- [ ] Error message improvements
- [ ] More example programs
- [ ] Tutorial documentation

### Low Priority
- [ ] IDE plugins (VS Code, Vim)
- [ ] Syntax highlighting
- [ ] Package manager design
- [ ] Debugger protocol

## 📚 Resources

- **README.md**: Main documentation
- **examples/**: Example programs
- **engine/**: Core implementation
- **docs/**: Additional documentation

## 🙏 Recognition

All contributors will be:
- Listed in CONTRIBUTORS.md
- Mentioned in release notes
- Part of the Riau community!

## ❓ Questions?

- Open an issue for questions
- Tag with `question` label
- We're happy to help!

---

**Happy Coding!** 🚀

Thank you for contributing to Riau Programming Language!

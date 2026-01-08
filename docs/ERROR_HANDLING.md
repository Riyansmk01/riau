# Error Handling Guide

## Overview

Riau provides helpful error messages with context, suggestions, and hints to help you fix issues quickly.

## Error Message Format

```
Error at filename.riau:5:12
  let email = usrname + "@example.com"
              ^^^^^^^
Undefined variable 'usrname'

💡 Did you mean 'username'?

Hint: Make sure the variable is declared before use with 'let'
```

### Components

1. **Location**: File, line, and column number
2. **Code Context**: The actual line with error
3. **Error Pointer**: Visual indicator (^) showing exact location
4. **Error Message**: Clear description of the problem
5. **Suggestion**: "Did you mean?" for typos
6. **Hint**: Helpful advice for fixing the error

## Common Errors

### 1. Undefined Variable

**Error**:
```
Error at test.riau:3:15
  let email = usrname + "@example.com"
              ^^^^^^^
Undefined variable 'usrname'

💡 Did you mean 'username'?

Hint: Make sure the variable is declared before use with 'let'
```

**Fix**:
```riau
let username = "john"  // Declare first
let email = username + "@example.com"  // Then use
```

### 2. Type Mismatch

**Error**:
```
Error at test.riau:4:10
  let result = number + text
               ^^^^^^
Type mismatch: cannot add 'number' and 'string'

Hint: Ensure the types match or add explicit type conversion
```

**Fix**:
```riau
// Option 1: Convert to same type
let result = str(number) + text

// Option 2: Use correct types
let result = number1 + number2
```

### 3. Null Safety Violation

**Error**:
```
Error at test.riau:5:7
  print(user.name)
        ^^^^
Variable 'user' may be null

Hint: Use null safety operator '?' or check for null before accessing
```

**Fix**:
```riau
// Option 1: Null check
let user? = findUser(id)
if user {
    print(user.name)  // Safe
}

// Option 2: Default value
let name = user?.name ?? "Unknown"
```

### 4. Already Defined

**Error**:
```
Error at test.riau:7:5
  let count = 20
      ^^^^^
Variable 'count' already defined

Hint: Variable names must be unique within the same scope
```

**Fix**:
```riau
let count = 10
// Use different name or reassign
count = 20  // Reassignment (when supported)
// or
let newCount = 20
```

### 5. Syntax Errors

**Error**:
```
Error at test.riau:8:20
  let value = (10 + 20
                      ^
Expected ')' after expression

Hint: Check for missing semicolons, brackets, or parentheses
```

**Fix**:
```riau
let value = (10 + 20)  // Add closing parenthesis
```

### 6. Undefined Function

**Error**:
```
Error at test.riau:10:14
  let result = calculate_sum(10, 20)
               ^^^^^^^^^^^^^
Undefined function 'calculate_sum'

Hint: Check if the function is defined or imported
```

**Fix**:
```riau
// Define function first
fn calculate_sum(a, b) {
    return a + b
}

let result = calculate_sum(10, 20)
```

## Error Levels

### 🔴 Error
Critical issues that prevent code execution:
- Undefined variables
- Type mismatches
- Syntax errors

### 🟡 Warning
Potential issues that may cause problems:
- Unused variables
- Deprecated features
- Performance concerns

### 🟢 Hint
Helpful suggestions for improvement:
- Best practices
- Alternative approaches
- Optimization tips

## "Did You Mean?" Suggestions

Riau uses Levenshtein distance to suggest similar names:

```riau
let firstName = "John"
let lastName = "Doe"

// Typo: first_name vs firstName
let fullName = first_name + " " + lastName
```

**Error with Suggestion**:
```
Error at test.riau:5:16
  let fullName = first_name + " " + lastName
                 ^^^^^^^^^^
Undefined variable 'first_name'

💡 Did you mean 'firstName'?
```

### How It Works

1. **Calculates similarity** between typo and all variables
2. **Suggests closest match** if distance ≤ 3 characters
3. **Shows suggestion** in green for easy visibility

## Color-Coded Output

When terminal supports colors:
- 🔴 **Red**: Errors and error pointers
- 🟡 **Yellow**: Warnings and hints
- 🟢 **Green**: Suggestions and success
- 🔵 **Cyan**: Code context and line numbers
- **Bold**: Important information

## Debugging Tips

### 1. Read Error Messages Carefully

Error messages include:
- Exact location (line:column)
- Code context
- Clear explanation
- Helpful suggestions

### 2. Check Suggestions First

If you see "Did you mean?", it's usually a typo:
```
💡 Did you mean 'username'?
```

### 3. Follow Hints

Hints provide actionable advice:
```
Hint: Make sure the variable is declared before use with 'let'
```

### 4. Use REPL for Testing

Test small code snippets in REPL:
```bash
.\bin\riau.exe
> let x = 10
> print(x)
10
```

### 5. Enable Verbose Mode

For detailed error information:
```bash
.\bin\riau.exe --verbose script.riau
```

## Best Practices

### ✅ DO: Declare Before Use

```riau
let username = "john"  // Declare
print(username)        // Use
```

### ✅ DO: Use Descriptive Names

```riau
let userEmail = "john@example.com"  // Clear
// Not: let e = "john@example.com"  // Unclear
```

### ✅ DO: Handle Null Values

```riau
let user? = findUser(id)
if user {
    print(user.name)
}
```

### ❌ DON'T: Ignore Error Messages

Read the full error message, including hints and suggestions.

### ❌ DON'T: Use Similar Variable Names

```riau
// Confusing
let userName = "john"
let user_name = "doe"
let username = "smith"
```

## Error Recovery

Riau attempts to recover from errors and continue parsing:

```riau
let x = 10
let y = undefined_var  // Error here
let z = 20             // Still parsed
```

This helps identify multiple errors in one run.

## Getting Help

If error messages are unclear:

1. **Check documentation**: `docs/` folder
2. **Read examples**: `examples/` folder
3. **Open an issue**: Report unclear errors
4. **Ask community**: Discussions tab

---

**Remember**: Good error messages save debugging time. Riau is designed to help you fix issues quickly!

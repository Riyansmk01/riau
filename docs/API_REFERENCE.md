# Riau Programming Language - API Reference

## Table of Contents

1. [Built-in Functions](#built-in-functions)
2. [Data Types](#data-types)
3. [Operators](#operators)
4. [Keywords](#keywords)
5. [CGI Environment Variables](#cgi-environment-variables)

---

## Built-in Functions

### Output Functions

#### `print(value)`
Output value to stdout.

**Signature**: `print(value: any) -> null`

**Parameters**:
- `value` (any): Value to print

**Returns**: `null`

**Example**:
```riau
print("Hello World")
print(123)
print(true)
```

#### `log(value)`
Output value with `[LOG]` prefix for debugging.

**Signature**: `log(value: any) -> null`

**Parameters**:
- `value` (any): Value to log

**Returns**: `null`

**Example**:
```riau
log("Debug message")
log(variable)
```

---

### Environment Functions

#### `env(name)`
Read environment variable.

**Signature**: `env(name: string) -> string | null`

**Parameters**:
- `name` (string): Environment variable name

**Returns**: String value or `null` if not found

**Example**:
```riau
let method = env("REQUEST_METHOD")
let user = env("USERNAME")
```

---

### Type Functions

#### `type_of(value)`
Get the type of a value.

**Signature**: `type_of(value: any) -> string`

**Parameters**:
- `value` (any): Value to check

**Returns**: Type name as string (`"null"`, `"bool"`, `"number"`, `"string"`, `"array"`, `"object"`, `"function"`)

**Example**:
```riau
type_of("hello")  // "string"
type_of(123)      // "number"
type_of(true)     // "bool"
```

#### `len(value)`
Get length of string or array.

**Signature**: `len(value: string | array) -> number`

**Parameters**:
- `value` (string | array): String or array

**Returns**: Length as number, or `-1` if invalid type

**Example**:
```riau
len("hello")      // 5
len([1, 2, 3])    // 3
```

---

### String Functions

#### `str_concat(...strings)`
Concatenate multiple strings.

**Signature**: `str_concat(...strings: string) -> string`

**Parameters**:
- `...strings` (string): Strings to concatenate

**Returns**: Concatenated string

**Example**:
```riau
str_concat("Hello", " ", "World")  // "Hello World"
```

#### `str_length(str)`
Get string length (alias of `len()`).

**Signature**: `str_length(str: string) -> number`

**Parameters**:
- `str` (string): Input string

**Returns**: Length as number

**Example**:
```riau
str_length("Riau")  // 4
```

#### `str_upper(str)`
Convert string to uppercase.

**Signature**: `str_upper(str: string) -> string`

**Parameters**:
- `str` (string): Input string

**Returns**: Uppercase string

**Example**:
```riau
str_upper("hello")  // "HELLO"
```

#### `str_lower(str)`
Convert string to lowercase.

**Signature**: `str_lower(str: string) -> string`

**Parameters**:
- `str` (string): Input string

**Returns**: Lowercase string

**Example**:
```riau
str_lower("HELLO")  // "hello"
```

---

### Array Functions

#### `array_push(array, value)`
Add element to end of array.

**Signature**: `array_push(array: array, value: any) -> array`

**Parameters**:
- `array` (array): Target array
- `value` (any): Value to add

**Returns**: Modified array

**Example**:
```riau
let arr = [1, 2, 3]
array_push(arr, 4)  // [1, 2, 3, 4]
```

#### `array_pop(array)`
Remove and return last element.

**Signature**: `array_pop(array: array) -> any`

**Parameters**:
- `array` (array): Target array

**Returns**: Last element, or `null` if empty

**Example**:
```riau
let arr = [1, 2, 3]
array_pop(arr)  // 3
// arr is now [1, 2]
```

#### `array_length(array)`
Get array length (alias of `len()`).

**Signature**: `array_length(array: array) -> number`

**Parameters**:
- `array` (array): Input array

**Returns**: Length as number

**Example**:
```riau
array_length([1, 2, 3])  // 3
```

---

### Math Functions

#### `math_abs(number)`
Get absolute value.

**Signature**: `math_abs(number: number) -> number`

**Parameters**:
- `number` (number): Input number

**Returns**: Absolute value

**Example**:
```riau
math_abs(-10)   // 10
math_abs(5)     // 5
```

#### `math_floor(number)`
Round down to nearest integer.

**Signature**: `math_floor(number: number) -> number`

**Parameters**:
- `number` (number): Input number

**Returns**: Floored value

**Example**:
```riau
math_floor(3.7)   // 3
math_floor(-2.5)  // -3
```

#### `math_ceil(number)`
Round up to nearest integer.

**Signature**: `math_ceil(number: number) -> number`

**Parameters**:
- `number` (number): Input number

**Returns**: Ceiled value

**Example**:
```riau
math_ceil(3.2)   // 4
math_ceil(-2.5)  // -2
```

#### `math_round(number)`
Round to nearest integer.

**Signature**: `math_round(number: number) -> number`

**Parameters**:
- `number` (number): Input number

**Returns**: Rounded value

**Example**:
```riau
math_round(3.5)  // 4
math_round(3.2)  // 3
```

---

## Data Types

### null
Represents absence of value.

```riau
let value = null
```

### bool
Boolean value (`true` or `false`).

```riau
let active = true
let disabled = false
```

### number
Double-precision floating point number.

```riau
let integer = 42
let decimal = 3.14
let negative = -10
```

### string
UTF-8 text string.

```riau
let name = "Riau"
let message = "Hello World"
```

### array
Ordered collection of values.

```riau
let numbers = [1, 2, 3, 4, 5]
let mixed = [1, "two", true, null]
```

### object
Key-value pairs (dictionary/map).

```riau
let user = {
  name: "John",
  age: 25,
  active: true
}
```

### function
First-class function.

```riau
fn add(a, b) {
  return a + b
}

let multiply = fn(a, b) => a * b
```

---

## Operators

### Arithmetic Operators

| Operator | Description | Example |
|----------|-------------|---------|
| `+` | Addition | `5 + 3` → `8` |
| `-` | Subtraction | `5 - 3` → `2` |
| `*` | Multiplication | `5 * 3` → `15` |
| `/` | Division | `6 / 3` → `2` |
| `%` | Modulo | `5 % 3` → `2` |

### Comparison Operators

| Operator | Description | Example |
|----------|-------------|---------|
| `==` | Equal | `5 == 5` → `true` |
| `!=` | Not equal | `5 != 3` → `true` |
| `<` | Less than | `3 < 5` → `true` |
| `<=` | Less or equal | `5 <= 5` → `true` |
| `>` | Greater than | `5 > 3` → `true` |
| `>=` | Greater or equal | `5 >= 5` → `true` |

### Logical Operators

| Operator | Description | Example |
|----------|-------------|---------|
| `&&` | Logical AND | `true && true` → `true` |
| `||` | Logical OR | `true || false` → `true` |
| `!` | Logical NOT | `!true` → `false` |

### Assignment Operator

| Operator | Description | Example |
|----------|-------------|---------|
| `=` | Assignment | `let x = 5` |

---

## Keywords

### Variable Declaration
- `let` - Declare variable

### Control Flow
- `if` - Conditional statement
- `else` - Alternative branch
- `for` - For loop
- `in` - Loop iterator
- `while` - While loop

### Functions
- `fn` - Function declaration
- `return` - Return from function

### Values
- `true` - Boolean true
- `false` - Boolean false
- `null` - Null value

---

## CGI Environment Variables

When running as CGI script, these environment variables are available via `env()`:

### Request Information

| Variable | Description | Example |
|----------|-------------|---------|
| `REQUEST_METHOD` | HTTP method | `GET`, `POST`, `PUT`, `DELETE` |
| `QUERY_STRING` | URL parameters | `name=John&age=25` |
| `CONTENT_TYPE` | Request content type | `application/json` |
| `CONTENT_LENGTH` | Request body size | `1024` |

### Server Information

| Variable | Description | Example |
|----------|-------------|---------|
| `SERVER_SOFTWARE` | Web server name | `nginx/1.18.0` |
| `SERVER_NAME` | Server hostname | `example.com` |
| `SERVER_PORT` | Server port | `80`, `443` |
| `SERVER_PROTOCOL` | HTTP protocol | `HTTP/1.1` |

### HTTP Headers

| Variable | Description | Example |
|----------|-------------|---------|
| `HTTP_HOST` | Host header | `example.com` |
| `HTTP_USER_AGENT` | Browser user agent | `Mozilla/5.0...` |
| `HTTP_ACCEPT` | Accept header | `text/html` |
| `HTTP_COOKIE` | Cookies | `session=abc123` |

### Client Information

| Variable | Description | Example |
|----------|-------------|---------|
| `REMOTE_ADDR` | Client IP address | `192.168.1.100` |
| `REMOTE_PORT` | Client port | `54321` |

### Script Information

| Variable | Description | Example |
|----------|-------------|---------|
| `SCRIPT_NAME` | Script path | `/cgi-bin/script.riau` |
| `PATH_INFO` | Extra path info | `/user/123` |

### System Variables

| Variable | Description | Example |
|----------|-------------|---------|
| `USERNAME` | System username | `john` |
| `HOME` | Home directory | `/home/john` |
| `PATH` | System PATH | `/usr/bin:/bin` |

---

## Examples

### Complete Web Application

```riau
// Get request info
let method = env("REQUEST_METHOD")
let query = env("QUERY_STRING")

// Send headers
print("Content-Type: text/html\n\n")

// Generate HTML
print("<html>")
print("<body>")
print("<h1>Riau Web App</h1>")
print("<p>Method: " + method + "</p>")
print("<p>Query: " + query + "</p>")
print("</body>")
print("</html>")
```

### API Endpoint

```riau
// JSON response
print("Content-Type: application/json\n\n")
print("{")
print("  \"status\": \"success\",")
print("  \"data\": {")
print("    \"version\": \"0.1.0\"")
print("  }")
print("}")
```

---

**Version**: 0.1.0  
**Last Updated**: 2026-01-08  
**License**: MIT

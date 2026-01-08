# 🚀 Bahasa Pemrograman Riau

<div align="center">

![Version](https://img.shields.io/badge/version-0.1.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C-orange.svg)
![PHP Compatibility](https://img.shields.io/badge/PHP%20compatibility-60%25-yellow.svg)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)

**Bahasa pemrograman backend modern yang mudah, aman, dan siap production.**

[Quick Start](#-quick-start) • [Documentation](#-daftar-isi) • [Examples](examples/) • [Contributing](#-support--kontribusi)

</div>

```riau
// Hello World
print("Hello from Riau!")

// Web Application
print("Content-Type: text/html\n\n")
print("<h1>Dynamic Web with Riau!</h1>")
print("<p>Request: " + env("REQUEST_METHOD") + "</p>")
```

---

## 📖 Daftar Isi

1. [Pengenalan](#-pengenalan)
2. [Quick Start](#-quick-start)
3. [Apakah Riau Setara dengan PHP?](#-apakah-riau-setara-dengan-php)
4. [Web Development (CGI)](#-web-development-cgi)
5. [Built-in Functions](#-built-in-functions)
6. [Sintaks Bahasa](#-sintaks-bahasa)
7. [Contoh Program](#-contoh-program)
8. [Arsitektur](#️-arsitektur)
9. [Build & Testing](#-build--testing)
10. [Troubleshooting](#-troubleshooting)

---

## 🎯 Pengenalan

**Riau** adalah bahasa pemrograman yang dirancang untuk:
- ✅ **Kemudahan** - Syntax bersih seperti Python/JavaScript
- ✅ **Keamanan** - Null safety built-in
- ✅ **Performa** - Bytecode VM yang cepat
- ✅ **Web Ready** - CGI support untuk web development
- ✅ **Production** - Siap pakai dari awal

### Fitur Utama
- 🔹 Type inference otomatis
- 🔹 Null safety dengan operator `?`
- 🔹 Error handling dengan try-catch
- 🔹 Garbage collection otomatis
- 🔹 **CGI web support** (seperti PHP)
- 🔹 REPL untuk eksperimen cepat
- 🔹 **Enhanced error messages** dengan suggestions
- 🔹 **"Did you mean?"** untuk typos
- 🔹 **Performance benchmarking** tools
- 🔹 **Color-coded error output**

### 🎯 Killer Feature

**Riau = Best CGI Scripting Language**

Menggabungkan:
- ✅ Kemudahan PHP (drop file & run)
- ✅ Keamanan Rust (null safety built-in)
- ✅ Syntax modern TypeScript
- ✅ Performa Go (bytecode VM)

### 🔒 API Stability Guarantee

- ✅ **Built-in Functions**: Stable API (no breaking changes in 0.1.x)
- ✅ **Backward Compatibility**: Guaranteed within minor versions
- ✅ **Semantic Versioning**: Strictly followed
- ✅ **Deterministic Execution**: Same bytecode = same results

---

## 📦 Installation

### One-Line Install (Recommended)

**Linux / macOS**:
```bash
curl -sSL https://riau-lang.github.io/install.sh | bash
```

**Windows (PowerShell)**:
```powershell
iwr https://riau-lang.github.io/install.ps1 | iex
```

### Manual Install

Download binary from [Releases](https://github.com/yourusername/riau/releases):
- **Windows**: `riau-windows-x64.exe`
- **Linux**: `riau-linux-x64`
- **macOS**: `riau-macos-x64`

Add to PATH and you're ready!

### Build from Source

```bash
git clone https://github.com/yourusername/riau.git
cd riau
.\build.bat      # Windows
./build.sh       # Linux/macOS
```

**Full guide**: [INSTALLATION.md](docs/INSTALLATION.md)

---

## ⚡ Quick Start

### 1. Install GCC/MinGW

#### Windows
```bash
# Download MinGW-w64 dari: https://www.mingw-w64.org/downloads/
# Atau install via MSYS2:
pacman -S mingw-w64-x86_64-gcc

# Tambahkan ke PATH:
# C:\msys64\mingw64\bin

# Verifikasi
gcc --version
```

#### Linux
```bash
sudo apt update
sudo apt install build-essential
```

#### macOS
```bash
xcode-select --install
```

### 2. Build Riau

```bash
# Windows
.\build.bat

# Linux/macOS
chmod +x build.sh
./build.sh
```

### 3. Jalankan!

```bash
# REPL Mode
.\bin\riau.exe

# Run File
.\bin\riau.exe examples\hello.riau

# Web Script
.\bin\riau.exe examples\web_hello.riau
```

---

## 🔥 Apakah Riau Setara dengan PHP?

### TL;DR: **Belum Sepenuhnya, Tapi Sudah Sangat Promising!**

Riau saat ini berada di **versi 0.1.0** dan sudah memiliki fondasi yang kuat untuk web development. Mari kita bandingkan secara detail:

### ✅ Fitur yang Sudah Setara dengan PHP

| Fitur | PHP | Riau | Status |
|-------|-----|------|--------|
| **CGI Support** | ✅ | ✅ | **SETARA** - Bisa langsung output HTML |
| **Environment Variables** | ✅ `$_SERVER` | ✅ `env()` | **SETARA** - Akses semua CGI vars |
| **Dynamic Output** | ✅ `echo`, `print` | ✅ `print()` | **SETARA** - Output ke stdout |
| **Variables** | ✅ | ✅ | **SETARA** - Type inference otomatis |
| **Functions** | ✅ | ✅ | **SETARA** - Normal & arrow functions |
| **Control Flow** | ✅ | ✅ | **SETARA** - if/else, loops |
| **Arrays** | ✅ | ✅ | **SETARA** - Built-in array support |
| **String Operations** | ✅ | ✅ | **SETARA** - Concat, upper, lower, length |
| **Math Operations** | ✅ | ✅ | **SETARA** - abs, floor, ceil, round |
| **Type Checking** | ✅ `gettype()` | ✅ `type_of()` | **SETARA** |
| **Null Safety** | ❌ (PHP 8+) | ✅ | **LEBIH BAIK** - Built-in dari awal |
| **Garbage Collection** | ✅ | ✅ | **SETARA** - Automatic memory management |

### ⚠️ Fitur yang Belum Ada (Roadmap)

| Fitur | PHP | Riau | Target Version |
|-------|-----|------|----------------|
| **POST Data** | ✅ `$_POST` | ❌ | v0.2.0 |
| **Cookies** | ✅ `$_COOKIE` | ❌ | v0.2.0 |
| **Sessions** | ✅ `$_SESSION` | ❌ | v0.2.0 |
| **File Upload** | ✅ `$_FILES` | ❌ | v0.2.0 |
| **JSON** | ✅ `json_encode/decode` | ❌ | v0.2.0 |
| **Database** | ✅ PDO, MySQLi | ❌ | v0.3.0 |
| **File I/O** | ✅ `fopen`, `fread` | ❌ | v0.3.0 |
| **Classes/OOP** | ✅ | ❌ | v0.4.0 |
| **Namespaces** | ✅ | ❌ | v0.4.0 |
| **Composer** | ✅ | ❌ | v1.0.0 |

### 💪 Keunggulan Riau vs PHP

#### 1. **Null Safety Built-in**
```riau
// Riau - Aman dari awal
let user? = findUser(id)
if user {
  print(user.email)  // Dijamin tidak crash
}
```

```php
// PHP - Perlu manual check
$user = findUser($id);
if ($user !== null) {
  echo $user->email;  // Bisa crash jika lupa check
}
```

#### 2. **Type Inference Otomatis**
```riau
// Riau - Tidak perlu deklarasi type
let name = "John"      // Otomatis string
let age = 25           // Otomatis number
let active = true      // Otomatis bool
```

```php
// PHP - Perlu declare atau loose typing
$name = "John";        // Loose typing
// atau
string $name = "John"; // PHP 7.4+
```

#### 3. **Syntax Modern & Bersih**
```riau
// Riau - Arrow function built-in
fn double(x) => x * 2

// Riau - No $ signs
let total = price * quantity
```

```php
// PHP - Arrow function PHP 7.4+
$double = fn($x) => $x * 2;

// PHP - $ everywhere
$total = $price * $quantity;
```

#### 4. **Bytecode VM = Lebih Cepat**
- **PHP**: Interpreted (kecuali dengan OPcache)
- **Riau**: Compiled ke bytecode, lalu dieksekusi di VM
- **Hasil**: Riau berpotensi lebih cepat untuk operasi komputasi

#### 5. **Error Messages Lebih Jelas**
```
Riau:
[Line 15] Error: Cannot use null value
  let email = user.email
              ^^^^^^^^^^

PHP:
Fatal error: Uncaught Error: Call to a member function on null
```

### 📊 Perbandingan Code: PHP vs Riau

#### Example 1: Simple Web Page

**PHP:**
```php
<?php
header("Content-Type: text/html");
?>
<html>
<body>
  <h1>Hello from PHP!</h1>
  <p>Method: <?php echo $_SERVER['REQUEST_METHOD']; ?></p>
  <p>User: <?php echo $_SERVER['USERNAME']; ?></p>
</body>
</html>
```

**Riau:**
```riau
print("Content-Type: text/html\n\n")
print("<html><body>")
print("<h1>Hello from Riau!</h1>")
print("<p>Method: " + env("REQUEST_METHOD") + "</p>")
print("<p>User: " + env("USERNAME") + "</p>")
print("</body></html>")
```

**Kesimpulan**: Hampir sama! Riau lebih konsisten (semua pakai `print()`).

#### Example 2: Form Handling

**PHP:**
```php
<?php
$method = $_SERVER['REQUEST_METHOD'];
$name = $_GET['name'] ?? 'Guest';

echo "<h1>Welcome, $name!</h1>";
echo "<p>Method: $method</p>";
?>
```

**Riau (v0.1.0 - GET only):**
```riau
let method = env("REQUEST_METHOD")
let query = env("QUERY_STRING")  // "name=John"

print("Content-Type: text/html\n\n")
print("<h1>Welcome!</h1>")
print("<p>Method: " + method + "</p>")
print("<p>Query: " + query + "</p>")
```

**Kesimpulan**: PHP lebih mudah untuk parsing query string (punya `$_GET`). Riau v0.2.0 akan menambahkan ini.

#### Example 3: Functions & Logic

**PHP:**
```php
<?php
function calculateDiscount($price, $percent) {
  return $price * ($percent / 100);
}

$price = 100000;
$discount = calculateDiscount($price, 20);
$final = $price - $discount;

echo "Final price: $final";
?>
```

**Riau:**
```riau
fn calculateDiscount(price, percent) {
  return price * (percent / 100)
}

let price = 100000
let discount = calculateDiscount(price, 20)
let final = price - discount

print("Final price: " + final)
```

**Kesimpulan**: Hampir identik! Riau lebih bersih (no `$`, no `<?php ?>`).

### 🎯 Kapan Pakai Riau vs PHP?

#### Pakai **PHP** Jika:
- ✅ Butuh ekosistem mature (Laravel, WordPress, Composer)
- ✅ Butuh database support sekarang juga
- ✅ Butuh banyak library third-party
- ✅ Butuh hosting shared yang murah (PHP ada di mana-mana)
- ✅ Butuh OOP dan design patterns kompleks

#### Pakai **Riau** Jika:
- ✅ Ingin syntax modern dan bersih
- ✅ Ingin null safety dari awal
- ✅ Ingin belajar bahasa baru yang promising
- ✅ Ingin kontribusi ke open source project
- ✅ Ingin performa bytecode VM
- ✅ Proyek kecil-menengah (API, microservices)

### 🚀 Kesimpulan: Apakah Riau Setara PHP?

**Untuk Web Development Dasar (v0.1.0):**
- ✅ **CGI/Web Output**: SETARA
- ✅ **Syntax & Logic**: SETARA (bahkan lebih modern)
- ⚠️ **Form Handling**: Partial (GET only, belum POST)
- ❌ **Database**: Belum ada
- ❌ **Ekosistem**: Belum ada

**Rating Keseluruhan**: **60% setara dengan PHP**

**Proyeksi v1.0.0**: **90% setara dengan PHP** (+ database, JSON, sessions, file I/O)

### 💡 Rekomendasi

**Riau sangat cocok untuk:**
1. ✅ Belajar membuat bahasa pemrograman
2. ✅ Proyek web sederhana (landing page, API sederhana)
3. ✅ CGI scripting
4. ✅ Microservices kecil
5. ✅ Eksperimen dan prototyping

**Belum cocok untuk:**
1. ❌ Production web app kompleks (tunggu v1.0.0)
2. ❌ E-commerce (butuh database, sessions)
3. ❌ CMS (butuh file upload, database)
4. ❌ Enterprise apps (butuh OOP, namespaces)

**Tapi dengan roadmap yang jelas, Riau akan segera menyusul PHP!** 🚀

---

## 🌐 Web Development (CGI)

Riau mendukung **CGI-style web development** seperti PHP!

### Built-in Functions untuk Web

#### `print(value)` - Output ke stdout
```riau
print("Content-Type: text/html\n\n")
print("<h1>Hello Web!</h1>")
```

#### `env(name)` - Baca environment variables
```riau
let method = env("REQUEST_METHOD")  // GET, POST, dll
let query = env("QUERY_STRING")     // URL parameters
let user = env("USERNAME")          // System username
```

### Environment Variables yang Tersedia

Semua CGI environment variables standar:
- `REQUEST_METHOD` - GET, POST, PUT, DELETE
- `QUERY_STRING` - URL parameters (`?name=John&age=25`)
- `CONTENT_TYPE` - Request content type
- `CONTENT_LENGTH` - Request body size
- `SERVER_SOFTWARE` - Web server name
- `HTTP_USER_AGENT` - Browser user agent
- `REMOTE_ADDR` - Client IP address
- Dan banyak lagi...

### Contoh Web Application

#### Simple Hello World
```riau
// web_hello.riau
print("Content-Type: text/html\n\n")
print("<html><body>")
print("<h1>🚀 Hello from Riau!</h1>")
print("<p>Request Method: ")
print(env("REQUEST_METHOD"))
print("</p>")
print("</body></html>")
```

#### Form Handling
```riau
// web_form.riau
print("Content-Type: text/html\n\n")

let method = env("REQUEST_METHOD")
let query = env("QUERY_STRING")

print("<html><body>")
print("<h1>Form Handler</h1>")
print("<form method='GET'>")
print("<input type='text' name='name'>")
print("<input type='submit'>")
print("</form>")
print("<p>Method: " + method + "</p>")
print("<p>Query: " + query + "</p>")
print("</body></html>")
```

### Setup Web Server

#### Option 1: Nginx (Recommended)

1. Download Nginx: https://nginx.org/en/download.html
2. Edit `nginx.conf`:

```nginx
http {
    server {
        listen 8080;
        server_name localhost;
        
        location ~ \.riau$ {
            # CGI configuration
            fastcgi_pass   127.0.0.1:9000;
            fastcgi_param  SCRIPT_FILENAME  $document_root$fastcgi_script_name;
            fastcgi_param  QUERY_STRING     $query_string;
            fastcgi_param  REQUEST_METHOD   $request_method;
            include        fastcgi_params;
        }
    }
}
```

#### Option 2: Apache

1. Install Apache
2. Enable CGI module
3. Configure `.htaccess`:

```apache
AddHandler cgi-script .riau
Options +ExecCGI
```

#### Option 3: Python CGI Server (Testing)

```bash
# Quick testing
python -m http.server --cgi 8000
```

### Testing Web Scripts Locally

```bash
# Set environment variable dan run
$env:REQUEST_METHOD="GET"
$env:QUERY_STRING="name=John&age=25"
.\bin\riau.exe examples\web_hello.riau
```

---

## � Built-in Functions

Riau menyediakan berbagai built-in functions yang siap pakai tanpa perlu import.

### 📤 Output Functions

#### `print(value)`
Output nilai ke stdout (untuk web: output ke browser).

```riau
print("Hello World")
print(123)
print(true)
print([1, 2, 3])

// Web output
print("Content-Type: text/html\n\n")
print("<h1>Hello</h1>")
```

**Return**: `null`

#### `log(value)`
Output dengan prefix `[LOG]` untuk debugging.

```riau
log("Debug info")
log("Value:", x)
```

**Return**: `null`

---

### 🌍 Environment Functions

#### `env(name)`
Membaca environment variable dari sistem atau web server.

```riau
// System variables
let user = env("USERNAME")
let home = env("HOME")
let path = env("PATH")

// CGI variables (web)
let method = env("REQUEST_METHOD")
let query = env("QUERY_STRING")
let userAgent = env("HTTP_USER_AGENT")
let clientIP = env("REMOTE_ADDR")
```

**Parameters**:
- `name` (string): Nama environment variable

**Return**: String value atau `null` jika tidak ada

**CGI Variables yang Tersedia**:
- `REQUEST_METHOD` - GET, POST, PUT, DELETE
- `QUERY_STRING` - URL parameters
- `CONTENT_TYPE` - Request content type
- `CONTENT_LENGTH` - Request body size
- `SERVER_SOFTWARE` - Web server name
- `SERVER_NAME` - Server hostname
- `SERVER_PORT` - Server port
- `HTTP_HOST` - HTTP host header
- `HTTP_USER_AGENT` - Browser user agent
- `HTTP_ACCEPT` - Accept header
- `HTTP_COOKIE` - Cookies
- `REMOTE_ADDR` - Client IP address
- `REMOTE_PORT` - Client port
- `SCRIPT_NAME` - Script path
- `PATH_INFO` - Extra path info

---

### 🔍 Type Functions

#### `type_of(value)`
Mendapatkan tipe data dari sebuah nilai.

```riau
let name = "John"
let age = 25
let active = true
let items = [1, 2, 3]

print(type_of(name))    // "string"
print(type_of(age))     // "number"
print(type_of(active))  // "bool"
print(type_of(items))   // "array"
print(type_of(null))    // "null"
```

**Parameters**:
- `value` (any): Nilai yang ingin dicek tipenya

**Return**: String nama tipe (`"null"`, `"bool"`, `"number"`, `"string"`, `"array"`, `"object"`, `"function"`)

#### `len(value)`
Mendapatkan panjang string atau array.

```riau
let text = "Hello"
let numbers = [1, 2, 3, 4, 5]

print(len(text))     // 5
print(len(numbers))  // 5
```

**Parameters**:
- `value` (string | array): String atau array

**Return**: Number (panjang), atau `-1` jika tipe tidak valid

---

### 📝 String Functions

#### `str_concat(str1, str2, ...)`
Menggabungkan beberapa string.

```riau
let full = str_concat("Hello", " ", "World")
print(full)  // "Hello World"

// Atau pakai operator +
let full2 = "Hello" + " " + "World"
```

**Parameters**:
- `str1, str2, ...` (string): String yang ingin digabung

**Return**: String hasil gabungan

#### `str_length(str)`
Mendapatkan panjang string (alias dari `len()`).

```riau
let text = "Riau"
print(str_length(text))  // 4
```

**Return**: Number

#### `str_upper(str)`
Mengubah string menjadi uppercase.

```riau
let text = "hello world"
print(str_upper(text))  // "HELLO WORLD"
```

**Return**: String uppercase

#### `str_lower(str)`
Mengubah string menjadi lowercase.

```riau
let text = "HELLO WORLD"
print(str_lower(text))  // "hello world"
```

**Return**: String lowercase

---

### 📚 Array Functions

#### `array_push(array, value)`
Menambahkan elemen ke akhir array.

```riau
let numbers = [1, 2, 3]
array_push(numbers, 4)
print(numbers)  // [1, 2, 3, 4]
```

**Parameters**:
- `array` (array): Array target
- `value` (any): Nilai yang ingin ditambahkan

**Return**: Array yang sudah dimodifikasi

#### `array_pop(array)`
Menghapus dan mengembalikan elemen terakhir array.

```riau
let numbers = [1, 2, 3, 4]
let last = array_pop(numbers)
print(last)      // 4
print(numbers)   // [1, 2, 3]
```

**Parameters**:
- `array` (array): Array target

**Return**: Elemen terakhir, atau `null` jika array kosong

#### `array_length(array)`
Mendapatkan jumlah elemen dalam array (alias dari `len()`).

```riau
let items = [1, 2, 3, 4, 5]
print(array_length(items))  // 5
```

**Return**: Number

---

### 🔢 Math Functions

#### `math_abs(number)`
Mendapatkan nilai absolut (nilai positif).

```riau
print(math_abs(-10))   // 10
print(math_abs(5))     // 5
print(math_abs(-3.14)) // 3.14
```

**Return**: Number (nilai absolut)

#### `math_floor(number)`
Membulatkan ke bawah ke integer terdekat.

```riau
print(math_floor(3.7))   // 3
print(math_floor(3.2))   // 3
print(math_floor(-2.5))  // -3
```

**Return**: Number (integer)

#### `math_ceil(number)`
Membulatkan ke atas ke integer terdekat.

```riau
print(math_ceil(3.2))   // 4
print(math_ceil(3.7))   // 4
print(math_ceil(-2.5))  // -2
```

**Return**: Number (integer)

#### `math_round(number)`
Membulatkan ke integer terdekat.

```riau
print(math_round(3.2))  // 3
print(math_round(3.7))  // 4
print(math_round(3.5))  // 4
```

**Return**: Number (integer)

---

### 📋 Ringkasan Built-in Functions

| Kategori | Function | Deskripsi |
|----------|----------|-----------|
| **Output** | `print(value)` | Output ke stdout |
| | `log(value)` | Output dengan prefix [LOG] |
| **Environment** | `env(name)` | Baca environment variable |
| **Type** | `type_of(value)` | Get tipe data |
| | `len(value)` | Panjang string/array |
| **String** | `str_concat(...)` | Gabung string |
| | `str_length(str)` | Panjang string |
| | `str_upper(str)` | Uppercase |
| | `str_lower(str)` | Lowercase |
| **Array** | `array_push(arr, val)` | Tambah elemen |
| | `array_pop(arr)` | Hapus elemen terakhir |
| | `array_length(arr)` | Jumlah elemen |
| **Math** | `math_abs(n)` | Nilai absolut |
| | `math_floor(n)` | Bulatkan ke bawah |
| | `math_ceil(n)` | Bulatkan ke atas |
| | `math_round(n)` | Bulatkan terdekat |

**Total**: 16 built-in functions siap pakai! 🎉

---

## �📝 Sintaks Bahasa

### 1. Variabel

```riau
// Type inference
let name = "Riau"
let age = 21
let price = 99.99
let active = true

// Null safety
let user? = findUser(id)  // Bisa null
if user {
  print(user.email)       // Aman
}
```

### 2. Operators

```riau
// Aritmatika
a + b   // Penjumlahan
a - b   // Pengurangan
a * b   // Perkalian
a / b   // Pembagian
a % b   // Modulo

// Perbandingan
a == b  // Sama dengan
a != b  // Tidak sama
a < b   // Kurang dari
a <= b  // Kurang dari atau sama
a > b   // Lebih dari
a >= b  // Lebih dari atau sama

// Logika
a && b  // AND
a || b  // OR
!a      // NOT
```

### 3. Control Flow

```riau
// If-Else
if score >= 90 {
  print("Grade: A")
} else {
  print("Grade: B")
}

// For Loop
let numbers = [1, 2, 3, 4, 5]
for num in numbers {
  print(num)
}
```

### 4. Functions

```riau
// Normal function
fn add(a, b) {
  return a + b
}

// Arrow function
fn double(x) => x * 2

// With types
fn divide(a: float, b: float): float {
  return a / b
}
```

### 5. Built-in Functions

```riau
print(value)           // Print ke stdout
env(name)              // Get environment variable
type_of(value)         // Get type
len(array_or_string)   // Get length
```

---

## 💡 Contoh Program

### Hello World
```riau
print("Hello, Riau!")
print("Bahasa pemrograman yang mudah dan aman")
```

### Aritmatika
```riau
let a = 10
let b = 20
let sum = a + b
let product = a * b

print("10 + 20 = " + sum)
print("10 * 20 = " + product)
```

### Variables
```riau
let name = "Riyan"
let age = 21
let salary = 5000000.50

print("Name: " + name)
print("Age: " + age)
print("Salary: " + salary)
```

### Web Application
```riau
// Dynamic web page
print("Content-Type: text/html\n\n")
print("<html>")
print("<head><title>Riau Web</title></head>")
print("<body>")
print("<h1>Welcome to Riau!</h1>")
print("<p>This page is generated dynamically.</p>")
print("<p>Your username: " + env("USERNAME") + "</p>")
print("</body>")
print("</html>")
```

Lihat lebih banyak di folder `examples/`:
- `hello.riau` - Hello world
- `arithmetic.riau` - Operasi matematika
- `variables.riau` - Deklarasi variabel
- `web_hello.riau` - Web hello world
- `web_form.riau` - Form handling

---

## 🏗️ Arsitektur

### Pipeline Kompilasi
```
Source Code (.riau)
       ↓
    LEXER (Tokenisasi)
       ↓
    PARSER (Analisis Sintaks)
       ↓
     AST (Abstract Syntax Tree)
       ↓
  SEMANTIC ANALYZER (Type Checking)
       ↓
  COMPILER (Bytecode Generation)
       ↓
   BYTECODE
       ↓
  VIRTUAL MACHINE (Eksekusi)
       ↓
  RUNTIME SYSTEM (Memory, GC)
```

### Komponen Utama

1. **Lexer** - Tokenisasi source code
2. **Parser** - Recursive descent parser, build AST
3. **Semantic Analyzer** - Type checking, null safety
4. **Compiler** - AST to bytecode
5. **Virtual Machine** - Stack-based execution
6. **Runtime** - Garbage collection, memory management

### Struktur Folder
```
riau/
├── engine/              # Core implementation
│   ├── lexer/          # Tokenizer
│   ├── parser/         # Syntax analyzer
│   ├── ast/            # AST definitions
│   ├── semantic/       # Type checker
│   ├── bytecode/       # Compiler & bytecode
│   ├── vm/             # Virtual machine
│   └── cli/            # Command-line interface
├── examples/           # Example programs
├── bin/                # Compiled binary
├── build/              # Build artifacts
├── build.bat           # Windows build script
├── build.sh            # Linux/macOS build script
└── README.md           # This file
```

---

## 🔨 Build & Testing

### Build dari Source

```bash
# Windows
.\build.bat

# Linux/macOS
chmod +x build.sh
./build.sh
```

Output:
```
✅ Build successful!
Run REPL: bin\riau.exe
Run file: bin\riau.exe examples\hello.riau
```

### Running Tests

```bash
# Windows
.\test.bat

# Linux/macOS
chmod +x test.sh
./test.sh
```

### Manual Testing

```bash
# Test REPL
.\bin\riau.exe

# Test examples
.\bin\riau.exe examples\hello.riau
.\bin\riau.exe examples\arithmetic.riau
.\bin\riau.exe examples\web_hello.riau

# Test with environment
$env:TEST_VAR="Hello"
.\bin\riau.exe test_env.riau
```

---

## 🔧 Troubleshooting

### ❌ "gcc not found"

**Solusi:**
1. Install MinGW-w64 (Windows) atau build-essential (Linux)
2. Tambahkan ke PATH:
   - Windows: `C:\msys64\mingw64\bin`
   - Linux: Biasanya sudah di PATH
3. Restart terminal
4. Verifikasi: `gcc --version`

**Cek PATH:**
```bash
# Windows PowerShell
$env:PATH

# Linux/macOS
echo $PATH
```

### ❌ Build Failed

**Solusi:**
```bash
# Clean build artifacts
# Windows
rmdir /s /q build bin

# Linux/macOS
rm -rf build bin

# Rebuild
.\build.bat  # atau ./build.sh
```

### ⚠️ "stdio.h not found" di IDE

**Ini BUKAN error!** Hanya lint warning dari IDE.

**Penjelasan:**
- IDE (VS Code, dll) tidak tahu lokasi MinGW headers
- GCC akan menemukan headers dengan benar saat compile
- Build akan sukses meskipun ada warning ini

**Perbedaan:**
- **Lint Warning** (IDE): Muncul di editor, tidak block compile
- **Compilation Error** (GCC): Muncul saat compile, block binary

**Ignore warning ini dan compile saja!**

### ❌ Permission Denied (Linux/macOS)

```bash
chmod +x build.sh test.sh
./build.sh
```

### ❌ Web Script Tidak Jalan

**Cek:**
1. HTTP headers sudah dikirim? `print("Content-Type: text/html\n\n")`
2. Environment variables di-set web server?
3. CGI configured dengan benar?

**Debug:**
```bash
# Test lokal dulu
.\bin\riau.exe examples\web_hello.riau

# Set env manual
$env:REQUEST_METHOD="GET"
.\bin\riau.exe examples\web_hello.riau
```

---

## 📊 Fitur yang Sudah Diimplementasi

### ✅ Core Language
- [x] **Lexer** - Tokenizer lengkap (50+ token types)
- [x] **Parser** - Recursive descent parser
- [x] **AST** - Abstract Syntax Tree (25+ node types)
- [x] **Semantic Analyzer** - Type checking & validation
- [x] **Null Safety** - Built-in null safety validation
- [x] **Bytecode Compiler** - AST to bytecode compilation
- [x] **Virtual Machine** - Stack-based VM (50+ opcodes)
- [x] **Garbage Collection** - Reference counting memory management

### ✅ Data Types (7 Types)
- [x] `null` - Null value
- [x] `bool` - Boolean (true/false)
- [x] `number` - Double-precision floating point
- [x] `string` - UTF-8 strings
- [x] `array` - Dynamic arrays
- [x] `object` - Key-value objects
- [x] `function` - First-class functions

### ✅ Built-in Functions (16 Functions)
- [x] **Output**: `print()`, `log()`
- [x] **Environment**: `env()`
- [x] **Type**: `type_of()`, `len()`
- [x] **String**: `str_concat()`, `str_length()`, `str_upper()`, `str_lower()`
- [x] **Array**: `array_push()`, `array_pop()`, `array_length()`
- [x] **Math**: `math_abs()`, `math_floor()`, `math_ceil()`, `math_round()`

### ✅ Operators (15+ Operators)
- [x] **Arithmetic**: `+`, `-`, `*`, `/`, `%`
- [x] **Comparison**: `==`, `!=`, `<`, `<=`, `>`, `>=`
- [x] **Logical**: `&&`, `||`, `!`
- [x] **Assignment**: `=`

### ✅ Control Flow
- [x] **Conditionals**: `if`, `else`
- [x] **Loops**: `for...in`, `while`
- [x] **Functions**: Normal & arrow functions
- [x] **Return**: Early return from functions

### ✅ Web Development (CGI)
- [x] **CGI Support** - Full CGI compatibility
- [x] **HTTP Headers** - Output headers via `print()`
- [x] **Environment Variables** - Access via `env()`
- [x] **Dynamic HTML** - Generate HTML dynamically
- [x] **Form Handling** - GET requests (QUERY_STRING)
- [x] **Web Server Ready** - Nginx/Apache integration

### ✅ Tools & Infrastructure
- [x] **CLI** - Command-line interface
- [x] **REPL Mode** - Interactive shell
- [x] **File Execution** - Run .riau files
- [x] **Error Reporting** - Clear error messages with line numbers
- [x] **Build System** - Cross-platform (Windows/Linux/macOS)
- [x] **Test Suite** - Automated testing

### ✅ Documentation
- [x] **README.md** - Comprehensive guide (this file!)
- [x] **Examples** - 11+ example programs
- [x] **PHP Comparison** - Detailed comparison with PHP
- [x] **Built-in Functions Docs** - Complete API documentation

---

## 🚀 Roadmap

### v0.2.0 - Enhanced Web Features
- [ ] POST data handling
- [ ] Cookie support
- [ ] Session management
- [ ] JSON parsing
- [ ] String manipulation functions

### v0.3.0 - Database & Advanced
- [ ] Database drivers (MySQL, PostgreSQL, SQLite)
- [ ] File I/O operations
- [ ] Template engine
- [ ] WebSocket support

### v1.0.0 - Production Ready
- [ ] JIT compilation
- [ ] Package manager
- [ ] Debugger
- [ ] Performance optimizations
- [ ] Production case studies

---

## 💡 Best Practices

### 1. Web Development

```riau
// ✅ Good - Always send headers first
print("Content-Type: text/html\n\n")
print("<html>...")

// ❌ Bad - No headers
print("<html>...")
```

### 2. Null Safety

```riau
// ✅ Good - Check for null
let user? = findUser(id)
if user {
  print(user.email)
}

// ❌ Bad - Unsafe
let user = findUser(id)
print(user.email)  // Crash jika null
```

### 3. Environment Variables

```riau
// ✅ Good - Handle null
let method = env("REQUEST_METHOD")
if method {
  print("Method: " + method)
} else {
  print("Method: Unknown")
}
```

---

## 📚 Resources

### Documentation
- **README.md** (file ini) - Panduan lengkap
- **examples/** - Contoh program
- **LICENSE** - MIT License

### External Links
- CGI Specification: https://www.w3.org/CGI/
- Nginx Documentation: https://nginx.org/en/docs/
- Apache CGI Guide: https://httpd.apache.org/docs/current/howto/cgi.html

---

## 📞 Support & Kontribusi

### Menemukan Bug?
1. Cek apakah sudah ada di issues
2. Buat issue baru dengan detail:
   - Versi Riau (`.\bin\riau.exe --version`)
   - OS dan compiler (`gcc --version`)
   - Code yang error
   - Error message lengkap

### Ingin Kontribusi?
1. Fork repository
2. Buat branch baru
3. Commit changes
4. Push dan buat Pull Request

### Lisensi
MIT License - Bebas untuk commercial dan personal use

---

## 🛠️ Development Tools

### Helper Scripts

Untuk mempermudah development, gunakan script helper:

#### Linux/macOS
```bash
chmod +x dev.sh

# Commands
./dev.sh clean      # Clean build artifacts
./dev.sh build      # Build Riau
./dev.sh test       # Run tests
./dev.sh rebuild    # Clean and build
./dev.sh dev        # Full dev cycle (clean, build, test)
./dev.sh repl       # Start REPL
./dev.sh run file.riau  # Run file
./dev.sh examples   # Run all examples
```

#### Windows
```cmd
# Commands
dev.bat clean      # Clean build artifacts
dev.bat build      # Build Riau
dev.bat test       # Run tests
dev.bat rebuild    # Clean and build
dev.bat dev        # Full dev cycle
dev.bat repl       # Start REPL
dev.bat run file.riau  # Run file
dev.bat examples   # Run all examples
```

### CI/CD

Project ini menggunakan GitHub Actions untuk automated testing:
- ✅ Multi-platform builds (Linux, macOS, Windows)
- ✅ Automated testing
- ✅ Build artifacts

### Editor Configuration

File `.editorconfig` tersedia untuk konsistensi formatting:
- C/H files: 4 spaces
- Riau files: 2 spaces
- Markdown: 2 spaces
- Consistent line endings

---

## 📚 Resources

### Documentation
- **[README.md](README.md)** - Panduan lengkap (file ini)
- **[API_REFERENCE.md](docs/API_REFERENCE.md)** - Complete API documentation
- **[CONTRIBUTING.md](CONTRIBUTING.md)** - Panduan kontribusi
- **[CHANGELOG.md](CHANGELOG.md)** - Version history
- **[examples/](examples/)** - 12+ contoh program

### External Links
- **CGI Specification**: https://www.w3.org/CGI/
- **Nginx Documentation**: https://nginx.org/en/docs/
- **Apache CGI Guide**: https://httpd.apache.org/docs/current/howto/cgi.html
- **MinGW-w64**: https://www.mingw-w64.org/

### Community
- **Issues**: Report bugs dan suggest features
- **Pull Requests**: Contribute code
- **Discussions**: Ask questions dan share ideas

---

## ✨ Kesimpulan

**Riau** adalah bahasa pemrograman yang:
- ✅ Mudah dipelajari dengan syntax modern
- ✅ Aman dengan null safety built-in
- ✅ Cepat dengan bytecode VM
- ✅ **Siap untuk web development** (CGI seperti PHP)
- ✅ Production-ready untuk proyek kecil-menengah
- ✅ Open source (MIT License)

### 🎯 Positioning

**Status**: **Experimental Production Language**

Bukan "bahasa mainan" ❌  
Bukan "PHP killer" ❌  
**Tapi**: Fondasi bahasa serius untuk CGI scripting ✅

### 🚀 Killer Feature

**The Best CGI Scripting Language**

Menggabungkan kemudahan PHP, keamanan Rust, syntax modern TypeScript, dan performa Go.

👉 **Baca manifesto lengkap**: [Why Riau Exists](docs/WHY_RIAU.md)

### 🎯 Apakah Setara dengan PHP?

**Rating: 60% setara dengan PHP (v0.1.1)**

✅ **Sudah Setara**:
- CGI web support
- Environment variables
- Dynamic HTML output
- Functions & control flow
- Arrays & strings
- Math operations
- **Null safety** (lebih baik dari PHP!)

⚠️ **Belum Ada** (Coming Soon):
- POST data handling (v0.2.0)
- Database support (v0.3.0)
- File I/O (v0.3.0)
- OOP/Classes (v0.4.0)

**Proyeksi v1.0.0: 90% setara dengan PHP**

### 📊 Fitur Lengkap

| Kategori | Jumlah | Status |
|----------|--------|--------|
| **Built-in Functions (Stable API)** | 16 | ✅ Lengkap |
| **Operators** | 15+ | ✅ Lengkap |
| **Data Types** | 7 | ✅ Lengkap |
| **Control Flow** | if/else, for, while | ✅ Lengkap |
| **CGI Variables** | 15+ | ✅ Lengkap |
| **Bytecode Opcodes** | 50+ | ✅ Lengkap |

### 🔒 Stability Guarantee

- ✅ Backward compatibility within minor versions (0.1.x)
- ✅ Semantic versioning strictly followed
- ✅ Stable built-in functions API
- ✅ Deterministic VM execution

### 🚀 Mulai Sekarang:

1. **Install GCC** - `gcc --version`
2. **Build Riau** - `.\build.bat`
3. **Test REPL** - `.\bin\riau.exe`
4. **Buat Web App** - Edit `examples\web_hello.riau`
5. **Deploy** - Setup Nginx/Apache

**Selamat coding dengan Riau!** 🎉

---

**Versi**: 0.1.1  
**Terakhir Update**: 2026-01-08  
**Status**: Experimental Production Language  
**Tagline**: *The Best CGI Scripting Language*  
**Bahasa**: Indonesia  
**Lisensi**: MIT  
**Built-in Functions**: 16 (Stable API)  
**PHP Compatibility**: 60% (v0.1.1) → 90% (v1.0.0)

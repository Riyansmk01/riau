# Quick Start Guide - 5 Minutes to Riau

## 1. Install (1 minute)

### One-Line Install

**Linux/macOS**:
```bash
curl -sSL https://riau-lang.github.io/install.sh | bash
```

**Windows**:
```powershell
iwr https://riau-lang.github.io/install.ps1 | iex
```

### Verify
```bash
riau --version
```

---

## 2. Hello World (1 minute)

```bash
echo 'print("Hello, Riau!")' > hello.riau
riau hello.riau
```

**Output**: `Hello, Riau!`

---

## 3. Variables & Functions (1 minute)

```riau
// Variables
let name = "Riau"
let version = 0.1
let active = true

// Functions
fn greet(name) {
    return "Hello, " + name + "!"
}

print(greet("World"))
```

---

## 4. Web Application (2 minutes)

### Create Web Script

```riau
// web.riau
print("Content-Type: text/html\n\n")
print("<html>")
print("<body>")
print("<h1>Hello from Riau!</h1>")

let method = env("REQUEST_METHOD")
let query = env("QUERY_STRING")

print("<p>Method: " + method + "</p>")
print("<p>Query: " + query + "</p>")
print("</body>")
print("</html>")
```

### Run Locally
```bash
riau web.riau
```

### Deploy to Web Server

**Apache** (`httpd.conf`):
```apache
AddHandler cgi-script .riau
Options +ExecCGI
```

**Nginx** (`nginx.conf`):
```nginx
location ~ \.riau$ {
    fastcgi_pass unix:/var/run/fcgiwrap.socket;
    include fastcgi_params;
}
```

---

## 5. Next Steps

### Learn More
- [Full Documentation](../README.md)
- [API Reference](API_REFERENCE.md)
- [Examples](../examples/)

### Build Something
- REST API
- Form handler
- Dynamic website
- Automation script

### Get Help
- [GitHub Issues](https://github.com/yourusername/riau/issues)
- [Discussions](https://github.com/yourusername/riau/discussions)

---

**Congratulations!** You're now ready to build with Riau! 🎉

**Tagline**: *The Best CGI Scripting Language*

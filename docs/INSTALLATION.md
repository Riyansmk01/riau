# Installation Guide

## Quick Install

### Linux / macOS
```bash
curl -sSL https://raw.githubusercontent.com/Riyansmk01/riau/main/install.sh | bash
```

### Windows (PowerShell)
```powershell
iwr https://raw.githubusercontent.com/Riyansmk01/riau/main/install.ps1 | iex
```

### Manual Install

#### 1. Download Binary

**Windows**:
- Download `riau-windows-x64.exe` from [Releases](https://github.com/yourusername/riau/releases)
- Rename to `riau.exe`
- Move to `C:\Program Files\Riau\` or `%USERPROFILE%\.riau\bin\`

**Linux**:
```bash
wget https://github.com/yourusername/riau/releases/download/latest/riau-linux-x64
chmod +x riau-linux-x64
sudo mv riau-linux-x64 /usr/local/bin/riau
```

**macOS**:
```bash
curl -L https://github.com/yourusername/riau/releases/download/latest/riau-macos-x64 -o riau
chmod +x riau
sudo mv riau /usr/local/bin/riau
```

#### 2. Add to PATH

**Windows**:
1. Open System Properties → Environment Variables
2. Edit `Path` variable
3. Add `C:\Program Files\Riau\` or your install directory

**Linux/macOS**:
```bash
echo 'export PATH="$PATH:$HOME/.riau/bin"' >> ~/.bashrc
source ~/.bashrc
```

#### 3. Verify Installation

```bash
riau --version
```

---

## Build from Source

### Prerequisites
- GCC 7.0+ or Clang 10.0+
- Git

### Steps

```bash
# Clone repository
git clone https://github.com/yourusername/riau.git
cd riau

# Build
./build.sh        # Linux/macOS
.\build.bat       # Windows

# Install
sudo cp bin/riau /usr/local/bin/  # Linux/macOS
# Or add bin/ to PATH
```

---

## Quick Start

### 1. Hello World

```bash
echo 'print("Hello, Riau!")' > hello.riau
riau hello.riau
```

### 2. Web Application

```bash
cat > web.riau << 'EOF'
print("Content-Type: text/html\n\n")
print("<h1>Hello from Riau!</h1>")
print("<p>Request: " + env("REQUEST_METHOD") + "</p>")
EOF

riau web.riau
```

### 3. Executable Script (Unix)

```bash
cat > script.riau << 'EOF'
#!/usr/bin/env riau
print("Executable Riau script!")
EOF

chmod +x script.riau
./script.riau
```

---

## Web Server Setup

### Apache

#### 1. Enable CGI
```apache
# In httpd.conf or .htaccess
AddHandler cgi-script .riau
Options +ExecCGI
```

#### 2. Configure Directory
```apache
<Directory "/var/www/html">
    Options +ExecCGI
    AddHandler cgi-script .riau
</Directory>
```

#### 3. Create Script
```bash
cat > /var/www/html/index.riau << 'EOF'
#!/usr/bin/env riau
print("Content-Type: text/html\n\n")
print("<h1>Riau on Apache!</h1>")
EOF

chmod +x /var/www/html/index.riau
```

### Nginx

#### 1. Configure CGI
```nginx
location ~ \.riau$ {
    gzip off;
    root /var/www/html;
    fastcgi_pass unix:/var/run/fcgiwrap.socket;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

#### 2. Install fcgiwrap
```bash
# Ubuntu/Debian
sudo apt install fcgiwrap

# CentOS/RHEL
sudo yum install fcgiwrap
```

#### 3. Create Script
```bash
cat > /var/www/html/index.riau << 'EOF'
#!/usr/bin/env riau
print("Content-Type: text/html\n\n")
print("<h1>Riau on Nginx!</h1>")
EOF

chmod +x /var/www/html/index.riau
```

---

## Troubleshooting

### "riau: command not found"
- Check if `riau` is in PATH: `echo $PATH`
- Verify installation: `ls ~/.riau/bin/` or `ls /usr/local/bin/`
- Restart terminal or run `source ~/.bashrc`

### "Permission denied" (Unix)
```bash
chmod +x /path/to/riau
```

### CGI not working
- Check file permissions: `chmod +x script.riau`
- Verify shebang: `#!/usr/bin/env riau`
- Check web server error logs
- Ensure CGI is enabled in server config

### Build errors
- Update GCC: `gcc --version` (need 7.0+)
- Install build tools: `sudo apt install build-essential`
- Check for missing dependencies

---

## Uninstall

### Installed via script
```bash
rm -rf ~/.riau
# Remove from PATH in ~/.bashrc or ~/.zshrc
```

### Manual install
```bash
sudo rm /usr/local/bin/riau
```

### Windows
```powershell
Remove-Item -Recurse -Force "$env:USERPROFILE\.riau"
# Remove from PATH in Environment Variables
```

---

## Next Steps

- Read [Documentation](../README.md)
- Try [Examples](../examples/)
- Join [Community](https://github.com/yourusername/riau/discussions)
- Report [Issues](https://github.com/yourusername/riau/issues)

---

**Version**: 0.1.1  
**Last Updated**: 2026-01-08  
**License**: MIT

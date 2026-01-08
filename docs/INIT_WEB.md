# Riau Init-Web - Project Scaffolding Tool

## Usage

```bash
riau init-web [project-name]
```

## What It Creates

```
myproject/
├── .htaccess              # Apache configuration
├── index.riau             # Homepage template
├── about.riau             # About page template
├── api/
│   └── example.riau       # API example
├── public/
│   ├── css/
│   │   └── style.css      # CSS template
│   └── js/
│       └── script.js      # JS template
└── README.md              # Project documentation
```

## Implementation (v0.2.0)

This command will be implemented in the next version. For now, you can manually create the structure:

### Step 1: Create .htaccess

```apache
Options +ExecCGI
AddHandler cgi-script .riau
DirectoryIndex index.riau index.html

# Security
<FilesMatch "\.(riau)$">
    Require all granted
</FilesMatch>
```

### Step 2: Create index.riau

```riau
#!/usr/bin/env riau
print("Content-Type: text/html; charset=UTF-8\n\n")

print("<!DOCTYPE html>")
print("<html lang='en'>")
print("<head>")
print("    <meta charset='UTF-8'>")
print("    <meta name='viewport' content='width=device-width, initial-scale=1.0'>")
print("    <title>My Riau App</title>")
print("    <link rel='stylesheet' href='public/css/style.css'>")
print("</head>")
print("<body>")
print("    <div class='container'>")
print("        <h1>Welcome to Riau!</h1>")
print("        <p>Your web application is ready.</p>")
print("        <nav>")
print("            <a href='index.riau'>Home</a>")
print("            <a href='about.riau'>About</a>")
print("            <a href='api/example.riau'>API</a>")
print("        </nav>")
print("    </div>")
print("    <script src='public/js/script.js'></script>")
print("</body>")
print("</html>")
```

### Step 3: Create public/css/style.css

```css
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    min-height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
}

.container {
    background: white;
    padding: 3rem;
    border-radius: 20px;
    box-shadow: 0 20px 60px rgba(0,0,0,0.3);
    max-width: 600px;
    width: 90%;
}

h1 {
    color: #667eea;
    margin-bottom: 1rem;
}

p {
    color: #666;
    margin-bottom: 2rem;
}

nav a {
    display: inline-block;
    background: #667eea;
    color: white;
    padding: 0.8rem 1.5rem;
    border-radius: 8px;
    text-decoration: none;
    margin: 0.5rem;
    transition: all 0.3s;
}

nav a:hover {
    background: #764ba2;
    transform: translateY(-2px);
}
```

## Quick Start Script (Windows)

Save as `init-web.bat`:

```batch
@echo off
set PROJECT=%1

if "%PROJECT%"=="" (
    echo Usage: init-web.bat project-name
    exit /b 1
)

echo Creating Riau project: %PROJECT%
mkdir %PROJECT%
cd %PROJECT%

echo Creating .htaccess...
echo Options +ExecCGI > .htaccess
echo AddHandler cgi-script .riau >> .htaccess
echo DirectoryIndex index.riau index.html >> .htaccess

echo Creating index.riau...
echo #!/usr/bin/env riau > index.riau
echo print("Content-Type: text/html\n\n") >> index.riau
echo print("<h1>Welcome to %PROJECT%!</h1>") >> index.riau

echo Creating folder structure...
mkdir public\css
mkdir public\js
mkdir api

echo Project created successfully!
echo.
echo Next steps:
echo   1. cd %PROJECT%
echo   2. Edit index.riau
echo   3. Deploy to Apache/Nginx
```

## Quick Start Script (Unix/Linux)

Save as `init-web.sh`:

```bash
#!/bin/bash

PROJECT=$1

if [ -z "$PROJECT" ]; then
    echo "Usage: ./init-web.sh project-name"
    exit 1
fi

echo "Creating Riau project: $PROJECT"
mkdir -p "$PROJECT"
cd "$PROJECT"

echo "Creating .htaccess..."
cat > .htaccess << 'EOF'
Options +ExecCGI
AddHandler cgi-script .riau
DirectoryIndex index.riau index.html
EOF

echo "Creating index.riau..."
cat > index.riau << 'EOF'
#!/usr/bin/env riau
print("Content-Type: text/html; charset=UTF-8\n\n")
print("<h1>Welcome to Riau!</h1>")
EOF

chmod +x index.riau

echo "Creating folder structure..."
mkdir -p public/css
mkdir -p public/js
mkdir -p api

echo "Project created successfully!"
echo ""
echo "Next steps:"
echo "  1. cd $PROJECT"
echo "  2. Edit index.riau"
echo "  3. Deploy to Apache/Nginx"
```

---

**Note**: Full `riau init-web` command will be available in v0.2.0

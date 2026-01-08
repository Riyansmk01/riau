#!/bin/bash
# Riau Init-Web - Project Scaffolding Tool
# Usage: ./init-web.sh project-name

PROJECT=$1

if [ -z "$PROJECT" ]; then
    echo "Usage: ./init-web.sh project-name"
    echo ""
    echo "Example:"
    echo "  ./init-web.sh myproject"
    exit 1
fi

echo "========================================="
echo "  Riau Init-Web"
echo "  Creating project: $PROJECT"
echo "========================================="
echo ""

# Create project directory
if [ -d "$PROJECT" ]; then
    echo "Error: Directory $PROJECT already exists!"
    exit 1
fi

mkdir -p "$PROJECT"
cd "$PROJECT"

# Create .htaccess
echo "Creating .htaccess..."
cat > .htaccess << 'EOF'
Options +ExecCGI
AddHandler cgi-script .riau
DirectoryIndex index.riau index.html

# Security
<FilesMatch "\.(riau)$">
    Require all granted
</FilesMatch>
EOF

# Create index.riau
echo "Creating index.riau..."
cat > index.riau << EOF
#!/usr/bin/env riau
print("Content-Type: text/html; charset=UTF-8\n\n")

print("<!DOCTYPE html>")
print("<html lang='en'>")
print("<head>")
print("    <meta charset='UTF-8'>")
print("    <meta name='viewport' content='width=device-width, initial-scale=1.0'>")
print("    <title>$PROJECT</title>")
print("    <link rel='stylesheet' href='public/css/style.css'>")
print("</head>")
print("<body>")
print("    <div class='container'>")
print("        <h1>Welcome to $PROJECT!</h1>")
print("        <p>Your Riau web application is ready.</p>")
print("        <nav>")
print("            <a href='index.riau'>Home</a>")
print("            <a href='about.riau'>About</a>")
print("            <a href='api/example.riau'>API</a>")
print("        </nav>")
print("    </div>")
print("    <script src='public/js/script.js'></script>")
print("</body>")
print("</html>")
EOF

chmod +x index.riau

# Create about.riau
echo "Creating about.riau..."
cat > about.riau << EOF
#!/usr/bin/env riau
print("Content-Type: text/html; charset=UTF-8\n\n")
print("<h1>About $PROJECT</h1>")
print("<p>This is the about page.</p>")
print("<a href='index.riau'>Back to Home</a>")
EOF

chmod +x about.riau

# Create folder structure
echo "Creating folder structure..."
mkdir -p public/css
mkdir -p public/js
mkdir -p api

# Create style.css
echo "Creating public/css/style.css..."
cat > public/css/style.css << 'EOF'
* { margin: 0; padding: 0; box-sizing: border-box; }
body { font-family: 'Segoe UI', sans-serif; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; display: flex; align-items: center; justify-content: center; }
.container { background: white; padding: 3rem; border-radius: 20px; box-shadow: 0 20px 60px rgba(0,0,0,0.3); max-width: 600px; width: 90%; }
h1 { color: #667eea; margin-bottom: 1rem; }
p { color: #666; margin-bottom: 2rem; }
nav a { display: inline-block; background: #667eea; color: white; padding: 0.8rem 1.5rem; border-radius: 8px; text-decoration: none; margin: 0.5rem; transition: all 0.3s; }
nav a:hover { background: #764ba2; transform: translateY(-2px); }
EOF

# Create script.js
echo "Creating public/js/script.js..."
cat > public/js/script.js << 'EOF'
console.log('Riau app loaded!');
EOF

# Create API example
echo "Creating api/example.riau..."
cat > api/example.riau << EOF
#!/usr/bin/env riau
print("Content-Type: application/json; charset=UTF-8\n\n")
print("{")
print("  \"status\": \"success\",")
print("  \"message\": \"API endpoint working!\",")
print("  \"project\": \"$PROJECT\"")
print("}")
EOF

chmod +x api/example.riau

# Create README
echo "Creating README.md..."
cat > README.md << EOF
# $PROJECT

Riau web application created with \`init-web.sh\`

## Quick Start

1. Deploy to Apache/Nginx
2. Visit \`http://localhost/$PROJECT/\`

## Structure

- \`index.riau\` - Homepage
- \`about.riau\` - About page
- \`api/example.riau\` - API endpoint
- \`public/\` - Static assets

## Documentation

See https://github.com/Riyansmk01/riau
EOF

echo ""
echo "========================================="
echo "  Project Created Successfully!"
echo "========================================="
echo ""
echo "Next steps:"
echo "  1. cd $PROJECT"
echo "  2. Edit index.riau"
echo "  3. Deploy to Apache/Nginx"
echo "  4. Visit http://localhost/$PROJECT/"
echo ""
echo "Files created:"
echo "  - .htaccess"
echo "  - index.riau"
echo "  - about.riau"
echo "  - api/example.riau"
echo "  - public/css/style.css"
echo "  - public/js/script.js"
echo "  - README.md"
echo ""

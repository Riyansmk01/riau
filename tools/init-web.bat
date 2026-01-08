@echo off
REM Riau Init-Web - Project Scaffolding Tool
REM Usage: init-web.bat project-name

set PROJECT=%1

if "%PROJECT%"=="" (
    echo Usage: init-web.bat project-name
    echo.
    echo Example:
    echo   init-web.bat myproject
    exit /b 1
)

echo =========================================
echo   Riau Init-Web
echo   Creating project: %PROJECT%
echo =========================================
echo.

REM Create project directory
if exist "%PROJECT%" (
    echo Error: Directory %PROJECT% already exists!
    exit /b 1
)

mkdir "%PROJECT%"
cd "%PROJECT%"

REM Create .htaccess
echo Creating .htaccess...
(
echo Options +ExecCGI
echo AddHandler cgi-script .riau
echo DirectoryIndex index.riau index.html
echo.
echo # Security
echo ^<FilesMatch "\.(riau)$"^>
echo     Require all granted
echo ^</FilesMatch^>
) > .htaccess

REM Create index.riau
echo Creating index.riau...
(
echo #!/usr/bin/env riau
echo print("Content-Type: text/html; charset=UTF-8\n\n"^)
echo.
echo print("^<!DOCTYPE html^>"^)
echo print("^<html lang='en'^>"^)
echo print("^<head^>"^)
echo print("    ^<meta charset='UTF-8'^>"^)
echo print("    ^<meta name='viewport' content='width=device-width, initial-scale=1.0'^>"^)
echo print("    ^<title^>%PROJECT%^</title^>"^)
echo print("    ^<link rel='stylesheet' href='public/css/style.css'^>"^)
echo print("^</head^>"^)
echo print("^<body^>"^)
echo print("    ^<div class='container'^>"^)
echo print("        ^<h1^>Welcome to %PROJECT%!^</h1^>"^)
echo print("        ^<p^>Your Riau web application is ready.^</p^>"^)
echo print("        ^<nav^>"^)
echo print("            ^<a href='index.riau'^>Home^</a^>"^)
echo print("            ^<a href='about.riau'^>About^</a^>"^)
echo print("            ^<a href='api/example.riau'^>API^</a^>"^)
echo print("        ^</nav^>"^)
echo print("    ^</div^>"^)
echo print("    ^<script src='public/js/script.js'^>^</script^>"^)
echo print("^</body^>"^)
echo print("^</html^>"^)
) > index.riau

REM Create about.riau
echo Creating about.riau...
(
echo #!/usr/bin/env riau
echo print("Content-Type: text/html; charset=UTF-8\n\n"^)
echo print("^<h1^>About %PROJECT%^</h1^>"^)
echo print("^<p^>This is the about page.^</p^>"^)
echo print("^<a href='index.riau'^>Back to Home^</a^>"^)
) > about.riau

REM Create folder structure
echo Creating folder structure...
mkdir public\css
mkdir public\js
mkdir api

REM Create style.css
echo Creating public/css/style.css...
(
echo * { margin: 0; padding: 0; box-sizing: border-box; }
echo body { font-family: 'Segoe UI', sans-serif; background: linear-gradient(135deg, #667eea 0%%, #764ba2 100%%^); min-height: 100vh; display: flex; align-items: center; justify-content: center; }
echo .container { background: white; padding: 3rem; border-radius: 20px; box-shadow: 0 20px 60px rgba(0,0,0,0.3^); max-width: 600px; width: 90%%; }
echo h1 { color: #667eea; margin-bottom: 1rem; }
echo p { color: #666; margin-bottom: 2rem; }
echo nav a { display: inline-block; background: #667eea; color: white; padding: 0.8rem 1.5rem; border-radius: 8px; text-decoration: none; margin: 0.5rem; transition: all 0.3s; }
echo nav a:hover { background: #764ba2; transform: translateY(-2px^); }
) > public\css\style.css

REM Create script.js
echo Creating public/js/script.js...
(
echo console.log('Riau app loaded!'^);
) > public\js\script.js

REM Create API example
echo Creating api/example.riau...
(
echo #!/usr/bin/env riau
echo print("Content-Type: application/json; charset=UTF-8\n\n"^)
echo print("{"^)
echo print("  \"status\": \"success\","^)
echo print("  \"message\": \"API endpoint working!\","^)
echo print("  \"project\": \"%PROJECT%\""^)
echo print("}"^)
) > api\example.riau

REM Create README
echo Creating README.md...
(
echo # %PROJECT%
echo.
echo Riau web application created with `init-web.bat`
echo.
echo ## Quick Start
echo.
echo 1. Deploy to Apache/Nginx
echo 2. Visit `http://localhost/%PROJECT%/`
echo.
echo ## Structure
echo.
echo - `index.riau` - Homepage
echo - `about.riau` - About page
echo - `api/example.riau` - API endpoint
echo - `public/` - Static assets
echo.
echo ## Documentation
echo.
echo See https://github.com/Riyansmk01/riau
) > README.md

echo.
echo =========================================
echo   Project Created Successfully!
echo =========================================
echo.
echo Next steps:
echo   1. cd %PROJECT%
echo   2. Edit index.riau
echo   3. Deploy to Apache/Nginx
echo   4. Visit http://localhost/%PROJECT%/
echo.
echo Files created:
echo   - .htaccess
echo   - index.riau
echo   - about.riau
echo   - api/example.riau
echo   - public/css/style.css
echo   - public/js/script.js
echo   - README.md
echo.

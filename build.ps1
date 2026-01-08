# Build script for Riau Programming Language (PowerShell with UCRT64)

Write-Host "Building Riau Programming Language..." -ForegroundColor Cyan

# Use UCRT64 GCC
$GCC = "C:\msys64\ucrt64\bin\gcc.exe"

# Create directories
if (!(Test-Path "build")) { New-Item -ItemType Directory -Path "build" | Out-Null }
if (!(Test-Path "bin")) { New-Item -ItemType Directory -Path "bin" | Out-Null }

# Compile source files
Write-Host "Compiling lexer..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/lexer/lexer.c -o build/lexer.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling AST..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/ast/ast.c -o build/ast.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling parser..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/parser/parser.c -o build/parser.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling semantic analyzer..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/semantic/semantic.c -o build/semantic.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling bytecode..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/bytecode.c -o build/bytecode.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling compiler..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/compiler.c -o build/compiler.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling VM..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/vm/vm.c -o build/vm.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling error reporter..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/errors/error_reporter.c -o build/error_reporter.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host "Compiling CLI..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -Iengine -c engine/cli/main.c -o build/main.o
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

# Link
Write-Host "Linking..." -ForegroundColor Yellow
& $GCC -Wall -Wextra -std=c11 -O2 -o bin/riau.exe build/lexer.o build/ast.o build/parser.o build/semantic.o build/bytecode.o build/compiler.o build/vm.o build/error_reporter.o build/main.o -lm
if ($LASTEXITCODE -ne 0) { Write-Host "Build failed!" -ForegroundColor Red; exit 1 }

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "Build successful!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Run REPL: bin\riau.exe"
Write-Host "Run file: bin\riau.exe examples\hello.riau"
Write-Host "Run tests: bin\riau.exe examples\arithmetic.riau"
Write-Host ""

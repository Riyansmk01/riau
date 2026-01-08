Write-Host "Compiling Riau Programming Language..." -ForegroundColor Cyan

# Create directories
if (-not (Test-Path "build")) { New-Item -ItemType Directory -Path "build" | Out-Null }
if (-not (Test-Path "bin")) { New-Item -ItemType Directory -Path "bin" | Out-Null }

# Compile each file
$files = @(
    @{Name = "lexer"; Path = "engine/lexer/lexer.c" },
    @{Name = "ast"; Path = "engine/ast/ast.c" },
    @{Name = "parser"; Path = "engine/parser/parser.c" },
    @{Name = "semantic"; Path = "engine/semantic/semantic.c" },
    @{Name = "bytecode"; Path = "engine/bytecode/bytecode.c" },
    @{Name = "compiler"; Path = "engine/bytecode/compiler.c" },
    @{Name = "vm"; Path = "engine/vm/vm.c" },
    @{Name = "main"; Path = "engine/cli/main.c" }
)

$success = $true
foreach ($file in $files) {
    Write-Host "`nCompiling $($file.Name)..." -ForegroundColor Yellow
    gcc -Wall -Wextra -std=c11 -O2 -Iengine -c $file.Path -o "build/$($file.Name).o"
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Failed to compile $($file.Name)" -ForegroundColor Red
        $success = $false
        break
    }
}

if ($success) {
    Write-Host "`nLinking..." -ForegroundColor Yellow
    gcc -Wall -Wextra -std=c11 -O2 -o bin/riau.exe build/lexer.o build/ast.o build/parser.o build/semantic.o build/bytecode.o build/compiler.o build/vm.o build/main.o -lm
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "`n========================================" -ForegroundColor Green
        Write-Host "Build successful!" -ForegroundColor Green
        Write-Host "========================================" -ForegroundColor Green
        Write-Host "`nRun REPL: bin\riau.exe"
        Write-Host "Run file: bin\riau.exe examples\hello.riau"
    }
    else {
        Write-Host "`nLinking failed!" -ForegroundColor Red
    }
}
else {
    Write-Host "`n========================================" -ForegroundColor Red
    Write-Host "Build failed!" -ForegroundColor Red
    Write-Host "========================================" -ForegroundColor Red
}

@echo off
REM Build script for Riau Programming Language (Windows with MSYS2)

echo Building Riau Programming Language...

REM Create directories
if not exist "build" mkdir build
if not exist "bin" mkdir bin

REM Compile source files
echo Compiling lexer...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/lexer/lexer.c -o build/lexer.o
if errorlevel 1 goto error

echo Compiling AST...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/ast/ast.c -o build/ast.o
if errorlevel 1 goto error

echo Compiling parser...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/parser/parser.c -o build/parser.o
if errorlevel 1 goto error

echo Compiling semantic analyzer...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/semantic/semantic.c -o build/semantic.o
if errorlevel 1 goto error

echo Compiling bytecode...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/bytecode.c -o build/bytecode.o
if errorlevel 1 goto error

echo Compiling compiler...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/compiler.c -o build/compiler.o
if errorlevel 1 goto error

echo Compiling VM...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/vm/vm.c -o build/vm.o
if errorlevel 1 goto error

echo Compiling error reporter...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/errors/error_reporter.c -o build/error_reporter.o
if errorlevel 1 goto error

echo Compiling CLI...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/cli/main.c -o build/main.o
if errorlevel 1 goto error

REM Link
echo Linking...
gcc -Wall -Wextra -std=c11 -O2 -o bin/riau.exe build/lexer.o build/ast.o build/parser.o build/semantic.o build/bytecode.o build/compiler.o build/vm.o build/error_reporter.o build/main.o -lm
if errorlevel 1 goto error

echo.
echo ========================================
echo Build successful!
echo ========================================
echo.
echo Run REPL: bin\riau.exe
echo Run file: bin\riau.exe examples\hello.riau
echo Run tests: bin\riau.exe examples\arithmetic.riau
echo.
goto end

:error
echo.
echo ========================================
echo Build failed!
echo ========================================
echo.
echo Check the error messages above.
echo.
exit /b 1

:end

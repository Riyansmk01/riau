@echo off
REM Test runner for Riau Programming Language

echo ========================================
echo Running Riau Test Suite
echo ========================================
echo.

REM Build tests
echo Building tests...
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/lexer/lexer.c -o build/lexer.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/ast/ast.c -o build/ast.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/parser/parser.c -o build/parser.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/bytecode/bytecode.c -o build/bytecode.o
gcc -Wall -Wextra -std=c11 -O2 -Iengine -c engine/vm/vm.c -o build/vm.o

REM Build and run lexer tests
echo.
echo [1/3] Lexer Tests
gcc -Wall -Wextra -std=c11 -O2 -Iengine -o build/test_lexer.exe engine/tests/test_lexer.c build/lexer.o
if errorlevel 1 goto error
build\test_lexer.exe
if errorlevel 1 goto error

REM Build and run parser tests
echo.
echo [2/3] Parser Tests
gcc -Wall -Wextra -std=c11 -O2 -Iengine -o build/test_parser.exe engine/tests/test_parser.c build/lexer.o build/ast.o build/parser.o
if errorlevel 1 goto error
build\test_parser.exe
if errorlevel 1 goto error

REM Build and run VM tests
echo.
echo [3/3] VM Tests
gcc -Wall -Wextra -std=c11 -O2 -Iengine -o build/test_vm.exe engine/tests/test_vm.c build/bytecode.o build/vm.o -lm
if errorlevel 1 goto error
build\test_vm.exe
if errorlevel 1 goto error

echo.
echo ========================================
echo All tests passed!
echo ========================================
goto end

:error
echo.
echo ========================================
echo Tests failed!
echo ========================================
exit /b 1

:end

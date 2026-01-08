@echo off
REM Development helper script for Riau (Windows)

setlocal enabledelayedexpansion

REM Commands
if "%1"=="clean" goto clean
if "%1"=="build" goto build
if "%1"=="test" goto test
if "%1"=="rebuild" goto rebuild
if "%1"=="dev" goto dev
if "%1"=="repl" goto repl
if "%1"=="run" goto run
if "%1"=="examples" goto examples
if "%1"=="help" goto help
if "%1"=="" goto help
goto unknown

:clean
echo ========================================
echo   Cleaning build artifacts
echo ========================================
if exist build rmdir /s /q build
if exist bin rmdir /s /q bin
echo [32m✓[0m Clean complete
goto end

:build
echo ========================================
echo   Building Riau
echo ========================================
call build.bat
if errorlevel 1 (
    echo [31m✗[0m Build failed
    exit /b 1
)
echo [32m✓[0m Build complete
goto end

:test
echo ========================================
echo   Running tests
echo ========================================
call test.bat
if errorlevel 1 (
    echo [31m✗[0m Tests failed
    exit /b 1
)
echo [32m✓[0m Tests complete
goto end

:rebuild
call :clean
call :build
goto end

:dev
echo ========================================
echo   Development mode
echo ========================================
call :rebuild
call :test
echo [32m✓[0m Ready for development!
goto end

:repl
echo ========================================
echo   Starting REPL
echo ========================================
if not exist bin\riau.exe (
    echo [31m✗[0m Binary not found. Building first...
    call :build
)
bin\riau.exe
goto end

:run
if "%2"=="" (
    echo [31m✗[0m Usage: dev.bat run ^<file.riau^>
    exit /b 1
)
if not exist bin\riau.exe (
    echo [31m✗[0m Binary not found. Building first...
    call :build
)
echo ========================================
echo   Running %2
echo ========================================
bin\riau.exe %2
goto end

:examples
echo ========================================
echo   Running all examples
echo ========================================
if not exist bin\riau.exe (
    echo [31m✗[0m Binary not found. Building first...
    call :build
)
for %%f in (examples\*.riau) do (
    echo.
    echo [33mℹ[0m Running: %%f
    bin\riau.exe %%f
    if errorlevel 1 echo [31m✗[0m Failed: %%f
)
echo [32m✓[0m All examples complete
goto end

:help
echo Riau Development Helper (Windows)
echo.
echo Usage: dev.bat ^<command^>
echo.
echo Commands:
echo   clean      - Clean build artifacts
echo   build      - Build Riau
echo   test       - Run tests
echo   rebuild    - Clean and build
echo   dev        - Full development cycle (clean, build, test)
echo   repl       - Start REPL
echo   run ^<file^> - Run a .riau file
echo   examples   - Run all example files
echo   help       - Show this help
goto end

:unknown
echo [31m✗[0m Unknown command: %1
call :help
exit /b 1

:end
endlocal

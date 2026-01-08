# Riau Language Installer for Windows
# Usage: iwr https://raw.githubusercontent.com/Riyansmk01/riau/main/install.ps1 | iex

$ErrorActionPreference = "Stop"

Write-Host "=========================================" -ForegroundColor Cyan
Write-Host "  Riau Language Installer" -ForegroundColor Cyan
Write-Host "  The Best CGI Scripting Language" -ForegroundColor Cyan
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host ""

# Detect architecture
$Arch = if ([Environment]::Is64BitOperatingSystem) { "x64" } else { "x86" }
$Version = if ($env:RIAU_VERSION) { $env:RIAU_VERSION } else { "latest" }
$InstallDir = if ($env:RIAU_INSTALL_DIR) { $env:RIAU_INSTALL_DIR } else { "$env:USERPROFILE\.riau" }
$BinDir = "$InstallDir\bin"

Write-Host "Platform: windows-$Arch"
Write-Host "Version: $Version"
Write-Host "Install directory: $InstallDir"
Write-Host ""

# Create directories
New-Item -ItemType Directory -Force -Path $BinDir | Out-Null

# Download binary
$DownloadUrl = "https://github.com/yourusername/riau/releases/download/$Version/riau-windows-$Arch.exe"

Write-Host "Downloading Riau..." -ForegroundColor Yellow
try {
    Invoke-WebRequest -Uri $DownloadUrl -OutFile "$BinDir\riau.exe"
    Write-Host "✓ Riau installed to $BinDir\riau.exe" -ForegroundColor Green
}
catch {
    Write-Host "Error downloading Riau: $_" -ForegroundColor Red
    exit 1
}

Write-Host ""

# Setup PATH
$UserPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($UserPath -notlike "*$BinDir*") {
    [Environment]::SetEnvironmentVariable(
        "Path",
        "$UserPath;$BinDir",
        "User"
    )
    Write-Host "✓ Added to PATH" -ForegroundColor Green
    Write-Host "  Restart your terminal for PATH changes to take effect" -ForegroundColor Yellow
}
else {
    Write-Host "✓ Already in PATH" -ForegroundColor Green
}

# Update current session PATH
$env:Path = "$env:Path;$BinDir"

Write-Host ""

# Test installation
Write-Host "Testing installation..." -ForegroundColor Yellow
try {
    $null = & "$BinDir\riau.exe" --version 2>&1
    Write-Host "✓ Riau installed successfully!" -ForegroundColor Green
}
catch {
    Write-Host "⚠ Installation complete, but --version not yet implemented" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "=========================================" -ForegroundColor Green
Write-Host "  Installation Complete!" -ForegroundColor Green
Write-Host "=========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Quick Start:"
Write-Host "  1. Create a file: echo 'print(`"Hello Riau!`")' > hello.riau"
Write-Host "  2. Run it: riau hello.riau"
Write-Host ""
Write-Host "Web Development:"
Write-Host "  1. Create: echo 'print(`"Content-Type: text/html\n\n<h1>Hello Web!</h1>`")' > web.riau"
Write-Host "  2. Setup CGI in Apache/Nginx"
Write-Host "  3. Visit your site!"
Write-Host ""
Write-Host "Documentation: https://github.com/yourusername/riau"
Write-Host "Examples: $InstallDir\examples\"
Write-Host ""

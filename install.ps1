# Riau Language Installer for Windows
# Usage: iwr https://raw.githubusercontent.com/Riyansmk01/riau/main/install.ps1 | iex

# Force TLS 1.2 (CRITICAL for GitHub downloads)
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

$ErrorActionPreference = "Stop"

Write-Host "=========================================" -ForegroundColor Cyan
Write-Host "  Riau Language Installer" -ForegroundColor Cyan
Write-Host "  The Best CGI Scripting Language" -ForegroundColor Cyan
Write-Host "=========================================" -ForegroundColor Cyan
Write-Host ""

# Detect architecture
$Arch = if ([Environment]::Is64BitOperatingSystem) { "x64" } else { "x86" }
$Version = if ($env:RIAU_VERSION) { $env:RIAU_VERSION } else { "v0.1.1" }
$InstallDir = if ($env:RIAU_INSTALL_DIR) { $env:RIAU_INSTALL_DIR } else { "$env:USERPROFILE\.riau" }
$BinDir = "$InstallDir\bin"

Write-Host "Platform: windows-$Arch"
Write-Host "Version: $Version"
Write-Host "Install directory: $InstallDir"
Write-Host ""

# Create directories
New-Item -ItemType Directory -Force -Path $BinDir | Out-Null

# Download URL - use specific version (not 'latest' to avoid redirect issues)
$DownloadUrl = "https://github.com/Riyansmk01/riau/releases/download/$Version/riau-windows-$Arch.exe"
$ExePath = "$BinDir\riau.exe"

Write-Host "Downloading Riau..." -ForegroundColor Yellow
Write-Host "URL: $DownloadUrl" -ForegroundColor Gray

try {
    # Use HttpClient with User-Agent (CRITICAL for GitHub stability)
    $handler = New-Object System.Net.Http.HttpClientHandler
    $client = New-Object System.Net.Http.HttpClient($handler)
    
    # REQUIRED: User-Agent header prevents GitHub from closing connection
    $client.DefaultRequestHeaders.Add("User-Agent", "Riau-Installer/1.0")
    
    # Download binary
    $response = $client.GetAsync($DownloadUrl).Result
    
    if ($response.IsSuccessStatusCode) {
        $bytes = $response.Content.ReadAsByteArrayAsync().Result
        [System.IO.File]::WriteAllBytes($ExePath, $bytes)
        Write-Host "✓ Riau downloaded to $ExePath" -ForegroundColor Green
    }
    else {
        throw "HTTP $($response.StatusCode): $($response.ReasonPhrase)"
    }
    
    $client.Dispose()
}
catch {
    Write-Host "Error downloading Riau: $_" -ForegroundColor Red
    Write-Host "" -ForegroundColor Red
    Write-Host "Possible issues:" -ForegroundColor Yellow
    Write-Host "  1. Release not yet available (check: https://github.com/Riyansmk01/riau/releases)" -ForegroundColor Yellow
    Write-Host "  2. Network connection issue" -ForegroundColor Yellow
    Write-Host "  3. GitHub rate limit" -ForegroundColor Yellow
    Write-Host "  4. Incorrect version tag (current: $Version)" -ForegroundColor Yellow
    Write-Host "" -ForegroundColor Yellow
    Write-Host "Try manual download:" -ForegroundColor Cyan
    Write-Host "  $DownloadUrl" -ForegroundColor Gray
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
    $versionOutput = & "$ExePath" --version 2>&1
    Write-Host "✓ Riau installed successfully!" -ForegroundColor Green
    Write-Host "  Version: $versionOutput" -ForegroundColor Gray
}
catch {
    Write-Host "⚠ Installation complete, but --version not yet implemented" -ForegroundColor Yellow
    Write-Host "  Binary is ready at: $ExePath" -ForegroundColor Gray
}

Write-Host ""
Write-Host "=========================================" -ForegroundColor Green
Write-Host "  Installation Complete!" -ForegroundColor Green
Write-Host "=========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Quick Start:"
Write-Host "  1. Restart your terminal (or run: refreshenv)"
Write-Host "  2. Create a file: echo 'print(`"Hello Riau!`")' > hello.riau"
Write-Host "  3. Run it: riau hello.riau"
Write-Host ""
Write-Host "Web Development:"
Write-Host "  1. Create: echo 'print(`"Content-Type: text/html\n\n<h1>Hello Web!</h1>`")' > web.riau"
Write-Host "  2. Setup CGI in Apache/Nginx"
Write-Host "  3. Visit your site!"
Write-Host ""
Write-Host "Documentation: https://github.com/Riyansmk01/riau"
Write-Host "Examples: $InstallDir\examples\"
Write-Host ""

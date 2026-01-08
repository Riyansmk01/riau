#!/bin/bash
# Riau Language Installer for Linux/macOS
# Usage: curl -sSL https://riau-lang.github.io/install.sh | bash

set -e

echo "========================================="
echo "  Riau Language Installer"
echo "  The Best CGI Scripting Language"
echo "========================================="
echo ""

# Detect OS
OS="$(uname -s)"
ARCH="$(uname -m)"

case "$OS" in
    Linux*)     PLATFORM="linux";;
    Darwin*)    PLATFORM="macos";;
    *)          echo "Unsupported OS: $OS"; exit 1;;
esac

case "$ARCH" in
    x86_64)     ARCH="x64";;
    arm64)      ARCH="arm64";;
    aarch64)    ARCH="arm64";;
    *)          echo "Unsupported architecture: $ARCH"; exit 1;;
esac

# Version to install
VERSION="${RIAU_VERSION:-latest}"
INSTALL_DIR="${RIAU_INSTALL_DIR:-$HOME/.riau}"
BIN_DIR="$INSTALL_DIR/bin"

echo "Platform: $PLATFORM-$ARCH"
echo "Version: $VERSION"
echo "Install directory: $INSTALL_DIR"
echo ""

# Create directories
mkdir -p "$BIN_DIR"

# Download binary
DOWNLOAD_URL="https://github.com/yourusername/riau/releases/download/$VERSION/riau-$PLATFORM-$ARCH"

echo "Downloading Riau..."
if command -v curl &> /dev/null; then
    curl -sSL "$DOWNLOAD_URL" -o "$BIN_DIR/riau"
elif command -v wget &> /dev/null; then
    wget -q "$DOWNLOAD_URL" -O "$BIN_DIR/riau"
else
    echo "Error: curl or wget required"
    exit 1
fi

# Make executable
chmod +x "$BIN_DIR/riau"

echo "✓ Riau installed to $BIN_DIR/riau"
echo ""

# Setup PATH
SHELL_CONFIG=""
case "$SHELL" in
    */bash)     SHELL_CONFIG="$HOME/.bashrc";;
    */zsh)      SHELL_CONFIG="$HOME/.zshrc";;
    */fish)     SHELL_CONFIG="$HOME/.config/fish/config.fish";;
esac

if [ -n "$SHELL_CONFIG" ]; then
    if ! grep -q "RIAU" "$SHELL_CONFIG" 2>/dev/null; then
        echo "" >> "$SHELL_CONFIG"
        echo "# Riau Language" >> "$SHELL_CONFIG"
        echo "export PATH=\"\$PATH:$BIN_DIR\"" >> "$SHELL_CONFIG"
        echo "✓ Added to PATH in $SHELL_CONFIG"
        echo ""
        echo "Run: source $SHELL_CONFIG"
        echo "Or restart your terminal"
    fi
fi

# Test installation
echo "Testing installation..."
if "$BIN_DIR/riau" --version &> /dev/null; then
    echo "✓ Riau installed successfully!"
else
    echo "⚠ Installation complete, but --version not yet implemented"
fi

echo ""
echo "========================================="
echo "  Installation Complete!"
echo "========================================="
echo ""
echo "Quick Start:"
echo "  1. Create a file: echo 'print(\"Hello Riau!\")' > hello.riau"
echo "  2. Run it: riau hello.riau"
echo ""
echo "Web Development:"
echo "  1. Create: echo 'print(\"Content-Type: text/html\\n\\n<h1>Hello Web!</h1>\")' > web.riau"
echo "  2. Setup CGI in Apache/Nginx"
echo "  3. Visit your site!"
echo ""
echo "Documentation: https://github.com/yourusername/riau"
echo "Examples: $INSTALL_DIR/examples/"
echo ""

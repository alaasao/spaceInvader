#!/bin/bash
# Space Invaders - Build & Test Script

set -e

echo "╔════════════════════════════════════════╗"
echo "║   Space Invaders - Build & Test        ║"
echo "╚════════════════════════════════════════╝"
echo

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check dependencies
echo "[*] Checking dependencies..."
if ! command -v gcc &> /dev/null; then
    echo -e "${RED}✗ GCC not found${NC}"
    exit 1
fi
echo -e "${GREEN}✓ GCC${NC}"

if ! command -v make &> /dev/null; then
    echo -e "${RED}✗ Make not found${NC}"
    exit 1
fi
echo -e "${GREEN}✓ Make${NC}"

if ! pkg-config --exists ncurses 2>/dev/null; then
    echo -e "${RED}✗ ncurses development files not found${NC}"
    echo "  Install with: sudo apt-get install libncurses-dev"
    exit 1
fi
echo -e "${GREEN}✓ ncurses${NC}"

echo

# Clean and build
echo "[*] Building project..."
make distclean > /dev/null 2>&1 || true
make 2>&1 | grep -E "Built|error|Error" || true

if [ ! -f build/space_invaders_ncurses ]; then
    echo -e "${RED}✗ ncurses build failed${NC}"
    exit 1
fi
echo -e "${GREEN}✓ ncurses version built${NC}"

if [ ! -f build/space_invaders_sdl ]; then
    echo -e "${YELLOW}⚠ SDL3 version build failed (this may be expected)${NC}"
else
    echo -e "${GREEN}✓ SDL3 version built${NC}"
fi

echo

# Run basic checks
echo "[*] Running checks..."

# Check for symbol exports
nm build/space_invaders_ncurses | grep -q "game_init" && echo -e "${GREEN}✓ Model symbols present${NC}"
nm build/space_invaders_ncurses | grep -q "controller_init" && echo -e "${GREEN}✓ Controller symbols present${NC}"

echo

echo "[*] Build artifacts:"
ls -lh build/space_invaders_* 2>/dev/null | awk '{print "  " $9 " (" $5 ")"}'

echo

echo "╔════════════════════════════════════════╗"
echo "║   Ready to Play!                       ║"
echo "╠════════════════════════════════════════╣"
echo "║  ncurses:  make run-ncurses             ║"
echo "║  SDL3:     make run-sdl                 ║"
echo "╚════════════════════════════════════════╝"

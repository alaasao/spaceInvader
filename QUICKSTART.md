#!/bin/bash
# Quick Start Guide for Space Invaders

cat << 'EOF'
╔═══════════════════════════════════════════════════════════════╗
║           SPACE INVADERS - C Implementation                  ║
║              Quick Start Guide                                ║
╚═══════════════════════════════════════════════════════════════╝

📋 PROJECT OVERVIEW
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
A classic Space Invaders game written in C with:
  ✓ MVC Architecture (Model-View-Controller)
  ✓ Dual interfaces: ncurses (text) & SDL3 (graphical)
  ✓ Complete game mechanics with levels and scoring
  ✓ ISO C99 compliance with no memory leaks
  ✓ Full documentation and testing guides

📦 INSTALLATION & BUILD
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Prerequisites:
   sudo apt-get update
   sudo apt-get install build-essential libncurses-dev

2. Build the project:
   cd /home/kyoraku/Desktop/c/tp
   make

   This will create:
   • build/space_invaders_ncurses  (56 KB - text version)
   • build/space_invaders_sdl      (73 KB - graphical version)

🎮 PLAYING THE GAME
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Option 1: Play with ncurses (recommended for terminal)
  make run-ncurses
  or
  ./build/space_invaders_ncurses

Option 2: Play with SDL3 (requires X11 display)
  make run-sdl
  or
  LD_LIBRARY_PATH=./third/SDL3-3.2.24/build:./third/SDL3_image-3.2.4/build ./build/space_invaders_sdl

⌨️  CONTROLS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  A / LEFT ARROW   →  Move Left
  D / RIGHT ARROW  →  Move Right
  SPACE            →  Shoot
  P                →  Pause/Resume
  Q / ESC          →  Quit

📊 GAMEPLAY OVERVIEW
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  • Defend against waves of descending enemies
  • Use shields to block projectiles
  • Earn 10 points per enemy destroyed
  • Complete 10 levels to win
  • You have 3 lives
  • Game gets harder as fewer enemies remain

📁 PROJECT STRUCTURE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  src/              Source code files
  ├── model.c       Game logic & state (450+ lines)
  ├── controller.c  Input handling (75+ lines)
  ├── view_*.c      Rendering (280+250 lines)
  └── main.c        Game loop (300+ lines)

  include/          Header files
  ├── config.h      Game configuration
  ├── model.h       Game API
  ├── controller.h  Control API
  └── view_*.h      View interfaces

  build/            Compiled binaries
  Makefile          Build system
  README.md         Full documentation
  TESTING.md        Testing procedures
  LICENSE           MIT License

📚 DOCUMENTATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  README.md                - Full user and developer guide
  TESTING.md               - Testing and validation procedures
  COMPLETION_REPORT.md     - Project statistics and features
  Makefile (make help)     - Available build targets

🔧 COMMON COMMANDS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  make              Build both versions
  make run-ncurses  Build and run text version
  make run-sdl      Build and run graphical version
  make clean        Remove build artifacts
  make help         Show all available targets

  ./build.sh        Run automated build verification

🐛 TROUBLESHOOTING
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Terminal too small?
  → Resize to at least 100x25 characters and restart

ncurses version won't build?
  → Install: sudo apt-get install libncurses-dev

SDL version won't start?
  → Already in ./third/ directory, should work out of box

Controls not responding?
  → Ensure you pressed SPACE at the menu to start

❓ NEED HELP?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  1. Check README.md for detailed instructions
  2. Read TESTING.md for game mechanics
  3. Review code comments in src/ files
  4. Examine Makefile for build options

📋 SYSTEM REQUIREMENTS
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  Minimum:
  • Linux (Ubuntu 18.04+, Debian 10+)
  • GCC 5.0+ with C99 support
  • 20 MB disk space
  • 5 MB RAM
  
  Recommended:
  • Ubuntu 20.04 LTS or newer
  • 100x25+ terminal (ncurses)
  • 1024x768+ display (SDL3)

✅ QUICK TEST
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ./build.sh         Verify build integrity

📜 LICENSE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  MIT License - See LICENSE file for details

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Enjoy the game! 🎮
For more information, see README.md
EOF

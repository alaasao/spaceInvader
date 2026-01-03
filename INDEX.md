# Space Invaders - Complete Documentation Index

Welcome to the Space Invaders C implementation! This document helps you navigate all project files and documentation.

## 🚀 Quick Links

| Need | File | Purpose |
|------|------|---------|
| **Quick Start** | [QUICKSTART.md](QUICKSTART.md) | 5-minute setup and play guide |
| **Play Now** | `make run-ncurses` | Launch the game immediately |
| **Full Guide** | [README.md](README.md) | Complete user & developer guide |
| **How to Test** | [TESTING.md](TESTING.md) | Testing procedures & validation |
| **Project Stats** | [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) | Statistics and feature overview |
| **Build Details** | [COMPLETION_REPORT.md](COMPLETION_REPORT.md) | Detailed technical report |

## 📁 Project Structure

```
space-invaders/
├── 📄 Documentation
│   ├── README.md                    ← Start here for comprehensive guide
│   ├── QUICKSTART.md                ← 5-minute quick start
│   ├── TESTING.md                   ← Testing procedures
│   ├── PROJECT_SUMMARY.md           ← Statistics & features
│   ├── COMPLETION_REPORT.md         ← Technical details
│   ├── LICENSE                      ← MIT License
│   └── INDEX.md                     ← This file
│
├── 🔨 Build System
│   ├── Makefile                     ← Complete build configuration
│   └── build.sh                     ← Build verification script
│
├── 💻 Source Code
│   └── src/
│       ├── model.c                  ← Game logic (450+ lines)
│       ├── controller.c             ← Input handling (75+ lines)
│       ├── view_ncurses.c           ← Text rendering (280+ lines)
│       ├── view_sdl.c               ← Graphics rendering (250+ lines)
│       ├── utils.c                  ← Utilities (50+ lines)
│       └── main.c                   ← Game loop (300+ lines)
│
├── 📚 Headers
│   └── include/
│       ├── model.h                  ← Game API
│       ├── controller.h             ← Control API
│       ├── view_ncurses.h           ← ncurses API
│       ├── view_sdl.h               ← SDL3 API
│       ├── utils.h                  ← Utils API
│       └── config.h                 ← Game constants
│
├── 🎮 Executables
│   └── build/
│       ├── space_invaders_ncurses   ← Text-based version (56 KB)
│       └── space_invaders_sdl       ← Graphical version (73 KB)
│
└── 📦 Third-Party
    └── third/
        ├── SDL3-3.2.24/             ← SDL3 library
        └── SDL3_image-3.2.4/        ← SDL3 Image library
```

## 📖 Documentation Guide

### For First-Time Users
1. Read [QUICKSTART.md](QUICKSTART.md) (5 minutes)
2. Run `make run-ncurses` to play
3. If you have questions, check [README.md](README.md) § Troubleshooting

### For Developers
1. Read [README.md](README.md) § Architecture section
2. Review code comments in `src/` files
3. Read [COMPLETION_REPORT.md](COMPLETION_REPORT.md) for technical details
4. Check [TESTING.md](TESTING.md) for validation procedures

### For Testing & Validation
1. See [TESTING.md](TESTING.md) § Unit Testing
2. Use `./build.sh` for quick verification
3. Run `make valgrind-*` for memory checks
4. Review [TESTING.md](TESTING.md) § Test Coverage Checklist

### For Building & Configuration
1. Check [README.md](README.md) § Building section
2. Review `Makefile` for build targets
3. Edit `include/config.h` to customize gameplay
4. Run `make help` for all targets

## 🎮 Gameplay Guide

### Controls
| Key | Action |
|-----|--------|
| `A` / `←` | Move Left |
| `D` / `→` | Move Right |
| `SPACE` | Shoot |
| `P` | Pause/Resume |
| `Q` / `ESC` | Quit |

### Game Objectives
- Destroy all enemies in each wave
- Avoid enemy projectiles (use shields)
- Progress through 10 levels
- Maximize your score
- Don't lose all 3 lives

### Scoring
- 10 points per enemy destroyed
- 100 bonus points per level completed
- Total maximum: 100 enemies + 9 levels × 100 = 1,900 points

See [README.md](README.md) § Game Mechanics for details.

## 🔧 Common Tasks

### Build the Project
```bash
make              # Build both versions
make clean        # Remove build files
make distclean    # Complete cleanup
```

### Run the Game
```bash
make run-ncurses  # Text-based (recommended)
make run-sdl      # Graphical version
```

### Test for Memory Leaks
```bash
make valgrind-ncurses
make valgrind-sdl
```

### Verify Build
```bash
./build.sh        # Automated build check
```

See [README.md](README.md) for more details.

## 📊 Project Information

### Statistics
- **Lines of Code**: 1,828 (source + headers)
- **Source Files**: 6
- **Header Files**: 6
- **Compilation Time**: < 2 seconds
- **Binary Size**: 56 KB (ncurses) + 73 KB (SDL3)
- **Project Size**: 472 KB (excluding third-party)

### Requirements
- **OS**: Linux (Ubuntu 18.04+)
- **Compiler**: GCC 5.0+ with C99
- **Libraries**: ncurses-dev, SDL3 (included)
- **Terminal**: 100x25 minimum (for ncurses)
- **Disk**: 20 MB
- **RAM**: 5 MB minimum

### Features
- ✅ Dual interfaces (ncurses + SDL3)
- ✅ MVC architecture
- ✅ 10 levels with progression
- ✅ Physics & collision detection
- ✅ Shield system
- ✅ Score tracking
- ✅ No memory leaks
- ✅ Complete documentation

See [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) for full details.

## 🐛 Troubleshooting

### Terminal Too Small
- Resize your terminal to at least 100x25 characters
- For ncurses version: check with `resize` command

### ncurses Won't Build
```bash
sudo apt-get install libncurses-dev
```

### SDL3 Version Doesn't Run
- SDL3 libraries are in `./third/` directory
- Try: `make run-sdl`
- Or manually: `LD_LIBRARY_PATH=./third/SDL3-3.2.24/build:./third/SDL3_image-3.2.4/build ./build/space_invaders_sdl`

### Game Runs Slowly
- Close other applications
- Try ncurses version instead of SDL3
- Check CPU usage with `top`

See [README.md](README.md) § Troubleshooting for more solutions.

## 📚 Reading Order

**Recommended reading order:**

1. **[QUICKSTART.md](QUICKSTART.md)** (5 min)
   - Overview and quick start
   - Common commands

2. **[README.md](README.md)** (20 min)
   - Complete user guide
   - Architecture overview
   - Configuration options

3. **[TESTING.md](TESTING.md)** (15 min)
   - How to test the game
   - Memory validation
   - Debug instructions

4. **[COMPLETION_REPORT.md](COMPLETION_REPORT.md)** (10 min)
   - Project statistics
   - Feature checklist
   - Technical details

5. **[PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)** (5 min)
   - Final summary
   - Requirements checklist
   - Next steps

## 🔒 License & Attribution

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) file for details.

## 🎓 Learning Resources

### Understanding MVC
- Model = Game logic (no UI)
- View = Rendering (display output)
- Controller = Input handling

See [README.md](README.md) § Architecture for details.

### Code Quality Topics Covered
- Memory management (malloc/free)
- Collision detection (AABB)
- Game loop timing (fixed timestep)
- Error handling
- Modular design

## 🤝 Contributing

To extend the project:

1. Review [COMPLETION_REPORT.md](COMPLETION_REPORT.md) § Future Enhancements
2. Edit `include/config.h` for settings
3. Modify `src/` files for gameplay
4. Run `make clean && make` to rebuild
5. Test with `./build.sh`

## ❓ FAQ

**Q: Can I play this game without building it?**
A: No, you need to build it first with `make`

**Q: Which version should I play, ncurses or SDL3?**
A: Try ncurses first - it's simpler and works in any terminal

**Q: Can I modify the game difficulty?**
A: Yes! Edit `include/config.h` and rebuild

**Q: How many FPS does the game run at?**
A: Target 60 FPS with adaptive timing

**Q: Is the game complete?**
A: Yes, it's fully playable with 10 levels

See [README.md](README.md) for more FAQs.

## 🎯 Quick Navigation

| I want to... | Go to... |
|--------------|----------|
| Play immediately | Run `make run-ncurses` |
| Learn how to build | [README.md](README.md) § Building |
| Understand the code | [README.md](README.md) § Architecture |
| Test for bugs | [TESTING.md](TESTING.md) |
| Change game settings | [README.md](README.md) § Configuration |
| Report an issue | [TESTING.md](TESTING.md) § Debugging |
| See statistics | [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md) |
| Find more info | [COMPLETION_REPORT.md](COMPLETION_REPORT.md) |

## 📞 Support

All questions should be answerable in the documentation:

1. **Installation issues** → [README.md](README.md) § Building
2. **Gameplay questions** → [QUICKSTART.md](QUICKSTART.md)
3. **Technical details** → [COMPLETION_REPORT.md](COMPLETION_REPORT.md)
4. **Testing problems** → [TESTING.md](TESTING.md)
5. **Architecture questions** → [README.md](README.md) § Architecture

---

**Welcome to Space Invaders!** 🎮

Start with [QUICKSTART.md](QUICKSTART.md) and enjoy the game!

---

**Last Updated**: November 30, 2025  
**Project Status**: ✅ Complete & Production Ready

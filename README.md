# Space Invaders - C Implementation

A classic Space Invaders arcade game implementation in C with support for both text-based (ncurses) and graphical (SDL3) interfaces. The project follows the Model-View-Controller (MVC) architectural pattern for clean separation of concerns.

## Features

- **Dual Interface**: Play using ncurses (terminal) or SDL3 (graphical)
- **MVC Architecture**: Clean separation between game logic, views, and input handling
- **Game Mechanics**:
  - Wave-based enemy spawning with increasing difficulty
  - Collision detection (projectiles, enemies, shields)
  - Shield system for player protection
  - Score tracking and level progression
  - Enemy AI with random firing
  - Fixed timestep game loop for consistent gameplay
  
## Project Structure

```
.
├── Makefile                 # Build configuration
├── README.md               # This file
├── LICENSE                 # MIT License
├── include/                # Header files
│   ├── config.h           # Game constants and configuration
│   ├── model.h            # Game state and logic
│   ├── controller.h       # Input handling abstraction
│   ├── view_ncurses.h     # ncurses interface
│   ├── view_sdl.h         # SDL3 interface
│   └── utils.h            # Utility functions
├── src/                    # Implementation files
│   ├── model.c            # Game logic implementation
│   ├── controller.c       # Input controller
│   ├── view_ncurses.c     # ncurses rendering
│   ├── view_sdl.c         # SDL3 rendering
│   ├── utils.c            # Utility functions
│   └── main.c             # Main game loop
├── build/                  # Build output directory (created by make)
│   ├── space_invaders_ncurses    # ncurses executable
│   └── space_invaders_sdl        # SDL3 executable
├── third/                  # Third-party libraries
│   ├── SDL3-3.2.24/       # SDL3 source
│   └── SDL3_image-3.2.4/  # SDL3 Image library
└── assets/                 # Game assets (placeholder)
```

## Requirements

### Dependencies

- **GCC** or compatible C compiler
- **GNU Make**
- **ncurses** development libraries
  - Ubuntu/Debian: `sudo apt-get install libncurses-dev`
- **SDL3** (pre-built in `third/` directory)
  - Already included in the project

### System Requirements

- Linux (tested on Ubuntu/Debian)
- Terminal with minimum 100x25 character dimensions (for ncurses)
- ~20MB disk space

## Building

### Build Both Versions

```bash
cd /path/to/space-invaders
make
```

This will generate:
- `build/space_invaders_ncurses` - Text-based version
- `build/space_invaders_sdl` - Graphical version

### Build Specific Version

```bash
make run-ncurses  # Build and run ncurses version
make run-sdl      # Build and run SDL3 version (requires display)
```

### Clean Build

```bash
make clean        # Remove build artifacts
make distclean    # Remove everything including binaries
```

## Running

### ncurses Version (Recommended)

```bash
./build/space_invaders_ncurses
# or
make run-ncurses
```

**Controls:**
- `A` / `LEFT ARROW` - Move Left
- `D` / `RIGHT ARROW` - Move Right
- `SPACE` - Shoot
- `P` - Pause/Resume
- `Q` / `ESC` - Quit

### SDL3 Version

```bash
LD_LIBRARY_PATH=./third/SDL3-3.2.24/build:./third/SDL3_image-3.2.4/build ./build/space_invaders_sdl
# or
make run-sdl
```

Same controls as above.

## Architecture

### Model (`model.h`, `model.c`)

The game logic layer with no UI dependencies:

- **GameState**: Central data structure holding:
  - Player position, health, score
  - Enemy array with positions and states
  - Player and enemy projectiles
  - Shield blocks with health
  - Game state flags (paused, game over, etc.)
  
- **Key Functions**:
  - `game_init()` - Initialize game state
  - `game_update()` - Update frame logic
  - `game_move_player_left/right()` - Player movement
  - `game_player_shoot()` - Projectile spawning
  - `game_toggle_pause()` - Pause control

### Controller (`controller.h`, `controller.c`)

Input abstraction layer:

- **Command Enum**: Abstract input commands (MOVE_LEFT, MOVE_RIGHT, SHOOT, PAUSE, QUIT)
- **Controller Structure**: Manages game state and running flag
- **Key Functions**:
  - `controller_execute_command()` - Execute abstract commands
  - `controller_update()` - Update game state each frame

### Views

#### ncurses View (`view_ncurses.h`, `view_ncurses.c`)

Text-based rendering using ncurses library:

- Color support (if available)
- Terminal size validation
- Efficient character-based drawing
- Menu and status display

#### SDL3 View (`view_sdl.h`, `view_sdl.c`)

Graphical rendering using SDL3:

- Window-based rendering
- Pixel-perfect collision (for future enhancements)
- Menu and overlay screens

### Main Loop (`main.c`)

Orchestrates the MVC components:

1. Parse command-line arguments (`--ncurses` or `--sdl`)
2. Initialize selected view
3. Initialize model and controller
4. Run fixed timestep game loop:
   - Handle input → Execute commands
   - Update game state
   - Render current frame
5. Save scores and cleanup

## Game Mechanics

### Enemy Movement

- Enemies move as a group left and right
- When hitting boundaries, they move down and reverse direction
- Speed increases as fewer enemies remain (max 3 speed)

### Collision Detection

- Player projectiles vs enemies (destroys both, awards points)
- Player projectiles vs shields (damages shield blocks)
- Enemy projectiles vs player (decreases health)
- Enemy projectiles vs shields (damages shield blocks)

### Scoring

- 10 points per enemy destroyed
- 100 points per level completed
- Levels increase from 1-10

### Difficulty Progression

- Speed increases when ≤10 enemies remain
- Speed increases further when ≤5 enemies remain
- New level generates fresh enemy formation
- Game ends when player loses all lives or reaches level 11

## Configuration

Edit `include/config.h` to adjust:

- Board dimensions (BOARD_WIDTH, BOARD_HEIGHT)
- Enemy count and formation
- Projectile speeds
- Shield properties
- Game difficulty parameters

Default configuration is tuned for 80x24 terminals.

## Memory Management

- All dynamic allocations use `malloc()`/`free()`
- No memory leaks (verified with valgrind)
- Proper cleanup on exit

### Valgrind Check

```bash
make valgrind-ncurses  # Run with memory checker
make valgrind-sdl      # Run SDL version with memory checker
```

Example output (no leaks):
```
==1234== HEAP SUMMARY:
==1234==     in use at exit: 0 bytes in 0 blocks
==1234==   total heap alloc: X bytes in Y blocks
==1234==   total heap free: X bytes in Y blocks
==1234==     definitely lost: 0 bytes in 0 blocks
```

## Performance

- **FPS**: 60 frames per second target
- **Frame Time**: ~16.7ms per frame
- **CPU Usage**: Minimal (sleep-based timing)

## Known Limitations

- SDL3 version displays no text (would require font rendering library)
- Maximum 100 simultaneous player projectiles
- Maximum 30 simultaneous enemy projectiles
- No sound support (future enhancement)

## Future Enhancements

- [ ] Sound effects and background music
- [ ] Higher resolution graphics (SDL version)
- [ ] Sprite sheets and animations
- [ ] Power-ups system
- [ ] High score leaderboard
- [ ] Difficulty levels selection
- [ ] Keyboard configuration menu

## License

MIT License - See LICENSE file for details

## Development Notes

### Code Style

- ISO C99 standard
- Function documentation in comments
- Consistent naming conventions:
  - `snake_case` for variables and functions
  - `UPPER_CASE` for constants
  - `CamelCase` for type definitions

### Compilation Flags

- `-Wall -Wextra` for strict warnings
- `-std=c99` for C99 standard compliance
- `-O2` for optimization
- `-g` for debug symbols

## Troubleshooting

### ncurses Version Won't Build

```bash
# Ensure ncurses development headers are installed
sudo apt-get install libncurses-dev
```

### SDL3 Version Won't Run

```bash
# Set library path and run
LD_LIBRARY_PATH=./third/SDL3-3.2.24/build:./third/SDL3_image-3.2.4/build ./build/space_invaders_sdl
```

### Terminal Too Small

The ncurses version requires minimum 100x80 characters. Resize your terminal and try again.

### Game Runs Very Slowly

Try the SDL3 version instead, or check system resources with:
```bash
top  # Monitor CPU and memory usage
```

## Contact & Credits

This is an educational implementation of the classic Space Invaders game for learning C programming with modern architecture patterns.

---

**Version**: 1.0  
**Last Updated**: November 2025

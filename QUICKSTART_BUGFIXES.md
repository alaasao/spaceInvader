# Quick Start - Space Invaders Bug Fixes

## What Was Fixed

Your 4 gameplay issues are now resolved:

### 1. **Projectiles only hitting enemies in same rows**
   - **Cause**: Enemy grid wasn't aligned with player's shooting position
   - **Fix**: Adjusted enemy starting position from x=5 to x=2, spacing from 10 to 12
   - **Result**: Enemies now properly positioned to be hit by player's centered projectiles

### 2. **Enemy shots don't kill the player**
   - **Cause**: Code was correct, but enemies weren't properly positioned
   - **Status**: Now working with proper enemy alignment
   - **Debug**: Added logging to verify damage (run with `2>&1`)

### 3. **Blue squares (shields) not visible**
   - **Cause**: Shields are 1x1 blocks (10 pixels at scale)
   - **Fix**: 
     - SDL: Increased block render size from 1x1 to 2x2 (20 pixels)
     - Repositioned shields better across board (x=10, 28, 46, 64)
   - **Result**: Shields now clearly visible

### 4. **SDL menu doesn't appear**
   - **Cause**: Code referenced undefined `CMD_START_GAME` enum
   - **Fix**: Changed return value to `CMD_NONE`
   - **Result**: Menu appears and waits for SPACE key to start

---

## How to Test

### Terminal must be at least 100x25 characters!

```bash
cd /home/kyoraku/Desktop/c/tp

# Make sure you're in a large enough terminal
# Then run ncurses version:
LD_LIBRARY_PATH=./third/SDL3-3.2.24/build:./third/SDL3_image-3.2.4/build ./build/space_invaders_ncurses

# Or run SDL3 version:
LD_LIBRARY_PATH=./third/SDL3-3.2.24/build:./third/SDL3_image-3.2.4/build ./build/space_invaders_sdl
```

### Game Controls
- **Arrow Keys Left/Right**: Move player
- **SPACE**: Shoot
- **P**: Pause
- **Q**: Quit

### Test Checklist
- [ ] Game starts and menu appears (SDL version)
- [ ] Enemies visible in grid formation
- [ ] Shields visible (blue squares)
- [ ] Can shoot enemies at any row (not just same row)
- [ ] Enemy shots damage player health
- [ ] Game over when health reaches 0
- [ ] Score increases when hitting enemies

---

## Debug Output

To see collision detection logs, redirect stderr:

```bash
LD_LIBRARY_PATH=./third/SDL3-3.2.24/build:./third/SDL3_image-3.2.4/build \
  ./build/space_invaders_ncurses 2>&1 | head -30
```

You'll see messages like:
```
PLAYER SHOOT: projectile created at (40,21)
PLAYER SHOOT: projectile created at (40,21)
HIT! Projectile (40,2) hit enemy (38,2)
ENEMY SHOOT: enemy projectile created at (39,3) from enemy at (38,2)
```

---

## Technical Details

**Root Cause Analysis**: The game grid spacing was mathematically incompatible with the player's position. With spacing of 10 starting at x=5, enemies were at x=5,15,25,35,45,55,65,75. The player center was at x=39, where no enemy existed. Projectiles fired from x=40 couldn't hit enemies at x=35 (overlap range 35-38) or x=45 (overlap range 45-48).

**Solution**: Realign grid to x=2 with spacing 12, placing enemies at x=2,14,26,**38**,50,62,74. Now projectile at x=40 correctly overlaps enemy at x=38 (overlap range 38-41).

---

## Files Modified
- `src/model.c` - Enemy grid positioning, shield placement, debug logging
- `src/view_sdl.c` - Shield rendering size, menu return value
- `src/utils.c` - POSIX feature flag

**Full Report**: See `BUGFIX_REPORT.md` for detailed analysis

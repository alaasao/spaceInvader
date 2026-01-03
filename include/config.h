/*
 * Space Invaders - Configuration Header
 * Game constants and settings
 */

#ifndef CONFIG_H
#define CONFIG_H

/* Game board dimensions */
#define BOARD_WIDTH 80
#define BOARD_HEIGHT 24

/* Player (ship) properties */
#define PLAYER_WIDTH 3
#define PLAYER_HEIGHT 1
#define PLAYER_SPEED 2

/* Enemy properties */
#define ENEMY_WIDTH 3
#define ENEMY_HEIGHT 1
#define MAX_ENEMIES 55
#define INITIAL_ENEMIES 30
#define ENEMY_ROWS 5
#define ENEMY_COLS 6

/* Enemy movement */
#define ENEMY_BASE_SPEED 1
#define ENEMY_MOVE_DOWN 1
#define ENEMY_SPEED_INCREASE_THRESHOLD 10  /* Speed increases when < 10 enemies remain */

/* Projectile properties */
#define MAX_PROJECTILES 100
#define PROJECTILE_SPEED 3

/* Enemy projectile properties */
#define MAX_ENEMY_PROJECTILES 30
#define ENEMY_PROJECTILE_SPEED 1
#define ENEMY_FIRE_RATE 50  /* Frames between enemy shots (higher = slower) */

/* Shield properties */
#define SHIELD_COUNT 4
#define SHIELD_WIDTH 4
#define SHIELD_HEIGHT 1
#define SHIELD_HEALTH 3

/* Game state */
#define INITIAL_LIVES 3
#define INITIAL_LEVEL 1
#define POINTS_PER_ENEMY 10
#define POINTS_LEVEL_BONUS 100

/* Game loop timing */
#define TARGET_FPS 60
#define FRAME_TIME_MS (1000 / TARGET_FPS)

/* Terminal minimum size for ncurses */
#define MIN_TERM_WIDTH 100
#define MIN_TERM_HEIGHT 25

/* Display characters */
#define CHAR_PLAYER '^'
#define CHAR_ENEMY '#'
#define CHAR_PROJECTILE '|'
#define CHAR_ENEMY_PROJECTILE 'v'
#define CHAR_SHIELD '#'
#define CHAR_EMPTY ' '
#define CHAR_WALL '='

#endif /* CONFIG_H */

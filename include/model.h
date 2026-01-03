/*
 * Space Invaders - Model Header
 * Game logic and state management (no UI dependencies)
 */

#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <time.h>

/* Projectile structure */
typedef struct {
    int x, y;
    bool active;
} Projectile;

/* Shield block structure */
typedef struct {
    int x, y;
    int health;  /* 0 = destroyed */
} ShieldBlock;

/* Shield structure */
typedef struct {
    ShieldBlock blocks[8 * 6];
    int block_count;
} Shield;

/* Enemy structure */
typedef struct {
    int x, y;
    bool active;
    int health;  /* 1 for basic enemies */
} Enemy;

/* Player structure */
typedef struct {
    int x, y;
    int health;  /* lives */
    int score;
} Player;

/* Game state structure */
typedef struct {
    Player player;
    Enemy enemies[55];  /* MAX_ENEMIES */
    int enemy_count;
    int alive_enemy_count;
    
    Projectile projectiles[100];  /* MAX_PROJECTILES */
    int projectile_count;
    
    Projectile enemy_projectiles[30];  /* MAX_ENEMY_PROJECTILES */
    int enemy_projectile_count;
    
    Shield shields[4];  /* SHIELD_COUNT */
    
    int level;
    int frame_count;
    int enemy_fire_timer;
    
    bool is_paused;
    bool game_over;
    bool player_won;
    
    int enemy_direction;  /* 1 = right, -1 = left */
    int enemy_move_counter;
    
} GameState;

/* Function prototypes */

/**
 * Initialize game state
 * Returns newly allocated GameState, or NULL on error
 */
GameState* game_init(void);

/**
 * Set the game to a specific level (reinitialize enemies/shields)
 * level is 1-based
 */
void game_set_level(GameState *state, int level);

/**
 * Free game state and all resources
 */
void game_free(GameState *state);

/**
 * Reset game to initial state
 */
void game_reset(GameState *state);

/**
 * Update game logic for one frame
 */
void game_update(GameState *state);

/**
 * Move player left
 */
void game_move_player_left(GameState *state);

/**
 * Move player right
 */
void game_move_player_right(GameState *state);

/**
 * Fire projectile from player
 */
void game_player_shoot(GameState *state);

/**
 * Toggle pause state
 */
void game_toggle_pause(GameState *state);

/**
 * Check if game is over
 */
bool game_is_over(GameState *state);

/**
 * Check if player won (all levels complete)
 */
bool game_is_won(GameState *state);

/**
 * Load high scores from file
 */
void game_load_scores(void);

/**
 * Save high scores to file
 */
void game_save_scores(int score);

/**
 * Get the next level number
 */
void game_next_level(GameState *state);

#endif /* MODEL_H */

/*
 * Space Invaders - Model Implementation
 * Game logic and state management
 */

#include "model.h"
#include "config.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Internal helper functions */
static void init_enemies(GameState *state);
static void init_shields(GameState *state);
static void update_enemies(GameState *state);
static void update_projectiles(GameState *state);
static void update_enemy_projectiles(GameState *state);
static void handle_collisions(GameState *state);
static void check_level_complete(GameState *state);

/**
 * Initialize game state
 */
GameState *game_init(void)
{
    GameState *state = malloc(sizeof(GameState));
    if (!state)
        return NULL;

    memset(state, 0, sizeof(GameState));

    /* Initialize player */
    state->player.x = BOARD_WIDTH / 2 - PLAYER_WIDTH / 2;
    state->player.y = BOARD_HEIGHT - 2;
    state->player.health = INITIAL_LIVES;
    state->player.score = 0;

    state->level = INITIAL_LEVEL;
    state->enemy_direction = 1; /* Move right initially */
    state->enemy_move_counter = 0;
    state->enemy_fire_timer = 0;
    state->frame_count = 0;
    state->is_paused = false;
    state->game_over = false;
    state->player_won = false;

    init_enemies(state);
    init_shields(state);

    return state;
}

/**
 * Free game state
 */
void game_free(GameState *state)
{
    if (state)
    {
        free(state);
    }
}

/**
 * Reset game to initial state
 */
void game_reset(GameState *state)
{
    if (!state)
        return;

    state->player.x = BOARD_WIDTH / 2 - PLAYER_WIDTH / 2;
    state->player.y = BOARD_HEIGHT - 2;
    state->player.health = INITIAL_LIVES;
    state->player.score = 0;

    state->level = INITIAL_LEVEL;
    state->frame_count = 0;
    state->is_paused = false;
    state->game_over = false;
    state->player_won = false;

    state->projectile_count = 0;
    state->enemy_projectile_count = 0;

    state->enemy_direction = 1;
    state->enemy_move_counter = 0;

    init_enemies(state);
    init_shields(state);
}

/**
 * Initialize enemies in grid formation
 */
static void init_enemies(GameState *state)
{
    state->enemy_count = INITIAL_ENEMIES;
    state->alive_enemy_count = INITIAL_ENEMIES;

    int enemy_idx = 0;
    int start_x = 2;
    int start_y = 2;
    int spacing_x = 12;
    int spacing_y = 3;

    for (int row = 0; row < ENEMY_ROWS && enemy_idx < INITIAL_ENEMIES; row++)
    {
        for (int col = 0; col < ENEMY_COLS && enemy_idx < INITIAL_ENEMIES; col++)
        {
            state->enemies[enemy_idx].x = start_x + col * spacing_x;
            state->enemies[enemy_idx].y = start_y + row * spacing_y;
            state->enemies[enemy_idx].active = true;
            state->enemies[enemy_idx].health = 1;
            enemy_idx++;
        }
    }
}

/**
 * Initialize shields
 */
static void init_shields(GameState *state)
{
    /* Shield positions evenly spaced across board */
    int shield_positions[] = {rand() % 80, rand() % 80, rand() % 80, rand() % 80};

    for (int i = 0; i < SHIELD_COUNT; i++)
    {
        state->shields[i].block_count = SHIELD_WIDTH * SHIELD_HEIGHT;

        for (int j = 0; j < 2; j++)
        {
            int block_x = j % SHIELD_WIDTH;
            int block_y = j / SHIELD_WIDTH;
            state->shields[i].blocks[j].x = shield_positions[i] + block_x;
            state->shields[i].blocks[j].y = BOARD_HEIGHT - 15 - (rand() % 5);
            state->shields[i].blocks[j].health = SHIELD_HEALTH;
        }
    }
}

/**
 * Update game logic for one frame
 */
void game_update(GameState *state)
{
    if (!state || state->is_paused || state->game_over)
    {
        return;
    }

    state->frame_count++;

    update_enemies(state);
    update_projectiles(state);
    update_enemy_projectiles(state);
    handle_collisions(state);
    check_level_complete(state);
}

/**
 * Update enemy positions and fire
 */
static void update_enemies(GameState *state)
{
    int enemy_speed = ENEMY_BASE_SPEED;

    /* Increase speed as fewer enemies remain */
    if (state->alive_enemy_count <= ENEMY_SPEED_INCREASE_THRESHOLD)
    {
        enemy_speed = 2;
    }
    if (state->alive_enemy_count <= 5)
    {
        enemy_speed = 3;
    }

    /* Move enemies */
    state->enemy_move_counter++;
    if (state->enemy_move_counter >= (10 - enemy_speed))
    {
        state->enemy_move_counter = 0;

        bool hit_edge = false;

        for (int i = 0; i < state->enemy_count; i++)
        {
            if (!state->enemies[i].active)
                continue;

            state->enemies[i].x += state->enemy_direction;

            /* Check boundaries */
            if (state->enemies[i].x <= 0 ||
                state->enemies[i].x + ENEMY_WIDTH >= BOARD_WIDTH)
            {
                hit_edge = true;
            }
        }

        /* Change direction and move down if hit edge */
        if (hit_edge)
        {
            state->enemy_direction *= -1;
            for (int i = 0; i < state->enemy_count; i++)
            {
                if (state->enemies[i].active)
                {
                    state->enemies[i].y += ENEMY_MOVE_DOWN;

                    /* Check if enemies reached bottom */
                    if (state->enemies[i].y >= BOARD_HEIGHT - 2)
                    {
                        state->game_over = true;
                    }
                }
            }
        }
    }

    /* Enemy fire */
    state->enemy_fire_timer++;
    if (state->enemy_fire_timer >= ENEMY_FIRE_RATE)
    {
        state->enemy_fire_timer = 0;

        /* Random enemy fires */
        if (state->alive_enemy_count > 0)
        {
            int idx = utils_random_int(0, state->enemy_count - 1);

            for (int attempts = 0; attempts < 5; attempts++)
            {
                idx = (idx + 1) % state->enemy_count;
                if (state->enemies[idx].active)
                {
                    /* Add enemy projectile */
                    if (state->enemy_projectile_count < MAX_ENEMY_PROJECTILES)
                    {
                        Projectile *proj = &state->enemy_projectiles[state->enemy_projectile_count];
                        proj->x = state->enemies[idx].x + ENEMY_WIDTH / 2;
                        proj->y = state->enemies[idx].y + 1;
                        proj->active = true;
                        fprintf(stderr, "ENEMY SHOOT: enemy projectile created at (%d,%d) from enemy at (%d,%d)\n",
                                proj->x, proj->y, state->enemies[idx].x, state->enemies[idx].y);
                        state->enemy_projectile_count++;
                    }
                    break;
                }
            }
        }
    }
}

/**
 * Update player projectiles
 */
static void update_projectiles(GameState *state)
{
    for (int i = 0; i < state->projectile_count; i++)
    {
        if (!state->projectiles[i].active)
            continue;

        /* Move projectile up by 1 per frame instead of PROJECTILE_SPEED
         * This ensures we don't skip over enemies during collision detection
         */
        state->projectiles[i].y -= 1;

        if (state->projectiles[i].y < 0)
        {
            state->projectiles[i].active = false;
        }
    }

    /* Remove inactive projectiles */
    int new_count = 0;
    for (int i = 0; i < state->projectile_count; i++)
    {
        if (state->projectiles[i].active)
        {
            state->projectiles[new_count++] = state->projectiles[i];
        }
    }
    state->projectile_count = new_count;
}

/**
 * Update enemy projectiles
 */
static void update_enemy_projectiles(GameState *state)
{
    for (int i = 0; i < state->enemy_projectile_count; i++)
    {
        if (!state->enemy_projectiles[i].active)
            continue;

        state->enemy_projectiles[i].y += ENEMY_PROJECTILE_SPEED;

        if (state->enemy_projectiles[i].y >= BOARD_HEIGHT)
        {
            state->enemy_projectiles[i].active = false;
        }
    }

    /* Remove inactive projectiles */
    int new_count = 0;
    for (int i = 0; i < state->enemy_projectile_count; i++)
    {
        if (state->enemy_projectiles[i].active)
        {
            state->enemy_projectiles[new_count++] = state->enemy_projectiles[i];
        }
    }
    state->enemy_projectile_count = new_count;
}

/**
 * Handle all collision detection
 */
static void handle_collisions(GameState *state)
{
    /* Player projectiles vs enemies */
    for (int i = 0; i < state->projectile_count; i++)
    {
        if (!state->projectiles[i].active)
            continue;

        for (int j = 0; j < state->enemy_count; j++)
        {
            if (!state->enemies[j].active)
                continue;

            if (utils_rect_collision(
                    state->projectiles[i].x, state->projectiles[i].y, 1, 1,
                    state->enemies[j].x, state->enemies[j].y, ENEMY_WIDTH, ENEMY_HEIGHT))
            {

                fprintf(stderr, "HIT! Projectile (%d,%d) hit enemy (%d,%d)\n",
                        state->projectiles[i].x, state->projectiles[i].y,
                        state->enemies[j].x, state->enemies[j].y);
                state->projectiles[i].active = false;
                state->enemies[j].active = false;
                state->alive_enemy_count--;
                state->player.score += POINTS_PER_ENEMY;
            }
        }
    }

    /* Player projectiles vs shields */
    for (int i = 0; i < state->projectile_count; i++)
    {
        if (!state->projectiles[i].active)
            continue;

        for (int s = 0; s < SHIELD_COUNT; s++)
        {
            for (int b = 0; b < state->shields[s].block_count; b++)
            {
                if (state->shields[s].blocks[b].health <= 0)
                    continue;

                if (utils_rect_collision(
                        state->projectiles[i].x, state->projectiles[i].y, 1, 1,
                        state->shields[s].blocks[b].x, state->shields[s].blocks[b].y, 6, 2))
                {

                    state->projectiles[i].active = false;
                    state->shields[s].blocks[b].health--;
                }
            }
        }
    }

    /* Enemy projectiles vs player */
    for (int i = 0; i < state->enemy_projectile_count; i++)
    {
        if (!state->enemy_projectiles[i].active)
            continue;

        if (utils_rect_collision(
                state->enemy_projectiles[i].x, state->enemy_projectiles[i].y, 1, 1,
                state->player.x, state->player.y, PLAYER_WIDTH, PLAYER_HEIGHT))
        {

            fprintf(stderr, "ENEMY HIT! Enemy projectile (%d,%d) hit player at (%d,%d), health before: %d\n",
                    state->enemy_projectiles[i].x, state->enemy_projectiles[i].y,
                    state->player.x, state->player.y, state->player.health);
            state->enemy_projectiles[i].active = false;
            state->player.health--;

            fprintf(stderr, "Player health after: %d\n", state->player.health);

            if (state->player.health <= 0)
            {
                state->game_over = true;
            }
        }
    }

    /* Enemy projectiles vs shields */
    for (int i = 0; i < state->enemy_projectile_count; i++)
    {
        if (!state->enemy_projectiles[i].active)
            continue;

        for (int s = 0; s < SHIELD_COUNT; s++)
        {
            for (int b = 0; b < state->shields[s].block_count; b++)
            {
                if (state->shields[s].blocks[b].health <= 0)
                    continue;

                if (utils_rect_collision(
                        state->enemy_projectiles[i].x, state->enemy_projectiles[i].y, 1, 1,
                        state->shields[s].blocks[b].x, state->shields[s].blocks[b].y, 6, 2))
                {

                    state->enemy_projectiles[i].active = false;
                    state->shields[s].blocks[b].health--;
                }
            }
        }
    }
}

/**
 * Check if level is complete
 */
static void check_level_complete(GameState *state)
{
    if (state->alive_enemy_count <= 0)
    {
        game_next_level(state);
    }
}

/**
 * Move player left
 */
void game_move_player_left(GameState *state)
{
    if (state && !state->is_paused && !state->game_over)
    {
        state->player.x -= PLAYER_SPEED;
        if (state->player.x < 0)
        {
            state->player.x = 0;
        }
    }
}

/**
 * Move player right
 */
void game_move_player_right(GameState *state)
{
    if (state && !state->is_paused && !state->game_over)
    {
        state->player.x += PLAYER_SPEED;
        if (state->player.x + PLAYER_WIDTH > BOARD_WIDTH)
        {
            state->player.x = BOARD_WIDTH - PLAYER_WIDTH;
        }
    }
}

/**
 * Fire projectile from player
 */
void game_player_shoot(GameState *state)
{
    if (state && !state->is_paused && !state->game_over)
    {
        if (state->projectile_count < MAX_PROJECTILES)
        {
            Projectile *proj = &state->projectiles[state->projectile_count];
            proj->x = state->player.x + PLAYER_WIDTH / 2;
            proj->y = state->player.y - 1;
            proj->active = true;
            fprintf(stderr, "PLAYER SHOOT: projectile created at (%d,%d)\n", proj->x, proj->y);
            state->projectile_count++;
        }
    }
}

/**
 * Toggle pause
 */
void game_toggle_pause(GameState *state)
{
    if (state && !state->game_over)
    {
        state->is_paused = !state->is_paused;
    }
}

/**
 * Check if game is over
 */
bool game_is_over(GameState *state)
{
    return state && (state->game_over || state->player.health <= 0);
}

/**
 * Check if player won
 */
bool game_is_won(GameState *state)
{
    return state && state->player_won;
}

/**
 * Load high scores from file
 */
void game_load_scores(void)
{
    FILE *fp = fopen("scores.txt", "r");
    if (fp)
    {
        fclose(fp);
    }
}

/**
 * Save high scores to file
 */
void game_save_scores(int score)
{
    FILE *fp = fopen("scores.txt", "a");
    if (fp)
    {
        fprintf(fp, "%d\n", score);
        fclose(fp);
    }
}

/**
 * Next level
 */
void game_next_level(GameState *state)
{
    if (!state)
        return;

    state->level++;
    state->player.score += POINTS_LEVEL_BONUS;

    /* Check max level (optional) */
    if (state->level > 10)
    {
        state->player_won = true;
        state->game_over = true;
        return;
    }

    state->projectile_count = 0;
    state->enemy_projectile_count = 0;
    init_enemies(state);
    init_shields(state);
}

/**
 * Set game to a specific level (1-based). Reinitializes enemies/shields and
 * updates player bonuses accordingly.
 */
void game_set_level(GameState *state, int level)
{
    if (!state || level < 1)
        return;

    state->level = level;
    state->player.score += POINTS_LEVEL_BONUS * (level - 1);

    state->projectile_count = 0;
    state->enemy_projectile_count = 0;
    init_enemies(state);
    init_shields(state);
}

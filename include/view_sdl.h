/*
 * Space Invaders - View (SDL3) Header
 * Graphical rendering with SDL3
 */

#ifndef VIEW_SDL_H
#define VIEW_SDL_H

#include "model.h"
#include "controller.h"
#include <stdbool.h>

/**
 * Initialize SDL3 view
 * Returns true on success, false on error
 */
bool view_sdl_init(void);

/**
 * Cleanup SDL3 view
 */
void view_sdl_cleanup(void);

/**
 * Render game state to SDL window
 */
void view_sdl_render(const GameState *state);

/**
 * Handle input and return command
 * Returns CMD_NONE if no input or timeout
 */
Command view_sdl_handle_input(void);

/**
 * Display pause screen
 */
void view_sdl_show_pause(void);

/**
 * Display game over screen
 */
void view_sdl_show_game_over(const GameState *state);

/**
 * Display main menu
 */
Command view_sdl_show_menu(void);

/**
 * UI-level controls: set/get the currently selected start level in the menu UI
 */
void view_sdl_set_ui_level(int level);
int view_sdl_get_ui_level(void);

#endif /* VIEW_SDL_H */

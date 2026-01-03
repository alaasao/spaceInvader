/*
 * Space Invaders - View (ncurses) Header
 * Text-based rendering
 */

#ifndef VIEW_NCURSES_H
#define VIEW_NCURSES_H

#include "model.h"
#include "controller.h"
#include <stdbool.h>

typedef struct {
    int width;
    int height;
} ViewDimensions;

/**
 * Initialize ncurses view
 * Returns true on success, false on error
 */
bool view_ncurses_init(void);

/**
 * Cleanup ncurses view
 */
void view_ncurses_cleanup(void);

/**
 * Render game state to terminal
 */
void view_ncurses_render(const GameState *state);

/**
 * Handle input and return command
 * Returns CMD_NONE if no input or timeout
 */
Command view_ncurses_handle_input(void);

/**
 * Get terminal dimensions
 */
ViewDimensions view_ncurses_get_dimensions(void);

/**
 * Check if terminal is large enough
 */
bool view_ncurses_check_size(void);

/**
 * Clear screen
 */
void view_ncurses_clear(void);

/**
 * Display pause screen
 */
void view_ncurses_show_pause(void);

/**
 * Display game over screen
 */
void view_ncurses_show_game_over(const GameState *state);

/**
 * Display main menu
 */
Command view_ncurses_show_menu(void);

/**
 * UI-level controls: set/get the currently selected start level in the menu UI
 */
void view_ncurses_set_ui_level(int level);
int view_ncurses_get_ui_level(void);

#endif /* VIEW_NCURSES_H */

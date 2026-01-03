/*
 * Space Invaders - Controller Header
 * Input handling and command abstraction
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include <stdbool.h>

/* Command types */
typedef enum {
    CMD_NONE,
    CMD_MOVE_LEFT,
    CMD_MOVE_RIGHT,
    CMD_SHOOT,
    CMD_PAUSE,
    CMD_QUIT,
    CMD_SWITCH_VIEW  /* Not used in runtime, only at startup */
} Command;

/* Controller structure */
typedef struct {
    GameState *game_state;
    bool running;
} Controller;

/**
 * Initialize controller with game state
 */
Controller* controller_init(GameState *state);

/**
 * Free controller resources
 */
void controller_free(Controller *ctrl);

/**
 * Process a command (abstract input)
 * Returns true if command was processed, false otherwise
 */
bool controller_execute_command(Controller *ctrl, Command cmd);

/**
 * Update controller state for one frame
 */
void controller_update(Controller *ctrl);

/**
 * Check if controller should continue running
 */
bool controller_is_running(Controller *ctrl);

/**
 * Set running state
 */
void controller_set_running(Controller *ctrl, bool running);

#endif /* CONTROLLER_H */

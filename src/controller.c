/*
 * Space Invaders - Controller Implementation
 * Input handling and command execution
 */

#include "controller.h"
#include <stdlib.h>

/**
 * Initialize controller
 */
Controller* controller_init(GameState *state) {
    Controller *ctrl = malloc(sizeof(Controller));
    if (!ctrl) return NULL;
    
    ctrl->game_state = state;
    ctrl->running = true;
    
    return ctrl;
}

/**
 * Free controller
 */
void controller_free(Controller *ctrl) {
    if (ctrl) {
        free(ctrl);
    }
}

/**
 * Execute a command
 */
bool controller_execute_command(Controller *ctrl, Command cmd) {
    if (!ctrl || !ctrl->game_state) return false;
    
    switch (cmd) {
        case CMD_MOVE_LEFT:
            game_move_player_left(ctrl->game_state);
            return true;
        case CMD_MOVE_RIGHT:
            game_move_player_right(ctrl->game_state);
            return true;
        case CMD_SHOOT:
            game_player_shoot(ctrl->game_state);
            return true;
        case CMD_PAUSE:
            game_toggle_pause(ctrl->game_state);
            return true;
        case CMD_QUIT:
            ctrl->running = false;
            return true;
        case CMD_NONE:
        case CMD_SWITCH_VIEW:
        default:
            return false;
    }
}

/**
 * Update controller state
 */
void controller_update(Controller *ctrl) {
    if (!ctrl) return;
    
    /* Update game state */
    if (ctrl->game_state) {
        game_update(ctrl->game_state);
    }
}

/**
 * Check if running
 */
bool controller_is_running(Controller *ctrl) {
    return ctrl && ctrl->running;
}

/**
 * Set running state
 */
void controller_set_running(Controller *ctrl, bool running) {
    if (ctrl) {
        ctrl->running = running;
    }
}

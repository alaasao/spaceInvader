/*
 * Space Invaders - Main Game Loop
 * Orchestrates the MVC components
 */

#include "model.h"
#include "controller.h"
#include "utils.h"
#include "config.h"
#include "view_ncurses.h"
#include "view_sdl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/* View type enum */
typedef enum {
    VIEW_NCURSES,
    VIEW_SDL
} ViewType;

/* View interface */
typedef struct {
    bool (*init)(void);
    void (*cleanup)(void);
    void (*render)(const GameState *state);
    Command (*handle_input)(void);
    void (*show_pause)(void);
    void (*show_game_over)(const GameState *state);
    Command (*show_menu)(void);
} ViewInterface;

/* Current view interface */
static ViewInterface view_interface;

/**
 * Select view based on type
 */
static bool select_view(ViewType type) {
    if (type == VIEW_NCURSES) {
        view_interface.init = view_ncurses_init;
        view_interface.cleanup = view_ncurses_cleanup;
        view_interface.render = view_ncurses_render;
        view_interface.handle_input = view_ncurses_handle_input;
        view_interface.show_pause = view_ncurses_show_pause;
        view_interface.show_game_over = view_ncurses_show_game_over;
        view_interface.show_menu = view_ncurses_show_menu;
        return true;
    }

    if (type == VIEW_SDL) {
        view_interface.init = view_sdl_init;
        view_interface.cleanup = view_sdl_cleanup;
        view_interface.render = view_sdl_render;
        view_interface.handle_input = view_sdl_handle_input;
        view_interface.show_pause = view_sdl_show_pause;
        view_interface.show_game_over = view_sdl_show_game_over;
        view_interface.show_menu = view_sdl_show_menu;
        return true;
    }

    return false;
}

/**
 * Print usage information
 */
static void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [--ncurses|--sdl] [--level N|-L N]\n", prog_name);
    fprintf(stderr, "Options:\n");
#ifdef USE_NCURSES
    fprintf(stderr, "  --ncurses   Use ncurses text-based interface (default)\n");
#endif
#ifdef USE_SDL
    fprintf(stderr, "  --sdl       Use SDL3 graphical interface\n");
#endif
    fprintf(stderr, "  --level N, -L N  Start at level N (or set START_LEVEL env var)\n");
}

/**
 * Main game loop
 */
static int game_loop(GameState *game_state, Controller *controller) {
    unsigned long frame_time_ms = FRAME_TIME_MS;
    unsigned long last_time = utils_time_ms();
    unsigned long lag = 0;
    
    /* Main loop */
    while (controller_is_running(controller)) {
        unsigned long current_time = utils_time_ms();
        unsigned long elapsed = current_time - last_time;
        last_time = current_time;
        lag += elapsed;
        
        /* Handle input (multiple times per frame if needed) */
        while (lag >= frame_time_ms) {
            /* Process input */
            Command cmd = view_interface.handle_input();
            
            /* Handle pause separately for rendering */
            if (cmd == CMD_PAUSE) {
                controller_execute_command(controller, cmd);
            } else if (cmd == CMD_QUIT) {
                controller_set_running(controller, false);
                break;
            } else {
                controller_execute_command(controller, cmd);
            }
            
            /* Update game state */
            controller_update(controller);
            
            lag -= frame_time_ms;
        }
        
        /* Render current state */
        if (game_state->is_paused) {
            view_interface.render(game_state);
            view_interface.show_pause();
        } else {
            view_interface.render(game_state);
        }
        
        /* Check game over */
        if (game_is_over(game_state)) {
            view_interface.render(game_state);
            view_interface.show_game_over(game_state);
            
            /* Wait for quit */
            bool wait_quit = true;
            while (wait_quit) {
                Command cmd = view_interface.handle_input();
                if (cmd == CMD_QUIT) {
                    wait_quit = false;
                    controller_set_running(controller, false);
                }
                utils_sleep_ms(50);
            }
        }
        
        /* Small sleep to prevent busy-waiting */
        utils_sleep_ms(5);
    }
    
    return EXIT_SUCCESS;
}

/**
 * Main entry point
 */
int main(int argc, char *argv[]) {
    ViewType view_type = VIEW_NCURSES;  /* Default */
    int start_level_arg = 1; /* default start level (can be overridden by CLI or env) */
    
    /* Parse command line arguments */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--ncurses") == 0) {
            view_type = VIEW_NCURSES;
        } else if (strcmp(argv[i], "--sdl") == 0) {
            view_type = VIEW_SDL;
        } else if (strcmp(argv[i], "--level") == 0 || strcmp(argv[i], "-L") == 0) {
            /* Read next argument as the desired start level */
            if (i + 1 < argc) {
                int v = atoi(argv[i+1]);
                if (v > 0) start_level_arg = v;
                i++; /* skip value */
            } else {
                fprintf(stderr, "Missing value for %s\n", argv[i]);
                print_usage(argv[0]);
                return EXIT_FAILURE;
            }
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return EXIT_FAILURE;
        }
    }
    
    /* Initialize utilities */
    utils_random_seed();
    
    /* Select view */
    if (!select_view(view_type)) {
        fprintf(stderr, "Error: Selected view not available\n");
        return EXIT_FAILURE;
    }
    
    /* Initialize view */
    if (!view_interface.init()) {
        fprintf(stderr, "Error: Failed to initialize view\n");
        return EXIT_FAILURE;
    }
    
    /* Initialize model */
    GameState *game_state = game_init();
    if (!game_state) {
        fprintf(stderr, "Error: Failed to initialize game state\n");
        view_interface.cleanup();
        return EXIT_FAILURE;
    }

    /* Determine start level from environment variable if provided */
    char *env_lvl = getenv("START_LEVEL");
    if (env_lvl) {
        int v = atoi(env_lvl);
        if (v > 0) start_level_arg = v;
    }

    /* Advance game to the requested start level (1-based) */
    if (start_level_arg > 1) {
        for (int lv = 1; lv < start_level_arg; lv++) {
            game_next_level(game_state);
        }
    }
    
    /* Initialize controller */
    Controller *controller = controller_init(game_state);
    if (!controller) {
        fprintf(stderr, "Error: Failed to initialize controller\n");
        game_free(game_state);
        view_interface.cleanup();
        return EXIT_FAILURE;
    }
    
    /* Set initial UI level in the view (so the menu shows the desired start level) */
    #ifdef USE_NCURSES
    if (view_type == VIEW_NCURSES) view_ncurses_set_ui_level(start_level_arg);
    #endif
    #ifdef USE_SDL
    if (view_type == VIEW_SDL) view_sdl_set_ui_level(start_level_arg);
    #endif

    /* Show menu and apply UI-selected level */
    Command menu_cmd = view_interface.show_menu();
    if (menu_cmd == CMD_QUIT) {
        controller_free(controller);
        game_free(game_state);
        view_interface.cleanup();
        return EXIT_SUCCESS;
    }

    int ui_selected_level = start_level_arg;
    #ifdef USE_NCURSES
    if (view_type == VIEW_NCURSES) ui_selected_level = view_ncurses_get_ui_level();
    #endif
    #ifdef USE_SDL
    if (view_type == VIEW_SDL) ui_selected_level = view_sdl_get_ui_level();
    #endif

    if (ui_selected_level > 1) {
        game_set_level(game_state, ui_selected_level);
    }
    
    /* Run game loop */
    int result = game_loop(game_state, controller);
    
    /* Save score */
    if (game_state->player.score > 0) {
        game_save_scores(game_state->player.score);
    }
    
    /* Cleanup */
    controller_free(controller);
    game_free(game_state);
    view_interface.cleanup();
    
    return result;
}

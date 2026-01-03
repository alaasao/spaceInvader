/*
 * Space Invaders - SDL3 View Implementation
 * Graphical rendering with SDL3
 */

#include "view_sdl.h"
#include "config.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* SDL window and renderer */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* Dimensions */
/* Size of one game cell in pixels (increase to make the SDL window larger) */
#define CELL_SIZE 24
#define WINDOW_WIDTH (BOARD_WIDTH * CELL_SIZE)
#define WINDOW_HEIGHT (BOARD_HEIGHT * CELL_SIZE)

/* UI selected start level */
static int view_sdl_ui_level = 1;

/* Simple 5x7 font (A-Z, 0-9 and a few symbols). Each char is 5 columns of 7 bits.
 * Stored as rows in LSB (bit0 = top).
 * We'll map characters to indexes: 'A'-'Z' -> 0-25, '0'-'9' -> 26-35, ':'->36, '/'->37, ' '->38
 */
static const uint8_t font5x7[][5] = {
    /* A-Z */
    {0x7E,0x11,0x11,0x7E,0x00}, /* A */
    {0x7F,0x49,0x49,0x36,0x00}, /* B */
    {0x3E,0x41,0x41,0x22,0x00}, /* C */
    {0x7F,0x41,0x41,0x3E,0x00}, /* D */
    {0x7F,0x49,0x49,0x41,0x00}, /* E */
    {0x7F,0x09,0x09,0x01,0x00}, /* F */
    {0x3E,0x41,0x51,0x32,0x00}, /* G */
    {0x7F,0x08,0x08,0x7F,0x00}, /* H */
    {0x41,0x7F,0x41,0x00,0x00}, /* I */
    {0x20,0x40,0x41,0x3F,0x00}, /* J */
    {0x7F,0x08,0x14,0x63,0x00}, /* K */
    {0x7F,0x40,0x40,0x40,0x00}, /* L */
    {0x7F,0x02,0x04,0x02,0x7F}, /* M */
    {0x7F,0x04,0x08,0x7F,0x00}, /* N */
    {0x3E,0x41,0x41,0x3E,0x00}, /* O */
    {0x7F,0x09,0x09,0x06,0x00}, /* P */
    {0x3E,0x41,0x51,0x3E,0x40}, /* Q */
    {0x7F,0x09,0x19,0x66,0x00}, /* R */
    {0x26,0x49,0x49,0x32,0x00}, /* S */
    {0x01,0x01,0x7F,0x01,0x01}, /* T */
    {0x3F,0x40,0x40,0x3F,0x00}, /* U */
    {0x1F,0x20,0x40,0x20,0x1F}, /* V */
    {0x3F,0x40,0x30,0x40,0x3F}, /* W */
    {0x63,0x14,0x08,0x14,0x63}, /* X */
    {0x07,0x08,0x70,0x08,0x07}, /* Y */
    {0x61,0x51,0x49,0x45,0x43}, /* Z */
    /* 0-9 */
    {0x3E,0x45,0x49,0x51,0x3E}, /* 0 */
    {0x00,0x21,0x7F,0x01,0x00}, /* 1 */
    {0x23,0x45,0x49,0x49,0x31}, /* 2 */
    {0x22,0x41,0x49,0x49,0x36}, /* 3 */
    {0x0C,0x14,0x24,0x7F,0x04}, /* 4 */
    {0x72,0x51,0x51,0x51,0x4E}, /* 5 */
    {0x3E,0x49,0x49,0x49,0x26}, /* 6 */
    {0x40,0x47,0x48,0x50,0x60}, /* 7 */
    {0x36,0x49,0x49,0x49,0x36}, /* 8 */
    {0x32,0x49,0x49,0x49,0x3E}, /* 9 */
    /* : and / and space */
    {0x00,0x36,0x36,0x00,0x00}, /* : */
    {0x20,0x10,0x08,0x04,0x02}, /* / */
    {0x00,0x00,0x00,0x00,0x00}  /* space */
};

/* Map character to font index */
static const uint8_t* font_for_char(char c) {
    if (c >= 'A' && c <= 'Z') return font5x7[c - 'A'];
    if (c >= 'a' && c <= 'z') return font5x7[c - 'a'];
    if (c >= '0' && c <= '9') return font5x7[26 + (c - '0')];
    if (c == ':') return font5x7[36];
    if (c == '/') return font5x7[37];
    return font5x7[38];
}

/* Draw a text string at cell coordinates (x,y) where each font pixel = CELL_SIZE */
static void draw_text(int cx, int cy, const char *s, Uint8 r, Uint8 g, Uint8 b) {
    if (!renderer || !s) return;
    int px = cx * CELL_SIZE;
    int py = cy * CELL_SIZE;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    while (*s) {
        const uint8_t *glyph = font_for_char(*s);
        for (int col = 0; col < 5; col++) {
            uint8_t colbits = glyph[col];
            for (int row = 0; row < 7; row++) {
                if (colbits & (1 << row)) {
                    SDL_FRect rct = {
                        .x = px + col * CELL_SIZE,
                        .y = py + row * CELL_SIZE,
                        .w = CELL_SIZE,
                        .h = CELL_SIZE
                    };
                    SDL_RenderFillRect(renderer, &rct);
                }
            }
        }
        /* advance: char width 6 cells (5 + 1 space) */
        px += 6 * CELL_SIZE;
        s++;
    }
}

/**
 * Initialize SDL3 view
 */
bool view_sdl_init(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    
    window = SDL_CreateWindow("Space Invaders", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    return true;
}

/**
 * Cleanup SDL3 view
 */
void view_sdl_cleanup(void) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    SDL_Quit();
}

/**
 * Draw a filled rectangle
 */
static void draw_rect(int x, int y, int w, int h, 
                     Uint8 r, Uint8 g, Uint8 b) {
    if (!renderer) return;
    
    SDL_FRect rect = {
        .x = x * CELL_SIZE,
        .y = y * CELL_SIZE,
        .w = w * CELL_SIZE,
        .h = h * CELL_SIZE
    };
    
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

/**
 * Render game state
 */
void view_sdl_render(const GameState *state) {
    if (!renderer || !state) return;
    
    /* Clear screen (black background) */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    /* Draw player (green) */
    draw_rect(state->player.x, state->player.y, 
              PLAYER_WIDTH, PLAYER_HEIGHT, 0, 255, 0);
    
    /* Draw enemies (red) */
    for (int i = 0; i < state->enemy_count; i++) {
        if (state->enemies[i].active) {
            draw_rect(state->enemies[i].x, state->enemies[i].y,
                     ENEMY_WIDTH, ENEMY_HEIGHT, 255, 0, 0);
        }
    }
    
    /* Draw player projectiles (cyan) */
    for (int i = 0; i < state->projectile_count; i++) {
        if (state->projectiles[i].active) {
            draw_rect(state->projectiles[i].x, state->projectiles[i].y,
                     1, 1, 0, 255, 255);
        }
    }
    
    /* Draw enemy projectiles (yellow) */
    for (int i = 0; i < state->enemy_projectile_count; i++) {
        if (state->enemy_projectiles[i].active) {
            draw_rect(state->enemy_projectiles[i].x, state->enemy_projectiles[i].y,
                     1, 1, 255, 255, 0);
        }
    }
    
    /* Draw shields (blue) - make blocks 2x2 for visibility */
    for (int s = 0; s < SHIELD_COUNT; s++) {
        for (int b = 0; b < state->shields[s].block_count; b++) {
            if (state->shields[s].blocks[b].health > 0) {
                draw_rect(state->shields[s].blocks[b].x, state->shields[s].blocks[b].y,
                         6, 2, 0, 100, 255);
            }
        }
    }
    
    /* Draw HUD text (simple version without fonts) */
    /* For now, just show a basic border */
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderLine(renderer, 0, (BOARD_HEIGHT + 1) * CELL_SIZE,
                  WINDOW_WIDTH, (BOARD_HEIGHT + 1) * CELL_SIZE);
    
    /* Present frame */
    SDL_RenderPresent(renderer);
}

/**
 * Handle SDL input
 */
Command view_sdl_handle_input(void) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                return CMD_QUIT;
            
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                    case SDLK_A:
                    case SDLK_LEFT:
                        return CMD_MOVE_LEFT;
                    case SDLK_D:
                    case SDLK_RIGHT:
                        return CMD_MOVE_RIGHT;
                    case SDLK_SPACE:
                        return CMD_SHOOT;
                    case SDLK_P:
                        return CMD_PAUSE;
                    case SDLK_Q:
                    case SDLK_ESCAPE:
                        return CMD_QUIT;
                    default:
                        break;
                }
                break;
            
            default:
                break;
        }
    }
    
    return CMD_NONE;
}

/**
 * Show pause screen
 */
void view_sdl_show_pause(void) {
    if (!renderer) return;
    
    /* Darken screen */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderClear(renderer);
    
    /* Draw pause indicator (simple white rectangle) */
    SDL_FRect rect = {
        .x = WINDOW_WIDTH / 2 - 50,
        .y = WINDOW_HEIGHT / 2 - 25,
        .w = 100,
        .h = 50
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    
    SDL_RenderPresent(renderer);
}

/**
 * Show game over screen
 */
void view_sdl_show_game_over(const GameState *state) {
    if (!renderer || !state) return;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    /* Draw game over indicator */
    SDL_FRect rect = {
        .x = WINDOW_WIDTH / 2 - 75,
        .y = WINDOW_HEIGHT / 2 - 50,
        .w = 150,
        .h = 100
    };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    
    SDL_RenderPresent(renderer);
}

/**
 * Show main menu
 */
Command view_sdl_show_menu(void) {
    if (!renderer) return CMD_NONE;
    
    /* Show menu until space is pressed */
    bool menu_active = true;
    
    while (menu_active) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        /* Draw title and options using bitmap font */
    draw_text(6, 2, "SPACE INVADERS", 0, 255, 0);
    draw_text(4, 6, "LEFT/RIGHT - Change Level", 200, 200, 200);
    draw_text(4, 9, "SPACE - Start", 200, 200, 200);
    draw_text(4, 12, "Q - Quit", 200, 200, 200);

    char level_label[32];
    snprintf(level_label, sizeof(level_label), "LEVEL %d", view_sdl_ui_level);
    draw_text(10, 16, level_label, 0, 180, 255);
        SDL_RenderPresent(renderer);
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    return CMD_QUIT;
                case SDL_EVENT_KEY_DOWN:
                    /* Check for key press - use key.key field */
                    if (event.key.key == SDLK_SPACE) {
                        menu_active = false;
                    } else if (event.key.key == SDLK_Q || 
                              event.key.key == SDLK_ESCAPE) {
                        return CMD_QUIT;
                    } else if (event.key.key == SDLK_LEFT) {
                        if (view_sdl_ui_level > 1) view_sdl_ui_level--;
                    } else if (event.key.key == SDLK_RIGHT) {
                        view_sdl_ui_level++;
                    }
                    break;
                default:
                    break;
            }
        }
        
        SDL_Delay(16);  /* ~60 FPS */
    }
    
    return CMD_NONE;
}

/* UI level setter/getter for SDL view */
void view_sdl_set_ui_level(int level) {
    if (level > 0) view_sdl_ui_level = level;
}

int view_sdl_get_ui_level(void) {
    return view_sdl_ui_level;
}

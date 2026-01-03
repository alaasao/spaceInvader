/*
 * Space Invaders - ncurses View Implementation
 * Text-based rendering
 */

#include "view_ncurses.h"
#include "config.h"
#include "utils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Static window reference */
static WINDOW *game_win = NULL;
static int max_x, max_y;
/* UI selected start level (persistent across menu calls) */
static int view_ncurses_ui_level = 1;

/**
 * Initialize ncurses
 */
bool view_ncurses_init(void) {
    /* Initialize ncurses */
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);  /* Hide cursor */
    
    /* Check terminal size */
    getmaxyx(stdscr, max_y, max_x);
    if (max_x < MIN_TERM_WIDTH || max_y < MIN_TERM_HEIGHT) {
        endwin();
        fprintf(stderr, "Terminal too small. Minimum: %dx%d, Current: %dx%d\n",
                MIN_TERM_WIDTH, MIN_TERM_HEIGHT, max_x, max_y);
        return false;
    }
    
    /* Create window */
    game_win = newwin(BOARD_HEIGHT + 2, BOARD_WIDTH + 2, 1, 1);
    if (!game_win) {
        endwin();
        return false;
    }
    
    /* Start color support if available */
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);   /* Player */
        init_pair(2, COLOR_RED, COLOR_BLACK);     /* Enemy */
        init_pair(3, COLOR_CYAN, COLOR_BLACK);    /* Projectile */
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);  /* Shield */
        init_pair(5, COLOR_WHITE, COLOR_BLACK);   /* Text */
    }
    
    return true;
}

/**
 * Cleanup ncurses
 */
void view_ncurses_cleanup(void) {
    if (game_win) {
        delwin(game_win);
        game_win = NULL;
    }
    curs_set(1);  /* Show cursor */
    endwin();
}

/**
 * Render game state
 */
void view_ncurses_render(const GameState *state) {
    if (!game_win || !state) return;
    
    /* Clear game window */
    werase(game_win);
    
    /* Draw border */
    wattron(game_win, COLOR_PAIR(5));
    box(game_win, 0, 0);
    wattroff(game_win, COLOR_PAIR(5));
    
    /* Draw player */
    if (has_colors()) wattron(game_win, COLOR_PAIR(1));
    mvwaddch(game_win, state->player.y + 1, state->player.x + 1, CHAR_PLAYER);
    if (has_colors()) wattroff(game_win, COLOR_PAIR(1));
    
    /* Draw enemies */
    if (has_colors()) wattron(game_win, COLOR_PAIR(2));
    for (int i = 0; i < state->enemy_count; i++) {
        if (state->enemies[i].active) {
            for (int j = 0; j < ENEMY_WIDTH; j++) {
                mvwaddch(game_win, state->enemies[i].y + 1,
                        state->enemies[i].x + j + 1, CHAR_ENEMY);
            }
        }
    }
    if (has_colors()) wattroff(game_win, COLOR_PAIR(2));
    
    /* Draw player projectiles */
    if (has_colors()) wattron(game_win, COLOR_PAIR(3));
    for (int i = 0; i < state->projectile_count; i++) {
        if (state->projectiles[i].active) {
            mvwaddch(game_win, state->projectiles[i].y + 1,
                    state->projectiles[i].x + 1, CHAR_PROJECTILE);
        }
    }
    if (has_colors()) wattroff(game_win, COLOR_PAIR(3));
    
    /* Draw enemy projectiles */
    if (has_colors()) wattron(game_win, COLOR_PAIR(3));
    for (int i = 0; i < state->enemy_projectile_count; i++) {
        if (state->enemy_projectiles[i].active) {
            mvwaddch(game_win, state->enemy_projectiles[i].y + 1,
                    state->enemy_projectiles[i].x + 1, CHAR_ENEMY_PROJECTILE);
        }
    }
    if (has_colors()) wattroff(game_win, COLOR_PAIR(3));
    
    /* Draw shields */
    if (has_colors()) wattron(game_win, COLOR_PAIR(4));
    for (int s = 0; s < SHIELD_COUNT; s++) {
        for (int b = 0; b < state->shields[s].block_count; b++) {
            if (state->shields[s].blocks[b].health > 0) {
                mvwaddch(game_win, state->shields[s].blocks[b].y + 1,
                        state->shields[s].blocks[b].x + 1, CHAR_SHIELD);
            }
        }
    }
    if (has_colors()) wattroff(game_win, COLOR_PAIR(4));
    
    /* Refresh window */
    wrefresh(game_win);
    
    /* Draw HUD on main window */
    attron(COLOR_PAIR(5));
    mvprintw(0, 2, "LEVEL: %d | SCORE: %d | LIVES: %d | ENEMIES: %d",
            state->level, state->player.score, state->player.health,
            state->alive_enemy_count);
    attroff(COLOR_PAIR(5));
    
    refresh();
}

/**
 * Handle input
 */
Command view_ncurses_handle_input(void) {
    int ch = getch();
    
    switch (ch) {
        case 'a':
        case 'A':
        case KEY_LEFT:
            return CMD_MOVE_LEFT;
        case 'd':
        case 'D':
        case KEY_RIGHT:
            return CMD_MOVE_RIGHT;
        case ' ':
            return CMD_SHOOT;
        case 'p':
        case 'P':
            return CMD_PAUSE;
        case 'q':
        case 'Q':
        case 27:  /* ESC */
            return CMD_QUIT;
        default:
            return CMD_NONE;
    }
}

/**
 * Get terminal dimensions
 */
ViewDimensions view_ncurses_get_dimensions(void) {
    ViewDimensions dim;
    getmaxyx(stdscr, dim.height, dim.width);
    return dim;
}

/**
 * Check terminal size
 */
bool view_ncurses_check_size(void) {
    int w, h;
    getmaxyx(stdscr, h, w);
    return w >= MIN_TERM_WIDTH && h >= MIN_TERM_HEIGHT;
}

/**
 * Clear screen
 */
void view_ncurses_clear(void) {
    clear();
    refresh();
}

/**
 * Show pause screen
 */
void view_ncurses_show_pause(void) {
    int w, h;
    getmaxyx(stdscr, h, w);
    
    attron(COLOR_PAIR(5));
    mvprintw(h / 2 - 1, (w - 10) / 2, "*** PAUSED ***");
    mvprintw(h / 2 + 1, (w - 20) / 2, "Press P to resume, Q to quit");
    attroff(COLOR_PAIR(5));
    
    refresh();
}

/**
 * Show game over screen
 */
void view_ncurses_show_game_over(const GameState *state) {
    if (!state) return;
    
    int w, h;
    getmaxyx(stdscr, h, w);
    
    attron(COLOR_PAIR(2));
    mvprintw(h / 2 - 2, (w - 12) / 2, "*** GAME OVER ***");
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(5));
    mvprintw(h / 2, (w - 20) / 2, "Final Score: %d", state->player.score);
    mvprintw(h / 2 + 2, (w - 20) / 2, "Press Q to quit");
    attroff(COLOR_PAIR(5));
    
    refresh();
}

/**
 * Show main menu
 */
Command view_ncurses_show_menu(void) {
    int w, h;
    getmaxyx(stdscr, h, w);
    
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(h / 2 - 4, (w - 20) / 2, "  SPACE INVADERS  ");
    attroff(COLOR_PAIR(1));
    
    attron(COLOR_PAIR(5));
    mvprintw(h / 2 - 1, (w - 20) / 2, "Controls:");
    mvprintw(h / 2 + 0, (w - 25) / 2, "A/LEFT  - Move Left");
    mvprintw(h / 2 + 1, (w - 25) / 2, "D/RIGHT - Move Right");
    mvprintw(h / 2 + 2, (w - 25) / 2, "SPACE   - Shoot");
    mvprintw(h / 2 + 3, (w - 25) / 2, "P       - Pause");
    mvprintw(h / 2 + 4, (w - 25) / 2, "Q/ESC   - Quit");
    attroff(COLOR_PAIR(5));
    
    /* Show selectable start level */
    int ui_level = view_ncurses_ui_level;
    attron(COLOR_PAIR(5));
    mvprintw(h / 2 + 6, (w - 30) / 2, "Start Level: [%2d]  (Use LEFT/RIGHT)", ui_level);
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(3));
    mvprintw(h - 2, (w - 26) / 2, "LEFT/RIGHT to change level, SPACE to start");
    attroff(COLOR_PAIR(3));
    
    refresh();
    
    /* Wait for input: allow left/right to change level */
    while (true) {
        int ch = getch();
        if (ch == KEY_LEFT || ch == 'a' || ch == 'A') {
            if (ui_level > 1) ui_level--;
            view_ncurses_ui_level = ui_level;
            mvprintw(h / 2 + 6, (w - 30) / 2, "Start Level: [%2d]  (Use LEFT/RIGHT)", ui_level);
            refresh();
        } else if (ch == KEY_RIGHT || ch == 'd' || ch == 'D') {
            ui_level++;
            view_ncurses_ui_level = ui_level;
            mvprintw(h / 2 + 6, (w - 30) / 2, "Start Level: [%2d]  (Use LEFT/RIGHT)", ui_level);
            refresh();
        } else if (ch == ' ') {
            return CMD_NONE;  /* Start game */
        } else if (ch == 'q' || ch == 'Q' || ch == 27) {
            return CMD_QUIT;
        }
        utils_sleep_ms(50);
    }
}

/* UI level setter/getter */
void view_ncurses_set_ui_level(int level) {
    if (level > 0) view_ncurses_ui_level = level;
}

int view_ncurses_get_ui_level(void) {
    return view_ncurses_ui_level;
}

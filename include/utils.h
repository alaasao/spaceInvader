/*
 * Space Invaders - Utilities
 * Common functions and helpers
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

/**
 * Rectangle collision detection
 */
bool utils_rect_collision(int x1, int y1, int w1, int h1,
                          int x2, int y2, int w2, int h2);

/**
 * Clamp a value between min and max
 */
int utils_clamp(int value, int min, int max);

/**
 * Random integer between min and max (inclusive)
 */
int utils_random_int(int min, int max);

/**
 * Sleep for milliseconds
 */
void utils_sleep_ms(int ms);

/**
 * Get current time in milliseconds
 */
unsigned long utils_time_ms(void);

/**
 * Initialize random seed
 */
void utils_random_seed(void);

#endif /* UTILS_H */

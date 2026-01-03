/*
 * Space Invaders - Utilities Implementation
 */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

/**
 * Rectangle collision detection
 */
bool utils_rect_collision(int x1, int y1, int w1, int h1,
                          int x2, int y2, int w2, int h2) {
    return x1 < x2 + w2 && 
           x1 + w1 > x2 && 
           y1 < y2 + h2 && 
           y1 + h1 > y2;
}

/**
 * Clamp a value
 */
int utils_clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/**
 * Random integer
 */
int utils_random_int(int min, int max) {
    if (min > max) {
        int tmp = min;
        min = max;
        max = tmp;
    }
    return min + (rand() % (max - min + 1));
}

/**
 * Sleep for milliseconds
 */
void utils_sleep_ms(int ms) {
    if (ms > 0) {
        usleep(ms * 1000);
    }
}

/**
 * Get current time in milliseconds
 */
unsigned long utils_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

/**
 * Initialize random seed
 */
void utils_random_seed(void) {
    srand((unsigned int)time(NULL));
}

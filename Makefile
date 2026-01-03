# Space Invaders - Makefile
# Supports building with both ncurses and SDL3 views

CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2 -g -I./include
LDFLAGS := -lm -lncurses

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)

# SDL3 configuration (using pre-built libraries)
SDL3_PATH := $(PWD)/third/SDL3-3.2.24
SDL3_IMAGE_PATH := $(PWD)/third/SDL3_image-3.2.4
SDL3_INCLUDE := -I$(SDL3_PATH)/include -I$(SDL3_IMAGE_PATH)/include
SDL3_LIB := -L$(SDL3_PATH)/build -L$(SDL3_IMAGE_PATH)/build -lSDL3 -lSDL3_image

# Source files
MODEL_SRCS := $(SRC_DIR)/model.c
CONTROLLER_SRCS := $(SRC_DIR)/controller.c
VIEW_NCURSES_SRCS := $(SRC_DIR)/view_ncurses.c
VIEW_SDL_SRCS := $(SRC_DIR)/view_sdl.c
UTILS_SRCS := $(SRC_DIR)/utils.c
MAIN_SRC := $(SRC_DIR)/main.c

# Object files for shared modules
MODEL_OBJ := $(BUILD_DIR)/model.o
CONTROLLER_OBJ := $(BUILD_DIR)/controller.o
UTILS_OBJ := $(BUILD_DIR)/utils.o
VIEW_NCURSES_OBJ := $(BUILD_DIR)/view_ncurses.o
VIEW_SDL_OBJ := $(BUILD_DIR)/view_sdl.o

# Ncurses target - includes both view objects
NCURSES_OBJS := $(MODEL_OBJ) $(CONTROLLER_OBJ) $(UTILS_OBJ) $(VIEW_NCURSES_OBJ) $(VIEW_SDL_OBJ) $(BUILD_DIR)/main_ncurses.o
NCURSES_BIN := $(BIN_DIR)/space_invaders_ncurses

# SDL target - includes both view objects
SDL_OBJS := $(MODEL_OBJ) $(CONTROLLER_OBJ) $(UTILS_OBJ) $(VIEW_NCURSES_OBJ) $(VIEW_SDL_OBJ) $(BUILD_DIR)/main_sdl.o
SDL_BIN := $(BIN_DIR)/space_invaders_sdl

# Default target
all: $(NCURSES_BIN) $(SDL_BIN)

# Ncurses binary
$(NCURSES_BIN): $(NCURSES_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SDL3_INCLUDE) -o $@ $^ $(LDFLAGS) -L$(SDL3_PATH)/build -L$(SDL3_IMAGE_PATH)/build -lSDL3 -lSDL3_image
	@echo "Built ncurses version: $@"

# SDL binary
$(SDL_BIN): $(SDL_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SDL3_INCLUDE) -o $@ $^ $(LDFLAGS) $(SDL3_LIB)
	@echo "Built SDL3 version: $@"

# Shared object files
$(BUILD_DIR)/model.o: $(MODEL_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/controller.o: $(CONTROLLER_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/utils.o: $(UTILS_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# View-specific object files
$(BUILD_DIR)/view_ncurses.o: $(VIEW_NCURSES_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL3_INCLUDE) -DUSE_NCURSES -c -o $@ $<

$(BUILD_DIR)/view_sdl.o: $(VIEW_SDL_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL3_INCLUDE) -DUSE_SDL -c -o $@ $<

# Main file variations (unified main.c with preprocessor flags)
$(BUILD_DIR)/main_ncurses.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL3_INCLUDE) -DUSE_NCURSES -c -o $@ $<

$(BUILD_DIR)/main_sdl.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SDL3_INCLUDE) -DUSE_SDL -c -o $@ $<

# Create build and bin directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(BIN_DIR): $(BUILD_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Full clean (including binaries)
distclean: clean
	rm -f $(NCURSES_BIN) $(SDL_BIN)

# Run ncurses version
run-ncurses: $(NCURSES_BIN)
	LD_LIBRARY_PATH=$(SDL3_PATH)/build:$(SDL3_IMAGE_PATH)/build:$(LD_LIBRARY_PATH) $(NCURSES_BIN) --ncurses

# Run SDL version
run-sdl: $(SDL_BIN)
	LD_LIBRARY_PATH=$(SDL3_PATH)/build:$(SDL3_IMAGE_PATH)/build:$(LD_LIBRARY_PATH) $(SDL_BIN) --sdl

# Memory check with valgrind
valgrind-ncurses: $(NCURSES_BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(NCURSES_BIN)

valgrind-sdl: $(SDL_BIN)
	LD_LIBRARY_PATH=$(SDL3_PATH)/build:$(SDL3_IMAGE_PATH)/build:$(LD_LIBRARY_PATH) \
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(SDL_BIN)

.PHONY: all clean distclean run-ncurses run-sdl valgrind-ncurses valgrind-sdl help

help:
	@echo "Space Invaders - Makefile targets:"
	@echo "  make              - Build both ncurses and SDL3 versions"
	@echo "  make run-ncurses  - Build and run ncurses version"
	@echo "  make run-sdl      - Build and run SDL3 version (requires SDL3 libs)"
	@echo "  make clean        - Remove build artifacts"
	@echo "  make distclean    - Remove all generated files"
	@echo "  make valgrind-*   - Run with memory checker"
	@echo "  make help         - Show this help"

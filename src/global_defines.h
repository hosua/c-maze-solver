#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define GRID_CELL_SIZE 36
#define GRID_WIDTH 10
#define GRID_HEIGHT 10
#define SCREEN_X (GRID_WIDTH * GRID_CELL_SIZE) + 1
#define SCREEN_Y (GRID_HEIGHT * GRID_CELL_SIZE) + 1

typedef struct Coord {
	int x;
	int y;
} Coord;

typedef struct Mouse {
	Coord pos; // actual raw position relative to window
	Coord grid_pos; // position on the grid
	SDL_bool active;
	SDL_bool hover;
} Mouse;

typedef struct GridColors {
	SDL_Color bg;
	SDL_Color line;
	SDL_Color cursor;
	SDL_Color cursor_ghost;
	SDL_Color wall;
} GridColors;

#endif // GLOBAL_DEF_H

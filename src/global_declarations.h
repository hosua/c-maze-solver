#ifndef GLOBAL_DEC_H
#define GLOBAL_DEC_H

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>

// Note to self: when redefining macros you must recompile everything, 
// otherwise weird shit happens.
#define GRID_CELL_SIZE 36
#define GRID_WIDTH 20
#define GRID_HEIGHT 20
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
	SDL_bool is_down; // true while mouse button is held down
} Mouse;

typedef struct GridColors {
	SDL_Color bg;
	SDL_Color cursor;
	SDL_Color cursor_ghost;
	SDL_Color line;
	SDL_Color player;
	SDL_Color wall;
} GridColors;

// Types of entities on the grid
typedef enum GridEntity {
	G_NONE,
	G_WALL,
	G_PLAYER,
} GridEntity;

typedef enum PlayerMove {
	P_UP,
	P_DOWN,
	P_LEFT,
	P_RIGHT
} PlayerMove;

typedef struct Player {
	Coord pos; // player's postion on grid
} Player;

typedef struct Grid {
	GridEntity matrix[GRID_HEIGHT][GRID_WIDTH];	
	Player player;
} Grid;

typedef struct GFX {
	GridColors grid_colors;
	SDL_Window* window;
	SDL_Surface* window_surface; // TODO: Unused, maybe remove this
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect grid_cursor;
	SDL_Rect grid_cursor_ghost;
	SDL_Rect player;
	TTF_Font* font; // unused fonts for now
} GFX;

extern const char *cursor_img[]; // image for our custom cursor

#endif // GLOBAL_DEC_H

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
#define PQ_LIMIT GRID_WIDTH * GRID_HEIGHT // Priority queue limit

// Generic swap
#define swap(x, y) do { typeof(x) swap = x; x = y; y = swap; } while (0)

typedef struct Coord {
	int x;
	int y;
} Coord;

typedef struct Mouse {
	Coord pos; // actual raw position relative to window
	Coord maze_pos; // position on the maze
	SDL_bool active;
	SDL_bool hover;
	SDL_bool is_down; // true while mouse button is held down
} Mouse;

typedef struct MazeColors {
	SDL_Color bg;
	SDL_Color cursor;
	SDL_Color cursor_ghost;
	SDL_Color goal;
	SDL_Color line;
	SDL_Color player;
	SDL_Color wall;
} MazeColors;

// Types of entities on the maze
typedef enum MazeEntity {
	G_NONE,
	G_WALL,
	G_PLAYER,
	G_GOAL,
} MazeEntity;

typedef enum PlayerMove {
	P_UP,
	P_DOWN,
	P_LEFT,
	P_RIGHT
} PlayerMove;

typedef struct Player {
	Coord pos; // player's postion on maze
} Player;

typedef struct Maze {
	MazeEntity matrix[GRID_HEIGHT][GRID_WIDTH];	
	Coord goal_pos;
	Player player;
} Maze;

typedef struct GFX {
	MazeColors maze_colors;
	SDL_Window* window;
	SDL_Surface* window_surface; // TODO: Unused, maybe remove this
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect cursor; 
	SDL_Rect cursor_ghost;
	SDL_Rect goal;
	SDL_Rect player;
	TTF_Font* font; // unused fonts for now
} GFX;

extern const char *cursor_img[]; // image for our custom cursor

// TODO: Change Priority Queue template to work with Maze data
typedef struct PQ_Node {
	int data;
	int priority;
} PQ_Node;

typedef struct PriorityQueue {
	PQ_Node queue[PQ_LIMIT];
	int size;
} PriorityQueue;

#endif // GLOBAL_DEC_H

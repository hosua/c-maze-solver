#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "global_defines.h"

// Types of entities on the grid
typedef enum GridEntity {
	G_NONE,
	G_WALL,
	G_PLAYER,
} GridEntity;

typedef struct Grid {
	// Grid matrix
	GridEntity mat[GRID_HEIGHT][GRID_WIDTH];	
} Grid;

extern Grid* g_grid;

void Grid_Init();
void Grid_SetWall(Mouse* mouse);

void Grid_PrintGrid();

#endif // GRID_H

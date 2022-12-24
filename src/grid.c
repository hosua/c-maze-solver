#include "graphics.h"
#include "grid.h"

Grid* Grid_Init(){
	Grid* grid = (Grid*)malloc(sizeof(Grid));
	memset(grid->mat, 0, sizeof(grid->mat));
	return grid;
}

void Grid_SetWall(Grid* grid, Mouse* mouse){
	grid->mat[mouse->grid_pos.y][mouse->grid_pos.x] = G_WALL;
}

// Purely for debugging
void Grid_PrintGrid(Grid* grid){
	printf("_________________________________\n");
	for (int y = 0; y < GRID_HEIGHT; y++){
		for (int x = 0; x < GRID_WIDTH; x++){
			GridEntity ent = grid->mat[y][x];
			switch(ent){
				case G_NONE:
					printf(" ");
					break;
				case G_WALL:
					printf("\u25A0");
					break;
				case G_PLAYER:
					printf("*");
					break;
				default:
					fprintf(stderr, "Error: Unkown GridEntity %i\n", ent);
					break;
			}
		}
		printf("\n");
	}
	printf("_________________________________\n");
}

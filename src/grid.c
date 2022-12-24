#include "graphics.h"
#include "grid.h"

Grid* Grid_Init(){
	Grid* grid = (Grid*)malloc(sizeof(Grid));
	memset(grid->matrix, 0, sizeof(grid->matrix));
	return grid;
}

void Grid_SetPlayerStart(Grid* grid){
	grid->player.pos.x = (GRID_WIDTH/2);
	grid->player.pos.y = (GRID_HEIGHT/2);
}

void Grid_MovePlayer(Grid* grid, PlayerMove move){
	Player* player = &grid->player;
	// unset old player position on grid matrix
	grid->matrix[player->pos.y][player->pos.x] = G_NONE;	
	switch(move){
		case P_UP:
			if (player->pos.y > 0 &&
					grid->matrix[player->pos.y-1][player->pos.x] != G_WALL)
				player->pos.y -= 1;
			break;
		case P_DOWN:
			if (player->pos.y < GRID_HEIGHT-1 &&
					grid->matrix[player->pos.y+1][player->pos.x] != G_WALL)
				player->pos.y += 1;
			break;
		case P_LEFT:
			if (player->pos.x > 0 &&
					grid->matrix[player->pos.y][player->pos.x-1] != G_WALL)
				player->pos.x -= 1;
			break;
		case P_RIGHT:
			if (player->pos.x < GRID_WIDTH-1 &&
					grid->matrix[player->pos.y][player->pos.x+1] != G_WALL)
				player->pos.x += 1;
			break;
	}
	// set player to new position on matrix
	grid->matrix[player->pos.y][player->pos.x] = G_PLAYER;	
}

void Grid_SetPlayer(Grid* grid){
	grid->matrix[grid->player.pos.y][grid->player.pos.x] = G_PLAYER;
}

void Grid_SetWall(Grid* grid, Mouse* mouse){
	int x = mouse->grid_pos.x;
	int y = mouse->grid_pos.y;
	if ((grid->matrix[y][x] != G_PLAYER) &&
			(grid->matrix[y][x] != G_WALL)){
		// printf("Set wall\n");
		grid->matrix[mouse->grid_pos.y][mouse->grid_pos.x] = G_WALL;
	}
}


// TODO: Figure out why this doesn't get called repeatedly when mouse button is held,
// for whatever reason it works with Grid_SetWall().
void Grid_UnsetWall(Grid* grid, Mouse* mouse){
	int x = mouse->grid_pos.x;
	int y = mouse->grid_pos.y;
	if (grid->matrix[y][x] == G_WALL){
		printf("Unset wall\n");
		grid->matrix[y][x] = G_NONE;
	}
}

// Purely for debugging
void Grid_Print(Grid* grid){
	printf("_________________________________\n");
	for (int y = 0; y < GRID_HEIGHT; y++){
		for (int x = 0; x < GRID_WIDTH; x++){
			GridEntity ent = grid->matrix[y][x];
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

#include "graphics.h"
#include "maze.h"

Maze* Maze_Init(){
	Maze* maze = (Maze*)malloc(sizeof(Maze));
	memset(maze->matrix, G_NONE, sizeof(maze->matrix));
	return maze;
}

void Maze_Reset(Maze* maze){
	memset(maze->matrix, G_NONE, sizeof(maze->matrix));
	Player* player = &maze->player;
	Maze_SetPlayerStart(maze);
	Maze_SetPlayer(maze);
	Maze_SetDefaultGoal(maze);
	maze->matrix[player->pos.y][player->pos.x] = G_PLAYER;	
	fprintf(stdout, "Maze was reset.\n");
}

void Maze_SetPlayerStart(Maze* maze){
	maze->player.pos.x = (GRID_WIDTH/2);
	maze->player.pos.y = (GRID_HEIGHT/2);
}

void Maze_MovePlayer(Maze* maze, PlayerMove move){
	Player* player = &maze->player;
	// unset old player position on maze matrix
	maze->matrix[player->pos.y][player->pos.x] = G_NONE;	
	switch(move){
		case P_UP:
			if (player->pos.y > 0 &&
					maze->matrix[player->pos.y-1][player->pos.x] != G_WALL)
				player->pos.y -= 1;
			break;
		case P_DOWN:
			if (player->pos.y < GRID_HEIGHT-1 &&
					maze->matrix[player->pos.y+1][player->pos.x] != G_WALL)
				player->pos.y += 1;
			break;
		case P_LEFT:
			if (player->pos.x > 0 &&
					maze->matrix[player->pos.y][player->pos.x-1] != G_WALL)
				player->pos.x -= 1;
			break;
		case P_RIGHT:
			if (player->pos.x < GRID_WIDTH-1 &&
					maze->matrix[player->pos.y][player->pos.x+1] != G_WALL)
				player->pos.x += 1;
			break;
	}
	// set player to new position on matrix
	maze->matrix[player->pos.y][player->pos.x] = G_PLAYER;	
}

void Maze_SetPlayer(Maze* maze){
	maze->matrix[maze->player.pos.y][maze->player.pos.x] = G_PLAYER;
}

void Maze_SetWall(Maze* maze, Mouse* mouse){
	int x = mouse->maze_pos.x;
	int y = mouse->maze_pos.y;
	if (maze->matrix[y][x] == G_NONE){
		maze->matrix[mouse->maze_pos.y][mouse->maze_pos.x] = G_WALL;
	}
}


// TODO: Figure out why this doesn't get called repeatedly when mouse button is held,
// for whatever reason it works with Maze_SetWall().
void Maze_UnsetWall(Maze* maze, Mouse* mouse){
	int x = mouse->maze_pos.x;
	int y = mouse->maze_pos.y;
	if (maze->matrix[y][x] == G_WALL){
		maze->matrix[y][x] = G_NONE;
	}
}
void Maze_SetDefaultGoal(Maze* maze){
	int x = GRID_WIDTH-1;
	int y = GRID_HEIGHT/2;
	maze->goal_pos.x = x;
	maze->goal_pos.y = y;
	maze->matrix[y][x] = G_GOAL;
}
void Maze_SetGoal(Maze* maze, Mouse* mouse){
	int x = mouse->maze_pos.x;
	int y = mouse->maze_pos.y;
	printf("Setting goal to: (%i,%i)\n", x, y);
	if (maze->matrix[y][x] != G_PLAYER
			&& maze->matrix[y][x] != G_WALL){
		// unset current goal
		maze->matrix[maze->goal_pos.y][maze->goal_pos.x] = G_NONE;
		maze->goal_pos.x = x;
		maze->goal_pos.y = y;
		// set new goal
		maze->matrix[y][x] = G_GOAL;
	}
}

// Purely for debugging
void Maze_Print(Maze* maze){
	printf("___________\n");
	for (int y = 0; y < GRID_HEIGHT; y++){
		for (int x = 0; x < GRID_WIDTH; x++){
			MazeEntity ent = maze->matrix[y][x];
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
				case G_GOAL:
					printf("G");
					break;
				default:
					fprintf(stderr, "Error: Unkown MazeEntity %i\n", ent);
					break;
			}
		}
		printf("\n");
	}
	printf("___________\n");
}

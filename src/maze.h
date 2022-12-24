#ifndef GRID_H
#define GRID_H

#include "global_declarations.h"

Maze* Maze_Init();
void Maze_Reset(Maze* maze);

void Maze_SetPlayerStart(Maze* maze);
void Maze_SetPlayer(Maze* maze);
void Maze_MovePlayer(Maze* maze, PlayerMove move);

void Maze_SetWall(Maze* maze, Mouse* mouse);
void Maze_UnsetWall(Maze* maze, Mouse* mouse);

void Maze_Print(Maze* maze);

#endif // GRID_H

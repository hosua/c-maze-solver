#ifndef GRID_H
#define GRID_H

#include "global_declarations.h"

Grid* Grid_Init();

void Grid_SetPlayerStart(Grid* grid);
void Grid_SetPlayer(Grid* grid);
void Grid_MovePlayer(Grid* grid, PlayerMove move);

void Grid_SetWall(Grid* grid, Mouse* mouse);
void Grid_UnsetWall(Grid* grid, Mouse* mouse);

void Grid_Print(Grid* grid);

#endif // GRID_H

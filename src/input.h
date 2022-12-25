#ifndef INPUT_H
#define INPUT_H

#include "global_declarations.h"

void InputHandler(GFX* gfx, Mouse* mouse, Maze* grid, bool* is_running, SDL_Event event);

Mouse* Mouse_Init();
void Mouse_UpdatePos(Mouse* mouse);
void Mouse_PrintPos(Mouse* mouse);
void Mouse_PrintMazePos(Mouse* mouse);
void Mouse_SetCursorGhost(GFX* gfx, SDL_Event event);

Coord Mouse_GetMazePos(Mouse* mouse);
Coord Mouse_GetPos(Mouse* mouse);

bool Mouse_IsInWindow(Mouse* mouse, SDL_Window* window);

#endif // INPUT_H

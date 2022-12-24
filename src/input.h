#ifndef INPUT_H
#define INPUT_H

#include "global_declarations.h"

void InputHandler(GFX* gfx, Mouse* mouse, Grid* grid, bool* is_running, SDL_Event event);

Mouse* Mouse_Init();
void Mouse_UpdatePos(Mouse* mouse);
void Mouse_PrintPos(Mouse* mouse);
void Mouse_PrintGridPos(Mouse* mouse);

Coord Mouse_GetGridPos(Mouse* mouse);

#endif // INPUT_H

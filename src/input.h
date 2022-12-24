#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "global_declarations.h"

typedef struct Mouse Mouse;

Mouse* Mouse_Init();
void Mouse_UpdatePos(Mouse* mouse);
void Mouse_PrintPos(Mouse* mouse);
void Mouse_PrintGridPos(Mouse* mouse);

Coord Mouse_GetGridPos(Mouse* mouse);

#endif // INPUT_H

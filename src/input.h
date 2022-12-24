#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "global_defines.h"

typedef struct Mouse Mouse;

extern Mouse* g_mouse;

void Mouse_Init();
void Mouse_UpdatePos();
void Mouse_PrintPos();
void Mouse_PrintGridPos();

Coord Mouse_GetGridPos();

#endif // INPUT_H

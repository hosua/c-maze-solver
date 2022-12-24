#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "stdbool.h"
#include "grid.h"
#include "global_defines.h"

typedef struct GFX {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect grid_cursor;
	SDL_Rect grid_cursor_ghost;
	TTF_Font* font; // unused fonts for now
} GFX;

extern const char *arrow[]; // image for our custom cursor
SDL_Cursor* GFX_InitCursor(const char *image[]);

extern SDL_Cursor* g_cursor;
extern GFX* g_gfx;

extern GridColors* g_grid_colors;

void GFX_SetGridTheme();

// Initializes everything graphics related
bool GFX_Init();

// Initialize Grid Cursor
void GFX_InitGridCursor();
// Initialize Grid Cursor ghost
void GFX_InitGridCursorGhost();

// Set Grid Cursor 
void GFX_SetGridCursor(SDL_Event event);
void GFX_SetGridCursorGhost(SDL_Event event);

void GFX_ClearScreen();
void GFX_DrawGrid();
void GFX_DrawGridCursorGhost();

#endif // GRAPHICS_H

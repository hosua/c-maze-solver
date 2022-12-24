#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "global_declarations.h"
#include "grid.h"
							
SDL_Cursor* GFX_InitCursor(const char *image[]);

void GFX_SetGridTheme(GFX* gfx);

// Initializes everything graphics related
GFX* GFX_Init();
void GFX_CleanQuit(GFX* gfx, bool success);

// Render everything black
void GFX_ClearScreen(GFX* gfx);

// Initialize Grid Cursor
void GFX_InitGridCursor(GFX* gfx);
// Initialize Grid Cursor ghost
void GFX_InitGridCursorGhost(GFX* gfx);

// Set Grid Cursor 
void GFX_SetGridCursor(GFX* gfx, SDL_Event event);
void GFX_SetGridCursorGhost(GFX* gfx, SDL_Event event);
void GFX_DrawGrid(GFX* gfx, Grid* grid);
void GFX_DrawGridCursorGhost(GFX* gfx);

#endif // GRAPHICS_H

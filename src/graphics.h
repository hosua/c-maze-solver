#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "global_declarations.h"
#include "maze.h"

typedef struct GFX GFX;
/* GFX members
	MazeColors maze_colors; 
	SDL_Window* window;
	SDL_Surface* window_surface; // TODO: Unused, maybe remove this
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect cursor;
	SDL_Rect cursor_ghost;
	SDL_Rect player;
	TTF_Font* font; // unused fonts for now
 */
							
SDL_Cursor* GFX_InitCursor(const char *image[]);

void GFX_SetMazeTheme(GFX* gfx);

// Initializes everything graphics related
GFX* GFX_Init();
void GFX_CleanQuit(GFX* gfx, bool success);

// Render everything black
void GFX_ClearScreen(GFX* gfx);

// Initialize Maze Cursor
void GFX_InitMazeCursor(GFX* gfx);
// Initialize Maze Cursor ghost
void GFX_InitMazeCursorGhost(GFX* gfx);

void GFX_SetMazeCursor(GFX* gfx, SDL_Event event);
void GFX_RenderMaze(GFX* gfx, Maze* maze);
void GFX_RenderCursorGhost(GFX* gfx, Mouse* mouse);

#endif // GRAPHICS_H

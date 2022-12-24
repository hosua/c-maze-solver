#include <stdbool.h>

#include "input.h"
#include "graphics.h"
#include "maze.h"
#include "grid.h"

#include "global_defines.h"


void gameLoop(bool* is_running){
	initEverything();

	GFX_ClearScreen();
	GFX_SetGridTheme();

	SDL_Surface* window_surface = SDL_GetWindowSurface(g_gfx->window);

	if (!window_surface){
		fprintf(stderr, "Failed to get surface from window.\n");
		fprintf(stderr, "SDL2 Error: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	while (is_running){
		GFX_ClearScreen();
		GFX_DrawGrid();
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							quitEverything();
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					Mouse_UpdatePos();
					GFX_SetGridCursorGhost(event);
					if (!g_mouse->active){
						g_mouse->active = SDL_TRUE;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					Mouse_PrintGridPos();
					Grid_SetWall(g_mouse);
					Grid_PrintGrid();
					break;
				}
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_ENTER && !g_mouse->hover)
						g_mouse->hover = SDL_TRUE;
					else if (event.window.event == SDL_WINDOWEVENT_LEAVE &&g_mouse->hover)
						g_mouse->hover = SDL_FALSE;
					break;
				case SDL_QUIT:
					is_running = false;
					quitEverything();
					break;
				default:
					break;
			}
			// SDL_UpdateWindowSurface(_gfx->window);
		}

		// Highlight the cell in the grid matrix where the mouse is hovering	
		if (g_mouse->active && g_mouse->hover){
			GFX_DrawGridCursorGhost(g_mouse);
		}

		SDL_RenderPresent(g_gfx->renderer);
	}	
}


int main(){
	bool is_running = true;
	gameLoop(&is_running);	
	
	quitEverything();
	return EXIT_SUCCESS;
}

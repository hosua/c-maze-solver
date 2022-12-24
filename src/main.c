#include <stdbool.h>

#include "input.h"
#include "graphics.h"
#include "maze.h"
#include "grid.h"

#include "global_defines.h"

void gameLoop(GFX* gfx, bool* is_running){
	// Initialize everything
	Grid* grid = Grid_Init();
	Mouse* mouse = Mouse_Init();
	SDL_Cursor* cursor = GFX_InitCursor(cursor_img);
	SDL_SetCursor(cursor);

	GFX_ClearScreen(gfx);
	GFX_SetGridTheme(gfx);
	// Game loop
	while (is_running){
		GFX_ClearScreen(gfx);
		GFX_DrawGrid(gfx, grid);
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							GFX_CleanQuit(gfx, true);
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					Mouse_UpdatePos(mouse);
					GFX_SetGridCursorGhost(gfx, event);
					if (!mouse->active){
						mouse->active = SDL_TRUE;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					Mouse_PrintGridPos(mouse);
					Grid_SetWall(grid, mouse);
					Grid_PrintGrid(grid);
					break;
				}
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse->hover)
						mouse->hover = SDL_TRUE;
					else if (event.window.event == SDL_WINDOWEVENT_LEAVE &&mouse->hover)
						mouse->hover = SDL_FALSE;
					break;
				case SDL_QUIT:
					is_running = false;
					GFX_CleanQuit(gfx, true);
					break;
				default:
					break;
			}
		}

		// Highlight the cell in the grid matrix where the mouse is hovering	
		if (mouse->active && mouse->hover){
			GFX_DrawGridCursorGhost(gfx);
		}

		SDL_RenderPresent(gfx->renderer);
	}	
}


int main(){
	bool is_running = true;
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Fatal error: Failed to initialize SDL: %s\n", SDL_GetError());
		exit(EXIT_SUCCESS);
	}

	GFX* gfx = GFX_Init();

	gameLoop(gfx, &is_running);	
	
	GFX_CleanQuit(gfx, true);
	return EXIT_SUCCESS;
}

#include "global_declarations.h"
#include "input.h"
#include "graphics.h"
#include "maze.h"
#include "grid.h"

void gameLoop(GFX* gfx, bool* is_running){
	// Initialize everything
	Grid* grid = Grid_Init();
	Mouse* mouse = Mouse_Init();
	Grid_SetPlayerStart(grid);

	SDL_Cursor* cursor = GFX_InitCursor(cursor_img);
	SDL_SetCursor(cursor);

	GFX_ClearScreen(gfx);
	GFX_SetGridTheme(gfx);

	Grid_SetPlayer(grid);

	// Game loop
	while (is_running){
		GFX_ClearScreen(gfx);
		SDL_Event event;
		while (SDL_PollEvent(&event)){
			InputHandler(gfx, mouse, grid, is_running, event);
		}
		// Highlight the cell in the grid matrix where the mouse is hovering	
		if (mouse->active && mouse->hover){
			GFX_DrawGridCursorGhost(gfx);
		}
		GFX_DrawGrid(gfx, grid);
		SDL_RenderPresent(gfx->renderer);
		// Grid_Print(grid); // For debugging 
	}	
}

int main(){
	bool is_running = true;
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Fatal error: Failed to initialize SDL: %s\n", SDL_GetError());
		exit(EXIT_SUCCESS);
	}
	GFX* gfx = GFX_Init();

	// But can it blend? (Allows for transparent rendering)
	SDL_SetRenderDrawBlendMode(gfx->renderer, SDL_BLENDMODE_BLEND);

	gameLoop(gfx, &is_running);	
	
	GFX_CleanQuit(gfx, true);
	return EXIT_SUCCESS;
}

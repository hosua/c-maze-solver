#include "maze.h"
#include "graphics.h"
#include "input.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

// This should be called first before trying to do anything with SDL
void initEverything(){
	if (SDL_Init(SDL_INIT_EVERYTHING)){
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		quitEverything();
	}

	// Initialize all graphics related stuff
	if (!GFX_Init()){
		quitEverything();
	}

	Grid_Init();
	Mouse_Init();

	g_cursor = GFX_InitCursor(arrow);
	SDL_SetCursor(g_cursor);
}

void quitEverything(){
	printf("Quitting, goodbye!\n");
	SDL_DestroyRenderer(g_gfx->renderer);
    SDL_DestroyWindow(g_gfx->window);
    SDL_Quit();
	exit(EXIT_SUCCESS);
}

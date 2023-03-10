#include "global_declarations.h"
#include "input.h"
#include "graphics.h"
#include "maze.h"

void gameLoop(GFX* gfx, bool* is_running){
	// Initialize everything
	Maze* maze = Maze_Init();
	Mouse* mouse = Mouse_Init();
	Maze_SetPlayerStart(maze);

	SDL_Cursor* cursor = GFX_InitCursor(cursor_img);
	SDL_SetCursor(cursor);

	GFX_ClearScreen(gfx);
	GFX_SetMazeTheme(gfx);

	Maze_SetPlayer(maze);
	Maze_SetDefaultGoal(maze);

	// Game loop
	while (is_running){
		GFX_ClearScreen(gfx);
		SDL_Event event;

		GFX_RenderMaze(gfx, maze);

		while (SDL_PollEvent(&event)){
			InputHandler(gfx, mouse, maze, is_running, event);
		}
		// Highlight the cell in the maze matrix where the mouse is hovering	
		if (mouse->active && mouse->hover){
			GFX_RenderCursorGhost(gfx, mouse);
		}
		SDL_RenderPresent(gfx->renderer);
		// Maze_Print(maze); // For debugging 
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

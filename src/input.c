#include "input.h"
#include "graphics.h"
#include "maze.h"
#include "global_declarations.h"

Mouse* Mouse_Init(){
	Mouse* mouse = (Mouse*)malloc(sizeof(Mouse));
	memset(mouse, 0, sizeof(Mouse));
	return mouse;
}

void Mouse_UpdatePos(Mouse* mouse){
	SDL_GetMouseState(&mouse->pos.x, &mouse->pos.y); // Relative to Window
	mouse->maze_pos.x = (mouse->pos.x / GRID_CELL_SIZE);
	mouse->maze_pos.y = (mouse->pos.y / GRID_CELL_SIZE);

	// Ensure that coordinates stay in bounds
	if (mouse->maze_pos.x == GRID_WIDTH)
		mouse->maze_pos.x--;
	if (mouse->maze_pos.y == GRID_HEIGHT)
		mouse->maze_pos.y--;
}

void Mouse_PrintPos(Mouse* mouse){
	printf("Mouse pos: (%i,%i)\n", mouse->pos.x, mouse->pos.y);
}

// returns maze coordinate based on mouse position
Coord Mouse_GetMazePos(Mouse* mouse){
	return mouse->maze_pos;
}

// returns raw mouse position
Coord Mouse_GetPos(Mouse* mouse){
	return mouse->pos;
}

bool Mouse_IsInWindow(Mouse* mouse, SDL_Window* window){
	Coord pos = Mouse_GetPos(mouse);
	Coord boundary;
	SDL_GetWindowSize(window, &boundary.x, &boundary.y);
	if (pos.x < 0 || pos.y < 0 || pos.x > boundary.x || pos.y > boundary.y)
		return false;
	// printf("Window size: %ix%i\n", boundary.x, boundary.y);
	return true;
}

void Mouse_SetCursorGhost(GFX* gfx, SDL_Event event){
	// set the cursor ghost to mouse position
	gfx->cursor_ghost.x = (event.motion.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
	gfx->cursor_ghost.y = (event.motion.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;
}
void Mouse_PrintMazePos(Mouse* mouse){
	fprintf(stdout, "Mouse maze position: (%i,%i)\n", mouse->maze_pos.x, mouse->maze_pos.y);
}

// Handles keyboard and mouse events
void InputHandler(GFX* gfx, Mouse* mouse, Maze* maze, bool* is_running, SDL_Event event){
	switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_w: case SDLK_UP:
					Maze_MovePlayer(maze, P_UP);
					break;
				case SDLK_s: case SDLK_DOWN:
					Maze_MovePlayer(maze, P_DOWN);
					break;
				case SDLK_a: case SDLK_LEFT:
					Maze_MovePlayer(maze, P_LEFT);
					break;
				case SDLK_d: case SDLK_RIGHT:
					Maze_MovePlayer(maze, P_RIGHT);
					break;
				case SDLK_g:
					// Set new goal at mouse position
					Maze_SetGoal(maze, mouse);
					break;
				case SDLK_r:
					Maze_Reset(maze);
					GFX_RenderMaze(gfx, maze);
					break;
				case SDLK_ESCAPE:
					GFX_CleanQuit(gfx, true);
					break;
			}
			break;
		case SDL_MOUSEMOTION:
			Mouse_UpdatePos(mouse);
			Mouse_SetCursorGhost(gfx, event);
			if (!mouse->active)
				mouse->active = SDL_TRUE;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse->is_down = SDL_TRUE;
			break;
		case SDL_MOUSEBUTTONUP:
			mouse->is_down = SDL_FALSE;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse->hover)
				mouse->hover = SDL_TRUE;
			else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse->hover)
				mouse->hover = SDL_FALSE;
			break;
		case SDL_QUIT:
			is_running = false;
			GFX_CleanQuit(gfx, true);
			break;
		default:
			break;
	}

	if (mouse->is_down && Mouse_IsInWindow(mouse, gfx->window)){
		Mouse_PrintPos(mouse);
		// Mouse_PrintMazePos(mouse);
		switch(event.button.button){
			case SDL_BUTTON_LEFT:
				Maze_SetWall(maze, mouse);
				break;
			// TODO: Figure out why the hell holding mouse button down works for right but not left
			case SDL_BUTTON_RIGHT:
				Maze_UnsetWall(maze, mouse);
				break;
			default:
				break;
		}
	}
}

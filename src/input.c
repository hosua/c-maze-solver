#include "input.h"
#include "graphics.h"
#include "grid.h"
#include "global_declarations.h"

Mouse* Mouse_Init(){
	Mouse* mouse = (Mouse*)malloc(sizeof(Mouse));
	memset(mouse, 0, sizeof(Mouse));
	return mouse;
}

void Mouse_UpdatePos(Mouse* mouse){
	SDL_GetMouseState(&mouse->pos.x, &mouse->pos.y); // Relative to Window
	mouse->grid_pos.x = (mouse->pos.x / GRID_CELL_SIZE);
	mouse->grid_pos.y = (mouse->pos.y / GRID_CELL_SIZE);

	// Ensure that coordinates stay in bounds
	if (mouse->grid_pos.x == GRID_WIDTH)
		mouse->grid_pos.x--;
	if (mouse->grid_pos.y == GRID_HEIGHT)
		mouse->grid_pos.y--;
}

void Mouse_PrintPos(Mouse* mouse){
	printf("Mouse pos: (%i,%i)\n", mouse->pos.x, mouse->pos.y);
}

// returns grid coordinate based on mouse position
Coord Mouse_GetGridPos(Mouse* mouse){
	return mouse->grid_pos;
}
void Mouse_PrintGridPos(Mouse* mouse){
	fprintf(stdout, "Mouse grid position: (%i,%i)\n", mouse->grid_pos.x, mouse->grid_pos.y);
}

// Handles keyboard and mouse events
void InputHandler(GFX* gfx, Mouse* mouse, Grid* grid, bool* is_running, SDL_Event event){
	switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_w: case SDLK_UP:
					Grid_MovePlayer(grid, P_UP);
					break;
				case SDLK_s: case SDLK_DOWN:
					Grid_MovePlayer(grid, P_DOWN);
					break;
				case SDLK_a: case SDLK_LEFT:
					Grid_MovePlayer(grid, P_LEFT);
					break;
				case SDLK_d: case SDLK_RIGHT:
					Grid_MovePlayer(grid, P_RIGHT);
					break;
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
			if (!mouse->is_down)
				mouse->is_down = SDL_TRUE;
			break;
		case SDL_MOUSEBUTTONUP:
			if (mouse->is_down)
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

	if (mouse->is_down){
		// Mouse_PrintGridPos(mouse);
		switch(event.button.button){
			case SDL_BUTTON_LEFT:
				Grid_SetWall(grid, mouse);
				break;
			// TODO: Figure out why the hell holding mouse button down works for right but not left
			case SDL_BUTTON_RIGHT:
				Grid_UnsetWall(grid, mouse);
				break;
			default:
				break;
		}
	}
}

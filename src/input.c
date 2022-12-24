#include "input.h"
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

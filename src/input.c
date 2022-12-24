#include "input.h"
#include "global_defines.h"

Mouse* g_mouse = NULL;

void Mouse_Init(){
	g_mouse = (Mouse*)malloc(sizeof(Mouse));
	memset(g_mouse, 0, sizeof(Mouse));
}

void Mouse_UpdatePos(){
	SDL_GetMouseState(&g_mouse->pos.x, &g_mouse->pos.y); // Relative to Window
	g_mouse->grid_pos.x = (g_mouse->pos.x / GRID_CELL_SIZE);
	g_mouse->grid_pos.y = (g_mouse->pos.y / GRID_CELL_SIZE);

	// Ensure that coordinates stay in bounds
	if (g_mouse->grid_pos.x == GRID_WIDTH)
		g_mouse->grid_pos.x--;
	if (g_mouse->grid_pos.y == GRID_HEIGHT)
		g_mouse->grid_pos.y--;
}

void Mouse_PrintPos(){
	printf("Mouse pos: (%i,%i)\n", g_mouse->pos.x, g_mouse->pos.y);
}

// returns grid coordinate based on mouse position
Coord Mouse_GetGridPos(){
	return g_mouse->grid_pos;
}
void Mouse_PrintGridPos(){
	fprintf(stdout, "Mouse grid position: (%i,%i)\n", g_mouse->grid_pos.x, g_mouse->grid_pos.y);
}

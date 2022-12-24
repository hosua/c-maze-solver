#include "graphics.h"

const char *cursor_img[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "XXXXXXXXXX                      ",
  "X........X                      ",
  "X........X                      ",
  "X........X                      ",
  "X........X                      ",
  "X........X                      ",
  "X........X                      ",
  "X........X                      ",
  "X........X                      ",
  "X........X                      ",
  "XXXXXXXXXX                      ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

GFX* GFX_Init(){
	GFX* gfx = NULL;
	gfx = (GFX*)malloc(sizeof(GFX));
	memset(gfx, 0, sizeof(GFX));

	gfx->grid_colors = (GridColors*)malloc(sizeof(GridColors));

	gfx->window = SDL_CreateWindow("Maze", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			SCREEN_X, SCREEN_Y, 
			0);
	if (!gfx->window){
		fprintf(stderr, "Fatal Error: Window failed to initialize\n");
		fprintf(stderr, "SDL2 Error: %s\n", SDL_GetError());
		GFX_CleanQuit(gfx, false);
	}

	gfx->renderer = SDL_CreateRenderer(gfx->window, -1, SDL_RENDERER_ACCELERATED);
	gfx->texture = NULL;

	gfx->window_surface = SDL_GetWindowSurface(gfx->window);

	if (!gfx->window_surface){
		fprintf(stderr, "Failed to get surface from window.\n");
		fprintf(stderr, "SDL2 Error: %s", SDL_GetError());
		GFX_CleanQuit(gfx, false);
	}

	GFX_InitGridCursor(gfx);
	GFX_InitGridCursorGhost(gfx);
	return gfx;
}

void GFX_CleanQuit(GFX* gfx, bool success){
	printf("Quitting, goodbye!\n");
	SDL_DestroyRenderer(gfx->renderer);
    SDL_DestroyWindow(gfx->window);
    SDL_Quit();
	return (success) ? exit(EXIT_SUCCESS) : exit(EXIT_FAILURE);
}

SDL_Cursor* GFX_InitCursor(const char *image[]){
	int i, row, col;
	Uint8 data[4*32];
	Uint8 mask[4*32];
	int hot_x, hot_y;
	i = -1;
	for (row=0; row<32; ++row){
		for (col=0; col<32; ++col){
			if (col % 8) {
				data[i] <<= 1;
				mask[i] <<= 1;
			} else {
				++i;
				data[i] = mask[i] = 0;
			}
			switch (image[4+row][col]){
				case 'X':
					data[i] |= 0x01;
					mask[i] |= 0x01;
					break;
				case '.':
					mask[i] |= 0x01;
					break;
				case ' ':
					break;
			}
		}
	}
	sscanf(image[4+row], "%i,%i", &hot_x, &hot_y);
	return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}

void GFX_SetSDLColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a, SDL_Color* color){
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
}

void GFX_SetGridTheme(GFX* gfx){
	// Dark theme
	GFX_SetSDLColor(22,22,22,255, &gfx->grid_colors->bg);
	GFX_SetSDLColor(44,44,44,255, &gfx->grid_colors->line); 
	GFX_SetSDLColor(44,44,44,255, &gfx->grid_colors->cursor_ghost); 
	GFX_SetSDLColor(255,255,255,255, &gfx->grid_colors->cursor);
	GFX_SetSDLColor(255,255,255,255, &gfx->grid_colors->wall);
}

void GFX_ClearScreen(GFX* gfx){
	SDL_SetRenderDrawColor(gfx->renderer, 0, 0, 0, 255); // draw black screen
	SDL_RenderClear(gfx->renderer);
}

void GFX_DrawGrid(GFX* gfx, Grid* grid){
	SDL_SetRenderDrawColor(gfx->renderer, 
			gfx->grid_colors->bg.r, gfx->grid_colors->bg.g, gfx->grid_colors->bg.b,
			gfx->grid_colors->bg.a);

	SDL_RenderClear(gfx->renderer);

	SDL_SetRenderDrawColor(gfx->renderer, 
			gfx->grid_colors->line.r, gfx->grid_colors->line.g, gfx->grid_colors->line.b,
			gfx->grid_colors->line.a);

	// Render grid lines
	for (int x = 0; x < SCREEN_X; x += GRID_CELL_SIZE){
		SDL_RenderDrawLine(gfx->renderer, x, 0, x, SCREEN_Y);
	}

	for (int y = 0; y < SCREEN_Y; y += GRID_CELL_SIZE){
		SDL_RenderDrawLine(gfx->renderer, 0, y, SCREEN_X, y);
	}


	SDL_Rect grid_wall_rects[GRID_WIDTH*GRID_HEIGHT];
	int ent_rects_count = 0;
	// Gather everything on the grid matrix into wall rect array
	for (int y = 0; y < GRID_HEIGHT; y++){
		for (int x = 0; x < GRID_WIDTH; x++){
			GridEntity ent = grid->mat[y][x];
			switch(ent){
				case G_NONE:
					break;
				case G_WALL:
				{
					SDL_Rect wall_rect = {
						.x = (x * GRID_CELL_SIZE),
						.y = (y * GRID_CELL_SIZE),
						.w = GRID_CELL_SIZE,
						.h = GRID_CELL_SIZE
					};
					grid_wall_rects[ent_rects_count++] = wall_rect;
					break;
				}
				case G_PLAYER:
					break;
				default:
					break;
			}
		}
	}

	// Render the contents in the wall rect array
	SDL_SetRenderDrawColor(gfx->renderer, 
			gfx->grid_colors->wall.r, gfx->grid_colors->wall.g, gfx->grid_colors->wall.b,
			gfx->grid_colors->wall.a);
	SDL_RenderFillRects(gfx->renderer, grid_wall_rects, ent_rects_count);
}

// Set Grid Cursor's initial state
void GFX_InitGridCursor(GFX* gfx){
	gfx->grid_cursor.x = (GRID_WIDTH-1)/2 * GRID_CELL_SIZE;
	gfx->grid_cursor.y = (GRID_HEIGHT-1)/2 * GRID_CELL_SIZE;
	gfx->grid_cursor.w = GRID_CELL_SIZE;
	gfx->grid_cursor.h = GRID_CELL_SIZE;
}

// Set Grid Cursor Ghost's initial state
void GFX_InitGridCursorGhost(GFX* gfx){
	gfx->grid_cursor_ghost.x = gfx->grid_cursor.x;
	gfx->grid_cursor_ghost.y = gfx->grid_cursor.y;
	gfx->grid_cursor_ghost.w = gfx->grid_cursor.w;
	gfx->grid_cursor_ghost.h = gfx->grid_cursor.h;
}

void GFX_SetGridCursorGhost(GFX* gfx, SDL_Event event){
	// set the cursor ghost to mouse position
	gfx->grid_cursor_ghost.x = (event.motion.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
	gfx->grid_cursor_ghost.y = (event.motion.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;
}
// Highlight the grid at where the user's mouse is hovering	
void GFX_DrawGridCursorGhost(GFX* gfx){
	SDL_SetRenderDrawColor(gfx->renderer, 
			gfx->grid_colors->cursor_ghost.r,
			gfx->grid_colors->cursor_ghost.g,
			gfx->grid_colors->cursor_ghost.b,
			gfx->grid_colors->cursor_ghost.a);
	SDL_RenderFillRect(gfx->renderer, &gfx->grid_cursor_ghost);
}




#include "graphics.h"

GFX* g_gfx = NULL;
SDL_Cursor* g_cursor = NULL;
GridColors* g_grid_colors = NULL;

const char *arrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "X                               ",
  "XX                              ",
  "X.X                             ",
  "X..X                            ",
  "X...X                           ",
  "X....X                          ",
  "X.....X                         ",
  "X......X                        ",
  "X.......X                       ",
  "X........X                      ",
  "X.....XXXXX                     ",
  "X..X..X                         ",
  "X.X X..X                        ",
  "XX  X..X                        ",
  "X    X..X                       ",
  "     X..X                       ",
  "      X..X                      ",
  "      X..X                      ",
  "       XX                       ",
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

bool GFX_Init(){
	g_gfx = (GFX*)malloc(sizeof(GFX));
	memset(g_gfx, 0, sizeof(GFX));

	g_grid_colors = (GridColors*)malloc(sizeof(GridColors));

	g_gfx->window = SDL_CreateWindow("Maze", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
			SCREEN_X, SCREEN_Y, 
			0);
	if (!g_gfx->window){
		fprintf(stderr, "Window failed to initialize\n");
		fprintf(stderr, "SDL2 Error: %s\n", SDL_GetError());
		return false;
	}
	g_gfx->renderer = SDL_CreateRenderer(g_gfx->window, -1, SDL_RENDERER_ACCELERATED);
	g_gfx->texture = NULL;

	GFX_InitGridCursor();
	GFX_InitGridCursorGhost();
	return true;
}

SDL_Cursor *GFX_InitCursor(const char *image[]){
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

void GFX_SetGridTheme(){
	// Dark theme
	GFX_SetSDLColor(22,22,22,255, &g_grid_colors->bg);
	GFX_SetSDLColor(44,44,44,255, &g_grid_colors->line); 
	GFX_SetSDLColor(44,44,44,255, &g_grid_colors->cursor_ghost); 
	GFX_SetSDLColor(255,255,255,255, &g_grid_colors->cursor);
	GFX_SetSDLColor(255,255,255,255, &g_grid_colors->wall);
}

void GFX_ClearScreen(){
	SDL_SetRenderDrawColor(g_gfx->renderer, 0, 0, 0, 255); // draw black screen
	SDL_RenderClear(g_gfx->renderer);
}

void GFX_DrawGrid(){
	SDL_SetRenderDrawColor(g_gfx->renderer, 
			g_grid_colors->bg.r, g_grid_colors->bg.g, g_grid_colors->bg.b,
			g_grid_colors->bg.a);

	SDL_RenderClear(g_gfx->renderer);

	SDL_SetRenderDrawColor(g_gfx->renderer, 
			g_grid_colors->line.r, g_grid_colors->line.g, g_grid_colors->line.b,
			g_grid_colors->line.a);

	// Render grid lines
	for (int x = 0; x < SCREEN_X; x += GRID_CELL_SIZE){
		SDL_RenderDrawLine(g_gfx->renderer, x, 0, x, SCREEN_Y);
	}

	for (int y = 0; y < SCREEN_Y; y += GRID_CELL_SIZE){
		SDL_RenderDrawLine(g_gfx->renderer, 0, y, SCREEN_X, y);
	}


	SDL_Rect grid_wall_rects[GRID_WIDTH*GRID_HEIGHT];
	int ent_rects_count = 0;
	// Gather everything on the grid matrix into wall rect array
	for (int y = 0; y < GRID_HEIGHT; y++){
		for (int x = 0; x < GRID_WIDTH; x++){
			GridEntity ent = g_grid->mat[y][x];
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
	SDL_SetRenderDrawColor(g_gfx->renderer, 
			g_grid_colors->wall.r, g_grid_colors->wall.g, g_grid_colors->wall.b,
			g_grid_colors->wall.a);
	SDL_RenderFillRects(g_gfx->renderer, grid_wall_rects, ent_rects_count);
}


// Set Grid Cursor's initial state
void GFX_InitGridCursor(){
	g_gfx->grid_cursor.x = (GRID_WIDTH-1)/2 * GRID_CELL_SIZE;
	g_gfx->grid_cursor.y = (GRID_HEIGHT-1)/2 * GRID_CELL_SIZE;
	g_gfx->grid_cursor.w = GRID_CELL_SIZE;
	g_gfx->grid_cursor.h = GRID_CELL_SIZE;
}

// Set Grid Cursor Ghost's initial state
void GFX_InitGridCursorGhost(){
	g_gfx->grid_cursor_ghost.x = g_gfx->grid_cursor.x;
	g_gfx->grid_cursor_ghost.y = g_gfx->grid_cursor.y;
	g_gfx->grid_cursor_ghost.w = g_gfx->grid_cursor.w;
	g_gfx->grid_cursor_ghost.h = g_gfx->grid_cursor.h;
}

void GFX_SetGridCursorGhost(SDL_Event event){
	// set the cursor ghost to mouse position
	g_gfx->grid_cursor_ghost.x = (event.motion.x / GRID_CELL_SIZE) * GRID_CELL_SIZE;
	g_gfx->grid_cursor_ghost.y = (event.motion.y / GRID_CELL_SIZE) * GRID_CELL_SIZE;
}

// Highlight the grid at where the user's mouse is hovering	
void GFX_DrawGridCursorGhost(){
	SDL_SetRenderDrawColor(g_gfx->renderer, 
			g_grid_colors->cursor_ghost.r,
			g_grid_colors->cursor_ghost.g,
			g_grid_colors->cursor_ghost.b,
			g_grid_colors->cursor_ghost.a);
	SDL_RenderFillRect(g_gfx->renderer, &g_gfx->grid_cursor_ghost);
}




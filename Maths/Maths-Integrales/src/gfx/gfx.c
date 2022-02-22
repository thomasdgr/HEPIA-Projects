/// @file gfx.c
/// @author Florent Gluck
/// @date November 6, 2016
/// Helper routines to render pixels in fullscreen graphic mode.
/// Uses the SDL2 library.
/// updated september 13 2019 by Pierre Kunzli

#include "../matrix/matrix.h"
#include "gfx.h"

int global_m = 0;
int global_n = 0;

// rajouté (déplacement vers cette librairie pour gagner en lisibilité)
// ajout d'un paramètre matrix pour savoir quelles valeurs sont à modifier
void render_image(int m, int n, struct gfx_context_t** context, matrix mat){
  if(*context==NULL) {
      *context = gfx_create("result.pgm", n, m);
      global_m = m;
      global_n = n;
  }
  if(global_m!=m || global_n!=n){
      global_m = m;
      global_n = n;
      *context = gfx_update(*context, m, n);
  }
  if (!*context) {
      fprintf(stderr, "Graphic mode initialization failed!\n");
      return;
  }
  SDL_ShowCursor(SDL_ENABLE);
  gfx_clear(*context, COLOR_BLACK);
  for(int x = 0; x < n; x++){
    for(int y = 0; y < m; y++) {
	  // on multiplie par 255 soit la valeur max pour dénormaliser
      uint32_t px = mat.data[y][x]*255;
	  // on donne trois fois le meme pixel car c'est du gris, pas du RGB
      uint32_t color = MAKE_COLOR(px, px, px);
      gfx_putpixel(*context, x, y, color);
    }
  }
}
// rien n'a été modifié par rapport à l'exemple plus bas

/// Create a fullscreen graphic window.
/// @param title Title of the window.
/// @param width Width of the window in pixels.
/// @param height Height of the window in pixels.
/// @return a pointer to the graphic context or NULL if it failed.
struct gfx_context_t* gfx_create(char *title, uint width, uint height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) goto error;
	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	uint32_t *pixels = malloc(width*height*sizeof(uint32_t));
	struct gfx_context_t *ctxt = malloc(sizeof(struct gfx_context_t));

	if (!window || !renderer || !texture || !pixels || !ctxt) goto error;

	ctxt->renderer = renderer;
	ctxt->texture = texture;
	ctxt->window = window;
	ctxt->width = width;
	ctxt->height = height;
	ctxt->pixels = pixels;

	SDL_ShowCursor(SDL_DISABLE);
	gfx_clear(ctxt, COLOR_BLACK);
	return ctxt;

error:
	return NULL;
}

/// Update the graphic context
/// @param ctxt The graphics context
/// @param width New width of the window
/// @param height New height of the window
/// @return a pointer to the new graphic context or NULL if it failed
struct gfx_context_t* gfx_update(struct gfx_context_t* ctxt, uint width, uint height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) goto error;
	SDL_SetWindowSize(ctxt->window, width, height);
	SDL_Texture *texture = SDL_CreateTexture(ctxt->renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, width, height);
	if(ctxt->pixels!=NULL) free(ctxt->pixels);
	uint32_t *pixels = malloc(width*height*sizeof(uint32_t));

	if (!texture || !pixels || !ctxt) goto error;

	ctxt->texture = texture;
	ctxt->width = width;
	ctxt->height = height;
	ctxt->pixels = pixels;

	SDL_ShowCursor(SDL_DISABLE);
	gfx_clear(ctxt, COLOR_BLACK);
	return ctxt;

error:
	return NULL;
}

/// Draw a pixel in the specified graphic context.
/// @param ctxt Graphic context where the pixel is to be drawn.
/// @param x X coordinate of the pixel.
/// @param y Y coordinate of the pixel.
/// @param color Color of the pixel.
void gfx_putpixel(struct gfx_context_t *ctxt, int x, int y, uint32_t color) {
	if (x < ctxt->width && y < ctxt->height)
		ctxt->pixels[ctxt->width*y+x] = color;
}

/// Clear the specified graphic context.
/// @param ctxt Graphic context to clear.
/// @param color Color to use.
void gfx_clear(struct gfx_context_t *ctxt, uint32_t color) {
	int n = ctxt->width*ctxt->height;
	while (n)
		ctxt->pixels[--n] = color;
}

/// Display the graphic context.
/// @param ctxt Graphic context to clear.
void gfx_present(struct gfx_context_t *ctxt) {
	SDL_UpdateTexture(ctxt->texture, NULL, ctxt->pixels, ctxt->width*sizeof(uint32_t));
	SDL_RenderCopy(ctxt->renderer, ctxt->texture, NULL, NULL);
	SDL_RenderPresent(ctxt->renderer);
}

/// Destroy a graphic window.
/// @param ctxt Graphic context of the window to close.
void gfx_destroy(struct gfx_context_t *ctxt) {
	SDL_ShowCursor(SDL_ENABLE);
	SDL_DestroyTexture(ctxt->texture);
	SDL_DestroyRenderer(ctxt->renderer);
	SDL_DestroyWindow(ctxt->window);
	free(ctxt->pixels);
	ctxt->texture = NULL;
	ctxt->renderer = NULL;
	ctxt->window = NULL;
	ctxt->pixels = NULL;
	SDL_Quit();
	free(ctxt);
}

/// If a key was pressed, returns its key code (non blocking call).
/// List of key codes: https://wiki.libsdl.org/SDL_Keycode
/// @return 0 if enter was not pressed.
SDL_Keycode gfx_keypressed() {
	SDL_PumpEvents();
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN)
			return event.key.keysym.sym;
	}
	return 0;
}

// affichage d'une image avec sdl2 à partir d'une matrice
void display(matrix mat){
    struct gfx_context_t* context = NULL;
    printf("press ENTER to continue\n");
    while(gfx_keypressed() != SDLK_RETURN){
        if(gfx_keypressed() == SDLK_SPACE){
            exit(0);
        }
        render_image(mat.m, mat.n, &context, mat);
        gfx_present(context);
    }
	matrix_destroy(&mat);
    gfx_destroy(context);
}

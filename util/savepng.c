/*
 * SDL_SavePNG -- libpng-based SDL_Surface writer.
 *
 * This code is free software, available under zlib/libpng license.
 * http://www.libpng.org/pub/png/src/libpng-LICENSE.txt
 */
#include "SDL.h"

#ifdef DISABLE_SAVEPNG
SDL_Surface *SDL_PNGFormatAlpha(SDL_Surface *src)
{
    return NULL;
}

int SDL_SavePNG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst)
{
    return -1;
}
#else

#include "png.h"
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1

#define USE_ROW_POINTERS

/* libpng callbacks */
static void png_error_SDL(png_structp ctx, png_const_charp str)
{
	SDL_SetError("libpng: %s\n", str);
}
static void png_write_SDL(png_structp png_ptr, png_bytep data, png_size_t length)
{
	//SDL_RWops *rw = (SDL_RWops*)png_get_io_ptr(png_ptr);
	//SDL_RWwrite(rw, data, sizeof(png_byte), length);
}

SDL_Surface *SDL_PNGFormatAlpha(SDL_Surface *src)
{
	/* NO-OP for images < 32bpp and 32bpp images that already have Alpha channel */
	if (src->format->BitsPerPixel <= 24 || src->format->Amask) {
		src->refcount++;
		return src;
	}

	/* Convert 32bpp alpha-less image to 24bpp alpha-less image */
	SDL_Surface *surf = SDL_CreateRGBSurface(src->flags, src->w, src->h, 24,
		src->format->Rmask, src->format->Gmask, src->format->Bmask, 0);
	SDL_BlitSurface(src, NULL, surf, NULL);

	return surf;
}

int SDL_SavePNG_RW(SDL_Surface *surface, SDL_RWops *dst, int freedst)
{

	return (SUCCESS);
}

#endif

